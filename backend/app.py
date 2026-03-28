from flask import Flask, request, jsonify
from flask_cors import CORS
import re
import subprocess
import tempfile
import os
import shutil

from ml.instrumenter import instrument_code

app = Flask(__name__)
CORS(app)


def safe_decode(data: bytes) -> str:
    if data is None:
        return ""
    return data.decode("utf-8", errors="replace")


@app.route("/run", methods=["POST"])
def run_code():
    body = request.json
    code = body["code"]
    skip_instrumentation = body.get("skip_instrumentation", False)
    stdin_text = body.get("stdin", "")

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
            return jsonify({
                "error": f"Instrumentation error: {str(e)}"
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
            return jsonify({
                "error": compile_proc.stderr,
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
            return jsonify({
                "error": "Execution timed out.",
                "instrumented_code": code
            })
        except Exception as e:
            return jsonify({
                "error": f"Runtime error: {str(e)}",
                "instrumented_code": code
            })

        stdout_text = safe_decode(run_proc.stdout)
        stderr_text = safe_decode(run_proc.stderr)

        if run_proc.returncode != 0:
            return jsonify({
                "error": stderr_text if stderr_text.strip() else f"Program exited with code {run_proc.returncode}.",
                "trace": stdout_text.splitlines(),
                "instrumented_code": code
            })

        return jsonify({
            "trace": stdout_text.splitlines(),
            "stderr": stderr_text,
            "instrumented_code": code
        })


if __name__ == "__main__":
    app.run(debug=True)
