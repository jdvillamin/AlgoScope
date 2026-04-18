import os
from urllib.parse import urlencode

from authlib.integrations.flask_client import OAuth
from flask import Blueprint, redirect, url_for, current_app
from flask_jwt_extended import create_access_token, create_refresh_token

from models import db, User

oauth_bp = Blueprint("oauth", __name__, url_prefix="/api/auth")
oauth = OAuth()

FRONTEND_URL = os.environ.get("FRONTEND_URL", "http://localhost:5173")

oauth.register(
    name="google",
    client_id=os.environ.get("GOOGLE_CLIENT_ID"),
    client_secret=os.environ.get("GOOGLE_CLIENT_SECRET"),
    server_metadata_url="https://accounts.google.com/.well-known/openid-configuration",
    client_kwargs={"scope": "openid email profile"},
)

oauth.register(
    name="github",
    client_id=os.environ.get("GITHUB_CLIENT_ID"),
    client_secret=os.environ.get("GITHUB_CLIENT_SECRET"),
    access_token_url="https://github.com/login/oauth/access_token",
    authorize_url="https://github.com/login/oauth/authorize",
    api_base_url="https://api.github.com/",
    client_kwargs={"scope": "user:email"},
)


def _find_or_create_user(provider, oauth_id, email, name):
    user = User.query.filter_by(oauth_provider=provider, oauth_id=str(oauth_id)).first()
    if user:
        return user

    user = User.query.filter_by(email=email).first()
    if user:
        if not user.oauth_provider:
            user.oauth_provider = provider
            user.oauth_id = str(oauth_id)
            db.session.commit()
        return user

    base = (name or email.split("@")[0]).lower().replace(" ", "_")[:70]
    username = base
    suffix = 1
    while User.query.filter_by(username=username).first():
        username = f"{base}_{suffix}"
        suffix += 1

    user = User(
        email=email,
        username=username,
        oauth_provider=provider,
        oauth_id=str(oauth_id),
    )
    db.session.add(user)
    db.session.commit()
    return user


def _redirect_with_tokens(user):
    access_token = create_access_token(identity=user.id)
    refresh_token = create_refresh_token(identity=user.id)
    params = urlencode({
        "access_token": access_token,
        "refresh_token": refresh_token,
    })
    return redirect(f"{FRONTEND_URL}/auth/callback#{params}")


@oauth_bp.route("/google", methods=["GET"])
def google_login():
    redirect_uri = url_for("oauth.google_callback", _external=True)
    return oauth.google.authorize_redirect(redirect_uri)


@oauth_bp.route("/google/callback", methods=["GET"])
def google_callback():
    try:
        token = oauth.google.authorize_access_token()
    except Exception as e:
        current_app.logger.error("Google OAuth error: %s", e)
        return redirect(f"{FRONTEND_URL}/auth/callback#error=oauth_failed")
    userinfo = token.get("userinfo") or oauth.google.userinfo()
    if not userinfo.get("email_verified"):
        return redirect(f"{FRONTEND_URL}/auth/callback#error=email_not_verified")
    user = _find_or_create_user(
        provider="google",
        oauth_id=userinfo["sub"],
        email=userinfo["email"],
        name=userinfo.get("name"),
    )
    return _redirect_with_tokens(user)


@oauth_bp.route("/github", methods=["GET"])
def github_login():
    redirect_uri = url_for("oauth.github_callback", _external=True)
    return oauth.github.authorize_redirect(redirect_uri)


@oauth_bp.route("/github/callback", methods=["GET"])
def github_callback():
    try:
        token = oauth.github.authorize_access_token()
    except Exception as e:
        current_app.logger.error("GitHub OAuth error: %s", e)
        return redirect(f"{FRONTEND_URL}/auth/callback#error=oauth_failed")
    resp = oauth.github.get("user", token=token)
    profile = resp.json()

    email = profile.get("email")
    if not email:
        resp2 = oauth.github.get("user/emails", token=token)
        emails = resp2.json()
        primary = next((e for e in emails if e.get("primary") and e.get("verified")), None)
        if not primary:
            primary = next((e for e in emails if e.get("verified")), None)
        if not primary:
            return redirect(f"{FRONTEND_URL}/auth/callback#error=email_not_verified")
        email = primary["email"]

    user = _find_or_create_user(
        provider="github",
        oauth_id=profile["id"],
        email=email,
        name=profile.get("login"),
    )
    return _redirect_with_tokens(user)
