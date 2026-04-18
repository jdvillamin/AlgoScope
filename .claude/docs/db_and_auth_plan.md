# Database & Authentication Plan

## Tech Stack

| Layer | Technology | Why |
|-------|-----------|-----|
| Database | PostgreSQL | Robust, production-ready, great SQLAlchemy support |
| ORM | SQLAlchemy + Flask-SQLAlchemy | Standard Flask ORM; declarative models, relationship support |
| Migrations | Flask-Migrate (Alembic) | Version-controlled schema changes |
| Auth | Flask-JWT-Extended | Stateless JWT tokens; clean fit for React SPA |
| Password hashing | Flask-Bcrypt | Industry-standard bcrypt hashing |
| Frontend auth state | React Context + localStorage | Simple JWT storage and auth context propagation |

### Python packages to add
```
flask-sqlalchemy
flask-migrate
flask-jwt-extended
flask-bcrypt
psycopg2-binary
```

### Frontend packages to add
```
react-router-dom
```

---

## Database Schema

### users
| Column | Type | Notes |
|--------|------|-------|
| id | UUID (PK) | Default uuid4 |
| email | VARCHAR(255) | Unique, indexed |
| username | VARCHAR(80) | Unique, indexed |
| password_hash | VARCHAR(128) | Bcrypt hash |
| created_at | TIMESTAMP | Default now() |

### saved_codes
| Column | Type | Notes |
|--------|------|-------|
| id | UUID (PK) | Default uuid4 |
| user_id | UUID (FK → users.id) | Indexed |
| title | VARCHAR(255) | User-given name |
| code | TEXT | The C source code |
| created_at | TIMESTAMP | Default now() |
| updated_at | TIMESTAMP | Auto-updated |

### run_history
| Column | Type | Notes |
|--------|------|-------|
| id | UUID (PK) | Default uuid4 |
| user_id | UUID (FK → users.id) | Indexed |
| code | TEXT | Code that was run |
| trace | JSONB | Full trace output |
| status | VARCHAR(20) | "success" / "compile_error" / "runtime_error" / "timeout" |
| created_at | TIMESTAMP | Default now() |

---

## Implementation Steps

### Phase 1: Database Setup
1. Install Python packages (`flask-sqlalchemy`, `flask-migrate`, `psycopg2-binary`)
2. Add database config to `backend/app.py` (connection URI, SQLAlchemy init)
3. Create `backend/models.py` with User, SavedCode, RunHistory models
4. Initialize Flask-Migrate, generate and run initial migration
5. Verify tables exist in PostgreSQL

### Phase 2: Auth Backend
1. Install `flask-jwt-extended`, `flask-bcrypt`
2. Create `backend/auth.py` with routes:
   - `POST /api/auth/register` — validate, hash password, create user, return JWT
   - `POST /api/auth/login` — verify credentials, return access + refresh tokens
   - `POST /api/auth/refresh` — issue new access token from refresh token
   - `GET /api/auth/me` — return current user info (protected)
3. Configure JWT settings (secret key, token expiry: 15min access, 30day refresh)
4. Add `@jwt_required()` decorator to protected routes
5. Test all auth endpoints with curl/Postman

### Phase 3: User Features Backend
1. Create `backend/codes.py` with routes:
   - `GET /api/codes` — list user's saved codes
   - `POST /api/codes` — save new code
   - `GET /api/codes/<id>` — load specific saved code
   - `PUT /api/codes/<id>` — update saved code
   - `DELETE /api/codes/<id>` — delete saved code
2. Create `backend/history.py` with routes:
   - `GET /api/history` — list user's run history (paginated)
   - `GET /api/history/<id>` — get specific run with full trace
3. Modify `POST /run` to optionally save to run_history if user is authenticated
4. Add ownership checks (users can only access their own data)

### Phase 4: Frontend Auth
1. Install `react-router-dom`
2. Create `frontend/src/contexts/AuthContext.jsx` — JWT storage, login/logout/register functions, auto-refresh
3. Create `frontend/src/pages/Login.jsx` and `Register.jsx` — forms with validation
4. Add auth header interceptor to `frontend/src/api/backend.js` (attach JWT to all requests)
5. Add route protection — redirect unauthenticated users to login
6. Add login/logout UI to the app header

### Phase 5: Frontend User Features
1. Create `frontend/src/components/SavedCodes.jsx` — list, load, save, delete user codes
2. Create `frontend/src/components/RunHistory.jsx` — browsable execution history with trace replay
3. Add "Save" button to Editor that persists current code
4. Add "History" panel showing recent runs
5. Wire up auto-save to run_history on each successful `/run` call

### Phase 6: Polish & Deploy
1. Add proper error handling and loading states for all async operations
2. Add input validation (email format, password strength, code title length)
3. Set up environment variables for secrets (JWT_SECRET_KEY, DATABASE_URL)
4. Add CORS configuration for production
5. Test full flow: register → login → write code → run → save → reload → view history
