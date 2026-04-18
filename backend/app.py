from datetime import timedelta

from dotenv import load_dotenv
load_dotenv()

from flask import Flask, request, jsonify
from flask_cors import CORS
from flask_migrate import Migrate
from flask_jwt_extended import JWTManager, get_jwt_identity, verify_jwt_in_request
import re
import subprocess
import tempfile
import os
import shutil

from ml.instrumenter import instrument_code
from models import db, bcrypt, limiter, RunHistory

app = Flask(__name__)

_db_url = os.environ.get(
    "DATABASE_URL", "sqlite:///" + os.path.join(os.path.dirname(__file__), "algoscope.db")
)
if _db_url.startswith("postgres://"):
    _db_url = _db_url.replace("postgres://", "postgresql://", 1)
app.config["SQLALCHEMY_DATABASE_URI"] = _db_url
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

_is_production = os.environ.get("FLASK_ENV") == "production"
_secret = os.environ.get("SECRET_KEY")
_jwt_secret = os.environ.get("JWT_SECRET_KEY")
if not _secret or not _jwt_secret:
    if _is_production:
        raise RuntimeError("SECRET_KEY and JWT_SECRET_KEY must be set in production")
    _secret = _secret or "dev-secret-change-in-production"
    _jwt_secret = _jwt_secret or "dev-jwt-secret-change-in-production"
app.config["SECRET_KEY"] = _secret
app.config["JWT_SECRET_KEY"] = _jwt_secret
app.config["JWT_ACCESS_TOKEN_EXPIRES"] = timedelta(minutes=15)
app.config["JWT_REFRESH_TOKEN_EXPIRES"] = timedelta(days=30)

db.init_app(app)
bcrypt.init_app(app)
jwt = JWTManager(app)
limiter.init_app(app)
migrate = Migrate(app, db)

from auth import auth_bp
from codes import codes_bp
from history import history_bp
from oauth import oauth_bp, oauth
app.register_blueprint(auth_bp)
app.register_blueprint(codes_bp)
app.register_blueprint(history_bp)
app.register_blueprint(oauth_bp)
oauth.init_app(app)

# Allowed origins: local Vite dev server + any origins listed in FRONTEND_ORIGIN.
# FRONTEND_ORIGIN is a comma-separated list, e.g.
#   "https://algoscope-visualizer.vercel.app,https://algoscope-visualizer-git-master-foo.vercel.app"
_frontend_origin_env = os.environ.get("FRONTEND_ORIGIN", "")
_allowed_origins = ["http://localhost:5173", "http://127.0.0.1:5173"]
_allowed_origins.extend(
    origin.strip() for origin in _frontend_origin_env.split(",") if origin.strip()
)
CORS(app, origins=_allowed_origins, supports_credentials=True)


@app.errorhandler(429)
def ratelimit_handler(e):
    return jsonify({"error": "Too many requests. Please try again later."}), 429


@app.route("/health", methods=["GET"])
def health():
    return jsonify({"status": "ok"}), 200


def safe_decode(data: bytes) -> str:
    if data is None:
        return ""
    return data.decode("utf-8", errors="replace")


def _get_optional_user_id():
    try:
        verify_jwt_in_request(optional=True)
        return get_jwt_identity()
    except Exception:
        return None


def _save_run_history(user_id, code, trace, status):
    if not user_id:
        return
    run = RunHistory(user_id=user_id, code=code, trace=trace, status=status)
    db.session.add(run)
    db.session.commit()


@app.route("/run", methods=["POST"])
@limiter.limit("10/minute")
def run_code():
    body = request.get_json(silent=True) or {}
    code = body.get("code") or ""
    if not code:
        return jsonify({"error": "Code is required."}), 400
    if len(code) > 50_000:
        return jsonify({"error": "Code exceeds the maximum allowed length (50 000 characters)."}), 400
    skip_instrumentation = body.get("skip_instrumentation", False)
    instrument_only = body.get("instrument_only", False)
    stdin_text = body.get("stdin", "")
    if len(stdin_text) > 1_000:
        return jsonify({"error": "Input exceeds the maximum allowed length (1 000 characters)."}), 400
    user_id = _get_optional_user_id()

    if not instrument_only:
        # Validate that no number in stdin exceeds 20
        numbers = re.findall(r'-?\d+', stdin_text)
        for n in numbers:
            if abs(int(n)) > 20:
                return jsonify({
                    "error": f"Input number {n} exceeds the limit of 20."
                })

    if not skip_instrumentation:
        try:
            code = instrument_code(code)
        except Exception as e:
            app.logger.error("Instrumentation failed: %s", e)
            return jsonify({
                "error": "Instrumentation failed. Please check your code and try again."
            })

    if instrument_only:
        return jsonify({
            "instrumented_code": code
        })

    with tempfile.TemporaryDirectory() as tmp:
        cfile = os.path.join(tmp, "main.c")
        exe = os.path.join(tmp, "a.out")

        project_root = os.path.dirname(os.path.abspath(__file__))
        tracer_dir = os.path.join(project_root, "..", "tracer")

        tracer_c = os.path.join(tracer_dir, "tracer.c")
        tracer_h = os.path.join(tracer_dir, "tracer.h")

        with open(cfile, "w", encoding="utf-8") as f:
            f.write(code)

        shutil.copy(tracer_h, tmp)

        compile_proc = subprocess.run(
            ["gcc", cfile, tracer_c, "-o", exe],
            capture_output=True,
            text=True
        )

        if compile_proc.returncode != 0:
            raw_stderr = compile_proc.stderr or ""
            clean_lines = []
            for line in raw_stderr.splitlines():
                if "main.c:" in line:
                    parts = line.split("main.c:", 1)
                    clean_lines.append("Line " + parts[1] if len(parts) > 1 else line)
                elif line.strip() and not line.startswith("/"):
                    clean_lines.append(line)
            user_msg = "\n".join(clean_lines).strip() if clean_lines else "Compilation failed. Please check your code for syntax errors."
            _save_run_history(user_id, code, None, "compile_error")
            return jsonify({
                "error": user_msg,
                "instrumented_code": code
            })

        try:
            run_proc = subprocess.run(
                [exe],
                input=stdin_text.encode("utf-8") if stdin_text else None,
                capture_output=True,
                timeout=5
            )
        except subprocess.TimeoutExpired:
            _save_run_history(user_id, code, None, "timeout")
            return jsonify({
                "error": "Your program took too long to finish and was stopped. Check for infinite loops or reduce input size.",
                "instrumented_code": code
            })
        except Exception as e:
            app.logger.error("Runtime error: %s", e)
            _save_run_history(user_id, code, None, "runtime_error")
            return jsonify({
                "error": "Something went wrong while running your program. Please try again.",
                "instrumented_code": code
            })

        stdout_text = safe_decode(run_proc.stdout)
        stderr_text = safe_decode(run_proc.stderr)

        trace_lines = stdout_text.splitlines()

        if run_proc.returncode != 0:
            if stderr_text.strip():
                user_msg = re.sub(r'/[^\s:]+/', '', stderr_text).strip()
            else:
                user_msg = f"Your program exited with an error (code {run_proc.returncode})."
            _save_run_history(user_id, code, trace_lines, "runtime_error")
            return jsonify({
                "error": user_msg,
                "trace": trace_lines,
                "instrumented_code": code
            })

        _save_run_history(user_id, code, trace_lines, "success")
        return jsonify({
            "trace": trace_lines,
            "stderr": stderr_text,
            "instrumented_code": code
        })


if __name__ == "__main__":
    app.run(debug=os.environ.get("FLASK_DEBUG", "0") == "1")
