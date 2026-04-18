import os

from flask import current_app
from itsdangerous import URLSafeTimedSerializer, BadSignature, SignatureExpired

_REFRESH_MAX_AGE = 30 * 24 * 60 * 60


def _is_production():
    return os.environ.get("FLASK_ENV") == "production"


def set_refresh_cookie(response, refresh_token):
    prod = _is_production()
    response.set_cookie(
        "refresh_token",
        value=refresh_token,
        httponly=True,
        secure=prod,
        samesite="None" if prod else "Lax",
        path="/api/auth",
        max_age=_REFRESH_MAX_AGE,
    )
    return response


def clear_refresh_cookie(response):
    prod = _is_production()
    response.set_cookie(
        "refresh_token",
        value="",
        httponly=True,
        secure=prod,
        samesite="None" if prod else "Lax",
        path="/api/auth",
        max_age=0,
    )
    return response


def create_exchange_code(user_id):
    s = URLSafeTimedSerializer(current_app.config["SECRET_KEY"])
    return s.dumps(str(user_id), salt="oauth-exchange")


def verify_exchange_code(code):
    s = URLSafeTimedSerializer(current_app.config["SECRET_KEY"])
    try:
        return s.loads(code, salt="oauth-exchange", max_age=60)
    except (BadSignature, SignatureExpired):
        return None
