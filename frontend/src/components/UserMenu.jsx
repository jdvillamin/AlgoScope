import { useState, useEffect, useRef } from "react";
import { useAuth } from "../contexts/useAuth";
import { baseURL } from "../api/backend";

function initials(name) {
  if (!name) return "?";
  const parts = name.trim().split(/\s+/);
  return ((parts[0]?.[0] || "") + (parts[1]?.[0] || "")).toUpperCase() || "?";
}

function Avatar({ name, size = 28 }) {
  return (
    <div
      style={{
        width: size,
        height: size,
        borderRadius: "50%",
        background: "linear-gradient(135deg, #4b8cf7, #7b5cf7)",
        color: "#fff",
        display: "flex",
        alignItems: "center",
        justifyContent: "center",
        fontSize: size * 0.4,
        fontWeight: 700,
        flexShrink: 0,
        userSelect: "none",
      }}
    >
      {initials(name)}
    </div>
  );
}

const ICON = {
  logout: (
    <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
      <path d="M9 21H5a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h4" />
      <polyline points="16 17 21 12 16 7" />
      <line x1="21" y1="12" x2="9" y2="12" />
    </svg>
  ),
  login: (
    <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
      <path d="M15 3h4a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2h-4" />
      <polyline points="10 17 15 12 10 7" />
      <line x1="15" y1="12" x2="3" y2="12" />
    </svg>
  ),
  close: (
    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
      <line x1="18" y1="6" x2="6" y2="18" />
      <line x1="6" y1="6" x2="18" y2="18" />
    </svg>
  ),
};

function Modal({ title, onClose, children }) {
  useEffect(() => {
    const onKey = (e) => e.key === "Escape" && onClose();
    window.addEventListener("keydown", onKey);
    return () => window.removeEventListener("keydown", onKey);
  }, [onClose]);

  return (
    <div
      onClick={onClose}
      style={{
        position: "fixed",
        inset: 0,
        background: "rgba(4, 8, 14, 0.65)",
        backdropFilter: "blur(2px)",
        display: "flex",
        alignItems: "center",
        justifyContent: "center",
        zIndex: 1000,
      }}
    >
      <div
        onClick={(e) => e.stopPropagation()}
        style={{
          width: "380px",
          maxWidth: "92vw",
          background: "#0e1520",
          border: "1px solid #1e2d42",
          borderRadius: "12px",
          boxShadow: "0 20px 60px rgba(0,0,0,0.6)",
          color: "#c8d8f0",
          fontFamily: "inherit",
        }}
      >
        <div
          style={{
            display: "flex",
            justifyContent: "space-between",
            alignItems: "center",
            padding: "14px 18px",
            borderBottom: "1px solid #1a2535",
          }}
        >
          <span style={{ fontSize: "13px", fontWeight: 700, letterSpacing: "0.5px" }}>{title}</span>
          <button
            onClick={onClose}
            style={{
              background: "transparent",
              border: "none",
              color: "#647e9c",
              cursor: "pointer",
              padding: 4,
              display: "flex",
            }}
          >
            {ICON.close}
          </button>
        </div>
        <div style={{ padding: "18px" }}>{children}</div>
      </div>
    </div>
  );
}

const inputStyle = {
  width: "100%",
  padding: "8px 10px",
  borderRadius: "6px",
  border: "1px solid #1e2d42",
  background: "#0a1018",
  color: "#c8d8f0",
  fontSize: "13px",
  fontFamily: "inherit",
  outline: "none",
  boxSizing: "border-box",
};

const labelStyle = {
  display: "block",
  fontSize: "11px",
  fontWeight: 600,
  letterSpacing: "0.6px",
  textTransform: "uppercase",
  color: "#647e9c",
  marginBottom: "6px",
};

const primaryBtn = {
  padding: "9px 14px",
  borderRadius: "8px",
  border: "1px solid #2a4a7e",
  background: "#1a2d4d",
  color: "#c8d8f0",
  fontSize: "12.5px",
  fontWeight: 600,
  cursor: "pointer",
  fontFamily: "inherit",
  width: "100%",
};

