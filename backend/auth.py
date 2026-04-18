import re

from flask import Blueprint, request, jsonify
from flask_jwt_extended import (
    create_access_token, create_refresh_token,
    jwt_required, get_jwt_identity
)

from models import db, User

auth_bp = Blueprint("auth", __name__, url_prefix="/api/auth")

EMAIL_RE = re.compile(r"^[^@\s]+@[^@\s]+\.[^@\s]+$")


@auth_bp.route("/register", methods=["POST"])
def register():
    body = request.get_json(silent=True) or {}
    email = (body.get("email") or "").strip().lower()
    username = (body.get("username") or "").strip()
    password = body.get("password") or ""

    errors = []
    if not email or not EMAIL_RE.match(email):
        errors.append("Valid email is required.")
    if not username or len(username) < 3 or len(username) > 80:
        errors.append("Username must be 3–80 characters.")
    if len(password) < 8:
        errors.append("Password must be at least 8 characters.")
    if errors:
        return jsonify({"errors": errors}), 400

    if User.query.filter_by(email=email).first():
        return jsonify({"errors": ["Email is already registered."]}), 409
    if User.query.filter_by(username=username).first():
        return jsonify({"errors": ["Username is already taken."]}), 409

    user = User(email=email, username=username)
    user.set_password(password)
    db.session.add(user)
    db.session.commit()

    access_token = create_access_token(identity=user.id)
    refresh_token = create_refresh_token(identity=user.id)

    return jsonify({
        "access_token": access_token,
        "refresh_token": refresh_token,
        "user": {"id": user.id, "email": user.email, "username": user.username},
    }), 201


@auth_bp.route("/login", methods=["POST"])
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

    access_token = create_access_token(identity=user.id)
    refresh_token = create_refresh_token(identity=user.id)

    return jsonify({
        "access_token": access_token,
        "refresh_token": refresh_token,
        "user": {"id": user.id, "email": user.email, "username": user.username},
    }), 200


@auth_bp.route("/refresh", methods=["POST"])
@jwt_required(refresh=True)
def refresh():
    user_id = get_jwt_identity()
    access_token = create_access_token(identity=user_id)
    return jsonify({"access_token": access_token}), 200


@auth_bp.route("/me", methods=["GET"])
@jwt_required()
def me():
    user_id = get_jwt_identity()
    user = db.session.get(User, user_id)
    if not user:
        return jsonify({"errors": ["User not found."]}), 404
    return jsonify({
        "user": {"id": user.id, "email": user.email, "username": user.username},
    }), 200
