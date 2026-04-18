import re

from flask import Blueprint, request, jsonify, make_response
from flask_jwt_extended import (
    create_access_token, create_refresh_token,
    jwt_required, get_jwt_identity, decode_token
)

from models import db, limiter, User
from auth_utils import (
    set_refresh_cookie, clear_refresh_cookie, verify_exchange_code,
)

auth_bp = Blueprint("auth", __name__, url_prefix="/api/auth")

EMAIL_RE = re.compile(r"^[^@\s]+@[^@\s]+\.[^@\s]+$")

COMMON_PASSWORDS = frozenset([
    "password", "12345678", "123456789", "1234567890", "qwerty123",
    "password1", "iloveyou", "sunshine1", "princess1", "football1",
    "charlie1", "access14", "trustno1", "letmein1", "baseball1",
    "abcdefgh", "abc12345", "monkey123", "master123", "dragon123",
])


def _validate_password(password):
    errors = []
    if len(password) < 8:
        errors.append("Password must be at least 8 characters.")
    if len(set(password)) < 3:
        errors.append("Password is too simple.")
    if password.lower() in COMMON_PASSWORDS:
        errors.append("This password is too common. Please choose a stronger one.")
    return errors


def _user_json(user):
    return {"id": user.id, "email": user.email, "username": user.username}


def _login_response(user, status=200):
    access_token = create_access_token(identity=user.id)
    refresh_token = create_refresh_token(identity=user.id)
    resp = make_response(jsonify({
        "access_token": access_token,
        "user": _user_json(user),
    }), status)
    set_refresh_cookie(resp, refresh_token)
    return resp


@auth_bp.route("/register", methods=["POST"])
@limiter.limit("3/minute")
def register():
    body = request.get_json(silent=True) or {}
    email = (body.get("email") or "").strip().lower()
    username = (body.get("username") or "").strip()
    password = body.get("password") or ""

    errors = []
    if not email or not EMAIL_RE.match(email):
        errors.append("Valid email is required.")
    if not username or len(username) < 3 or len(username) > 80:
        errors.append("Username must be 3\u201380 characters.")
    errors.extend(_validate_password(password))
    if errors:
        return jsonify({"errors": errors}), 400

    if User.query.filter_by(email=email).first() or User.query.filter_by(username=username).first():
        return jsonify({"errors": ["An account with this email or username already exists."]}), 409

    user = User(email=email, username=username)
    user.set_password(password)
    db.session.add(user)
    db.session.commit()

    return _login_response(user, status=201)


@auth_bp.route("/login", methods=["POST"])
@limiter.limit("5/minute")
def login():
    body = request.get_json(silent=True) or {}
    email = (body.get("email") or "").strip().lower()
    password = body.get("password") or ""

    user = User.query.filter_by(email=email).first()
    if not user:
        return jsonify({"errors": ["Invalid email or password."]}), 401
    if not user.password_hash:
        provider = (user.oauth_provider or "OAuth").capitalize()
        return jsonify({"errors": [f"This account uses {provider} sign-in. Please use the \"{provider}\" button."]}), 401
    if not user.check_password(password):
        return jsonify({"errors": ["Invalid email or password."]}), 401

    return _login_response(user)


@auth_bp.route("/refresh", methods=["POST"])
@limiter.limit("10/minute")
def refresh():
    refresh_token = request.cookies.get("refresh_token")
    if not refresh_token:
        return jsonify({"errors": ["Missing refresh token."]}), 401
    try:
        decoded = decode_token(refresh_token)
        user_id = decoded["sub"]
    except Exception:
        return jsonify({"errors": ["Invalid or expired refresh token."]}), 401
    user = db.session.get(User, user_id)
    if not user:
        return jsonify({"errors": ["User not found."]}), 401
    access_token = create_access_token(identity=user_id)
    return jsonify({
        "access_token": access_token,
        "user": _user_json(user),
    }), 200


@auth_bp.route("/logout", methods=["POST"])
def logout():
    resp = make_response(jsonify({"message": "Logged out."}), 200)
    clear_refresh_cookie(resp)
    return resp


@auth_bp.route("/exchange", methods=["POST"])
@limiter.limit("10/minute")
def exchange():
    body = request.get_json(silent=True) or {}
    code = body.get("code") or ""
    if not code:
        return jsonify({"errors": ["Code is required."]}), 400
    user_id = verify_exchange_code(code)
    if not user_id:
        return jsonify({"errors": ["Invalid or expired code."]}), 401
    user = db.session.get(User, user_id)
    if not user:
        return jsonify({"errors": ["User not found."]}), 401
    return _login_response(user)


@auth_bp.route("/me", methods=["GET"])
@jwt_required()
def me():
    user_id = get_jwt_identity()
    user = db.session.get(User, user_id)
    if not user:
        return jsonify({"errors": ["User not found."]}), 404
    return jsonify({"user": _user_json(user)}), 200