const errorStyle = {
  fontSize: "12px",
  color: "#f87171",
  padding: "6px 8px",
  borderRadius: "6px",
  background: "rgba(248, 113, 113, 0.08)",
};

function AuthModal({ onClose }) {
  const { login, register } = useAuth();
  const [mode, setMode] = useState("login");
  const [email, setEmail] = useState("");
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [errors, setErrors] = useState([]);
  const [submitting, setSubmitting] = useState(false);

  const submit = async () => {
    setErrors([]);
    setSubmitting(true);
    try {
      if (mode === "login") {
        await login(email, password);
      } else {
        await register(email, username, password);
      }
      onClose();
    } catch (err) {
      const data = err.response?.data;
      setErrors(data?.errors || [data?.msg || "Something went wrong. Please try again."]);
    } finally {
      setSubmitting(false);
    }
  };

  return (
    <Modal title={mode === "login" ? "Sign in" : "Create account"} onClose={onClose}>
      <div style={{ display: "flex", flexDirection: "column", gap: "14px" }}>
        <div>
          <label style={labelStyle}>Email</label>
          <input
            autoFocus
            type="email"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            placeholder="you@example.com"
            style={inputStyle}
            onKeyDown={(e) => e.key === "Enter" && submit()}
          />
        </div>
        {mode === "register" && (
          <div>
            <label style={labelStyle}>Username</label>
            <input
              value={username}
              onChange={(e) => setUsername(e.target.value)}
              placeholder="ada_lovelace"
              style={inputStyle}
              onKeyDown={(e) => e.key === "Enter" && submit()}
            />
          </div>
        )}
        <div>
          <label style={labelStyle}>Password</label>
          <input
            type="password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            placeholder="At least 8 characters"
            style={inputStyle}
            onKeyDown={(e) => e.key === "Enter" && submit()}
          />
        </div>
        {errors.length > 0 && (
          <div style={errorStyle}>
            {errors.map((e, i) => (
              <div key={i}>{e}</div>
            ))}
          </div>
        )}
        <button onClick={submit} disabled={submitting} style={{ ...primaryBtn, opacity: submitting ? 0.6 : 1 }}>
          {submitting ? "Please wait..." : mode === "login" ? "Sign in" : "Create account"}
        </button>
        <div style={{ textAlign: "center", fontSize: "12px", color: "#647e9c" }}>
          {mode === "login" ? (
            <>
              No account?{" "}
              <button
                onClick={() => { setMode("register"); setErrors([]); }}
                style={{ background: "none", border: "none", color: "#4b8cf7", cursor: "pointer", fontSize: "12px", fontFamily: "inherit", padding: 0 }}
              >
                Create one
              </button>
            </>
          ) : (
            <>
              Already have an account?{" "}
              <button
                onClick={() => { setMode("login"); setErrors([]); }}
                style={{ background: "none", border: "none", color: "#4b8cf7", cursor: "pointer", fontSize: "12px", fontFamily: "inherit", padding: 0 }}
              >
                Sign in
              </button>
            </>
          )}
        </div>

        <div style={{ display: "flex", alignItems: "center", gap: "10px", margin: "2px 0" }}>
          <div style={{ flex: 1, height: "1px", background: "#1e2d42" }} />
          <span style={{ fontSize: "11px", color: "#3d5270", fontWeight: 600 }}>OR</span>
          <div style={{ flex: 1, height: "1px", background: "#1e2d42" }} />
        </div>

        <a
          href={`${baseURL}/api/auth/google`}
          style={{
            ...primaryBtn,
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
            gap: "8px",
            textDecoration: "none",
            background: "#fff",
            color: "#333",
            border: "1px solid #ddd",
          }}
        >
          <svg width="16" height="16" viewBox="0 0 48 48"><path fill="#EA4335" d="M24 9.5c3.54 0 6.71 1.22 9.21 3.6l6.85-6.85C35.9 2.38 30.47 0 24 0 14.62 0 6.51 5.38 2.56 13.22l7.98 6.19C12.43 13.72 17.74 9.5 24 9.5z"/><path fill="#4285F4" d="M46.98 24.55c0-1.57-.15-3.09-.38-4.55H24v9.02h12.94c-.58 2.96-2.26 5.48-4.78 7.18l7.73 6c4.51-4.18 7.09-10.36 7.09-17.65z"/><path fill="#FBBC05" d="M10.53 28.59a14.5 14.5 0 0 1 0-9.18l-7.98-6.19a24.0 24.0 0 0 0 0 21.56l7.98-6.19z"/><path fill="#34A853" d="M24 48c6.48 0 11.93-2.13 15.89-5.81l-7.73-6c-2.15 1.45-4.92 2.3-8.16 2.3-6.26 0-11.57-4.22-13.47-9.91l-7.98 6.19C6.51 42.62 14.62 48 24 48z"/></svg>
          Continue with Google
        </a>

        <a
          href={`${baseURL}/api/auth/github`}
          style={{
            ...primaryBtn,
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
            gap: "8px",
            textDecoration: "none",
            background: "#24292e",
            color: "#fff",
            border: "1px solid #444",
          }}
        >
          <svg width="16" height="16" viewBox="0 0 24 24" fill="currentColor"><path d="M12 0C5.37 0 0 5.37 0 12c0 5.31 3.435 9.795 8.205 11.385.6.105.825-.255.825-.57 0-.285-.015-1.23-.015-2.235-3.015.555-3.795-.735-4.035-1.41-.135-.345-.72-1.41-1.23-1.695-.42-.225-1.02-.78-.015-.795.945-.015 1.62.87 1.845 1.23 1.08 1.815 2.805 1.305 3.495.99.105-.78.42-1.305.765-1.605-2.67-.3-5.46-1.335-5.46-5.925 0-1.305.465-2.385 1.23-3.225-.12-.3-.54-1.53.12-3.18 0 0 1.005-.315 3.3 1.23.96-.27 1.98-.405 3-.405s2.04.135 3 .405c2.295-1.56 3.3-1.23 3.3-1.23.66 1.65.24 2.88.12 3.18.765.84 1.23 1.905 1.23 3.225 0 4.605-2.805 5.625-5.475 5.925.435.375.81 1.095.81 2.22 0 1.605-.015 2.895-.015 3.3 0 .315.225.69.825.57A12.02 12.02 0 0 0 24 12c0-6.63-5.37-12-12-12z"/></svg>
          Continue with GitHub
        </a>
      </div>
    </Modal>
  );
}

