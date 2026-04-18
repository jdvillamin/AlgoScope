from flask import Blueprint, request, jsonify
from flask_jwt_extended import jwt_required, get_jwt_identity

from models import db, SavedCode

codes_bp = Blueprint("codes", __name__, url_prefix="/api/codes")


def _serialize(code):
    return {
        "id": code.id,
        "title": code.title,
        "code": code.code,
        "created_at": code.created_at.isoformat(),
        "updated_at": code.updated_at.isoformat(),
    }


@codes_bp.route("", methods=["GET"])
@jwt_required()
def list_codes():
    user_id = get_jwt_identity()
    codes = (SavedCode.query
             .filter_by(user_id=user_id)
             .order_by(SavedCode.updated_at.desc())
             .all())
    return jsonify({"codes": [_serialize(c) for c in codes]}), 200


@codes_bp.route("", methods=["POST"])
@jwt_required()
def create_code():
    user_id = get_jwt_identity()
    body = request.get_json(silent=True) or {}
    title = (body.get("title") or "").strip()
    code = body.get("code") or ""

    if not title:
        return jsonify({"errors": ["Title is required."]}), 400
    if not code:
        return jsonify({"errors": ["Code is required."]}), 400

    saved = SavedCode(user_id=user_id, title=title, code=code)
    db.session.add(saved)
    db.session.commit()
    return jsonify({"code": _serialize(saved)}), 201


@codes_bp.route("/<code_id>", methods=["GET"])
@jwt_required()
def get_code(code_id):
    user_id = get_jwt_identity()
    saved = db.session.get(SavedCode, code_id)
    if not saved or saved.user_id != user_id:
        return jsonify({"errors": ["Not found."]}), 404
    return jsonify({"code": _serialize(saved)}), 200


@codes_bp.route("/<code_id>", methods=["PUT"])
@jwt_required()
def update_code(code_id):
    user_id = get_jwt_identity()
    saved = db.session.get(SavedCode, code_id)
    if not saved or saved.user_id != user_id:
        return jsonify({"errors": ["Not found."]}), 404

    body = request.get_json(silent=True) or {}
    if "title" in body:
        title = (body["title"] or "").strip()
        if not title:
            return jsonify({"errors": ["Title is required."]}), 400
        saved.title = title
    if "code" in body:
        code = body["code"] or ""
        if not code:
            return jsonify({"errors": ["Code is required."]}), 400
        saved.code = code

    db.session.commit()
    return jsonify({"code": _serialize(saved)}), 200


@codes_bp.route("/<code_id>", methods=["DELETE"])
@jwt_required()
def delete_code(code_id):
    user_id = get_jwt_identity()
    saved = db.session.get(SavedCode, code_id)
    if not saved or saved.user_id != user_id:
        return jsonify({"errors": ["Not found."]}), 404

    db.session.delete(saved)
    db.session.commit()
    return jsonify({"message": "Deleted."}), 200
