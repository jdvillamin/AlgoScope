from flask import Blueprint, request, jsonify
from flask_jwt_extended import jwt_required, get_jwt_identity

from models import db, RunHistory

history_bp = Blueprint("history", __name__, url_prefix="/api/history")

ITEMS_PER_PAGE = 20


def _serialize(run, include_trace=False):
    data = {
        "id": run.id,
        "code": run.code,
        "status": run.status,
        "created_at": run.created_at.isoformat(),
    }
    if include_trace:
        data["trace"] = run.trace
    return data


@history_bp.route("", methods=["GET"])
@jwt_required()
def list_history():
    user_id = get_jwt_identity()
    page = request.args.get("page", 1, type=int)
    page = max(1, page)

    query = (RunHistory.query
             .filter_by(user_id=user_id)
             .order_by(RunHistory.created_at.desc()))
    total = query.count()
    runs = query.offset((page - 1) * ITEMS_PER_PAGE).limit(ITEMS_PER_PAGE).all()

    return jsonify({
        "history": [_serialize(r) for r in runs],
        "page": page,
        "total": total,
        "pages": (total + ITEMS_PER_PAGE - 1) // ITEMS_PER_PAGE,
    }), 200


@history_bp.route("/<run_id>", methods=["GET"])
@jwt_required()
def get_run(run_id):
    user_id = get_jwt_identity()
    run = db.session.get(RunHistory, run_id)
    if not run or run.user_id != user_id:
        return jsonify({"errors": ["Not found."]}), 404
    return jsonify({"run": _serialize(run, include_trace=True)}), 200