function UserMenu({ collapsed }) {
  const { user, logout } = useAuth();
  const [popupOpen, setPopupOpen] = useState(false);
  const [authOpen, setAuthOpen] = useState(false);
  const buttonRef = useRef(null);
  const popupRef = useRef(null);

  useEffect(() => {
    if (!popupOpen) return;
    const onClick = (e) => {
      if (
        popupRef.current &&
        !popupRef.current.contains(e.target) &&
        buttonRef.current &&
        !buttonRef.current.contains(e.target)
      ) {
        setPopupOpen(false);
      }
    };
    window.addEventListener("mousedown", onClick);
    return () => window.removeEventListener("mousedown", onClick);
  }, [popupOpen]);

  const menuItem = {
    display: "flex",
    alignItems: "center",
    gap: "10px",
    padding: "9px 12px",
    fontSize: "12.5px",
    color: "#c8d8f0",
    cursor: "pointer",
    borderRadius: "6px",
    background: "transparent",
    border: "none",
    width: "100%",
    textAlign: "left",
    fontFamily: "inherit",
  };

  return (
    <div
      style={{
        borderTop: "1px solid #1a2535",
        padding: collapsed ? "8px 6px" : "10px 10px",
        position: "relative",
        marginTop: "auto",
      }}
    >
      {user ? (
        <button
          ref={buttonRef}
          onClick={() => setPopupOpen((v) => !v)}
          style={{
            display: "flex",
            alignItems: "center",
            gap: "10px",
            width: "100%",
            padding: collapsed ? "4px" : "8px 10px",
            borderRadius: "8px",
            border: "1px solid transparent",
            background: popupOpen ? "#131d2e" : "transparent",
            cursor: "pointer",
            fontFamily: "inherit",
            justifyContent: collapsed ? "center" : "flex-start",
          }}
          onMouseEnter={(e) => {
            if (!popupOpen) e.currentTarget.style.background = "#0f1928";
          }}
          onMouseLeave={(e) => {
            if (!popupOpen) e.currentTarget.style.background = "transparent";
          }}
          title={collapsed ? user.username : undefined}
        >
          <Avatar name={user.username} />
          {!collapsed && (
            <div style={{ overflow: "hidden", textAlign: "left" }}>
              <div
                style={{
                  fontSize: "12.5px",
                  fontWeight: 600,
                  color: "#c8d8f0",
                  overflow: "hidden",
                  textOverflow: "ellipsis",
                  whiteSpace: "nowrap",
                }}
              >
                {user.username}
              </div>
              <div
                style={{
                  fontSize: "10.5px",
                  color: "#506888",
                  overflow: "hidden",
                  textOverflow: "ellipsis",
                  whiteSpace: "nowrap",
                }}
              >
                {user.email}
              </div>
            </div>
          )}
        </button>
      ) : (
        <button
          onClick={() => setAuthOpen(true)}
          style={{
            display: "flex",
            alignItems: "center",
            gap: "10px",
            width: "100%",
            padding: collapsed ? "6px" : "8px 10px",
            borderRadius: "8px",
            border: "1px solid #1e2d42",
            background: "#0f1928",
            color: "#8fa3c8",
            fontSize: "12.5px",
            fontWeight: 600,
            cursor: "pointer",
            fontFamily: "inherit",
            justifyContent: "center",
          }}
          title="Sign in"
        >
          <span style={{ display: "flex" }}>{ICON.login}</span>
          {!collapsed && "Sign in"}
        </button>
      )}

      {popupOpen && user && (
        <div
          ref={popupRef}
          style={{
            position: "absolute",
            bottom: "calc(100% - 4px)",
            left: collapsed ? "calc(100% + 6px)" : "10px",
            right: collapsed ? "auto" : "10px",
            width: collapsed ? "220px" : "auto",
            background: "#0e1520",
            border: "1px solid #1e2d42",
            borderRadius: "10px",
            boxShadow: "0 12px 32px rgba(0,0,0,0.55)",
            padding: "6px",
            zIndex: 50,
          }}
        >
          <div
            style={{
              display: "flex",
              alignItems: "center",
              gap: "10px",
              padding: "10px 10px 12px",
              borderBottom: "1px solid #1a2535",
              marginBottom: "4px",
            }}
          >
            <Avatar name={user.username} />
            <div style={{ overflow: "hidden" }}>
              <div
                style={{
                  fontSize: "12.5px",
                  fontWeight: 700,
                  color: "#c8d8f0",
                  whiteSpace: "nowrap",
                  overflow: "hidden",
                  textOverflow: "ellipsis",
                }}
              >
                {user.username}
              </div>
              <div
                style={{
                  fontSize: "11px",
                  color: "#647e9c",
                  whiteSpace: "nowrap",
                  overflow: "hidden",
                  textOverflow: "ellipsis",
                }}
              >
                {user.email}
              </div>
            </div>
          </div>

          <button
            style={{ ...menuItem, color: "#f87171" }}
            onClick={() => {
              setPopupOpen(false);
              logout();
            }}
            onMouseEnter={(e) => (e.currentTarget.style.background = "#1d1318")}
            onMouseLeave={(e) => (e.currentTarget.style.background = "transparent")}
          >
            {ICON.logout}
            Log out
          </button>
        </div>
      )}

      {authOpen && <AuthModal onClose={() => setAuthOpen(false)} />}
    </div>
  );
}

export default UserMenu;
