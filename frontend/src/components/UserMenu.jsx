import { useState, useEffect, useRef } from "react";

const STORAGE_KEY = "algoscope_user";

function loadUser() {
  try {
    const raw = localStorage.getItem(STORAGE_KEY);
    return raw ? JSON.parse(raw) : null;
  } catch {
    return null;
  }
}

function saveUser(user) {
  if (user) localStorage.setItem(STORAGE_KEY, JSON.stringify(user));
  else localStorage.removeItem(STORAGE_KEY);
}

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
  profile: (
    <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
      <path d="M20 21v-2a4 4 0 0 0-4-4H8a4 4 0 0 0-4 4v2" />
      <circle cx="12" cy="7" r="4" />
    </svg>
  ),
  settings: (
    <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
      <circle cx="12" cy="12" r="3" />
      <path d="M19.4 15a1.65 1.65 0 0 0 .33 1.82l.06.06a2 2 0 0 1-2.83 2.83l-.06-.06a1.65 1.65 0 0 0-1.82-.33 1.65 1.65 0 0 0-1 1.51V21a2 2 0 0 1-4 0v-.09a1.65 1.65 0 0 0-1-1.51 1.65 1.65 0 0 0-1.82.33l-.06.06a2 2 0 0 1-2.83-2.83l.06-.06a1.65 1.65 0 0 0 .33-1.82 1.65 1.65 0 0 0-1.51-1H3a2 2 0 0 1 0-4h.09a1.65 1.65 0 0 0 1.51-1 1.65 1.65 0 0 0-.33-1.82l-.06-.06a2 2 0 0 1 2.83-2.83l.06.06a1.65 1.65 0 0 0 1.82.33h0a1.65 1.65 0 0 0 1-1.51V3a2 2 0 0 1 4 0v.09a1.65 1.65 0 0 0 1 1.51h0a1.65 1.65 0 0 0 1.82-.33l.06-.06a2 2 0 0 1 2.83 2.83l-.06.06a1.65 1.65 0 0 0-.33 1.82v0a1.65 1.65 0 0 0 1.51 1H21a2 2 0 0 1 0 4h-.09a1.65 1.65 0 0 0-1.51 1z" />
    </svg>
  ),
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
};

function LoginModal({ onClose, onLogin }) {
  const [name, setName] = useState("");
  const [email, setEmail] = useState("");

  const submit = () => {
    if (!name.trim()) return;
    onLogin({ name: name.trim(), email: email.trim() });
    onClose();
  };

  return (
    <Modal title="Sign in" onClose={onClose}>
      <div style={{ display: "flex", flexDirection: "column", gap: "14px" }}>
        <div>
          <label style={labelStyle}>Name</label>
          <input
            autoFocus
            value={name}
            onChange={(e) => setName(e.target.value)}
            placeholder="Ada Lovelace"
            style={inputStyle}
            onKeyDown={(e) => e.key === "Enter" && submit()}
          />
        </div>
        <div>
          <label style={labelStyle}>Email</label>
          <input
            type="email"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            placeholder="ada@example.com"
            style={inputStyle}
            onKeyDown={(e) => e.key === "Enter" && submit()}
          />
        </div>
        <button onClick={submit} style={primaryBtn}>Sign in</button>
      </div>
    </Modal>
  );
}

function ProfileModal({ user, onClose, onSave }) {
  const [name, setName] = useState(user.name || "");
  const [email, setEmail] = useState(user.email || "");
  const [bio, setBio] = useState(user.bio || "");

  return (
    <Modal title="Profile" onClose={onClose}>
      <div style={{ display: "flex", flexDirection: "column", gap: "14px" }}>
        <div style={{ display: "flex", alignItems: "center", gap: "12px" }}>
          <Avatar name={name} size={48} />
          <div style={{ fontSize: "13px", color: "#8fa3c8" }}>Your AlgoScope identity</div>
        </div>
        <div>
          <label style={labelStyle}>Name</label>
          <input value={name} onChange={(e) => setName(e.target.value)} style={inputStyle} />
        </div>
        <div>
          <label style={labelStyle}>Email</label>
          <input value={email} onChange={(e) => setEmail(e.target.value)} style={inputStyle} />
        </div>
        <div>
          <label style={labelStyle}>Bio</label>
          <textarea
            value={bio}
            onChange={(e) => setBio(e.target.value)}
            rows={3}
            style={{ ...inputStyle, resize: "vertical", fontFamily: "inherit" }}
          />
        </div>
        <button
          onClick={() => {
            onSave({ ...user, name: name.trim() || user.name, email, bio });
            onClose();
          }}
          style={primaryBtn}
        >
          Save changes
        </button>
      </div>
    </Modal>
  );
}

function SettingsModal({ settings, onClose, onSave }) {
  const [theme, setTheme] = useState(settings.theme || "dark");
  const [autoRun, setAutoRun] = useState(!!settings.autoRun);
  const [showLineNumbers, setShowLineNumbers] = useState(settings.showLineNumbers !== false);

  return (
    <Modal title="Settings" onClose={onClose}>
      <div style={{ display: "flex", flexDirection: "column", gap: "16px" }}>
        <div>
          <label style={labelStyle}>Theme</label>
          <select value={theme} onChange={(e) => setTheme(e.target.value)} style={inputStyle}>
            <option value="dark">Dark</option>
            <option value="light">Light</option>
            <option value="system">System</option>
          </select>
        </div>
        <label style={{ display: "flex", alignItems: "center", gap: "10px", fontSize: "13px", color: "#c8d8f0", cursor: "pointer" }}>
          <input type="checkbox" checked={autoRun} onChange={(e) => setAutoRun(e.target.checked)} />
          Auto-run on code change
        </label>
        <label style={{ display: "flex", alignItems: "center", gap: "10px", fontSize: "13px", color: "#c8d8f0", cursor: "pointer" }}>
          <input type="checkbox" checked={showLineNumbers} onChange={(e) => setShowLineNumbers(e.target.checked)} />
          Show editor line numbers
        </label>
        <button
          onClick={() => {
            onSave({ theme, autoRun, showLineNumbers });
            onClose();
          }}
          style={primaryBtn}
        >
          Save settings
        </button>
      </div>
    </Modal>
  );
}

function UserMenu({ collapsed }) {
  const [user, setUser] = useState(loadUser);
  const [settings, setSettings] = useState(() => {
    try {
      return JSON.parse(localStorage.getItem("algoscope_settings") || "{}");
    } catch {
      return {};
    }
  });
  const [popupOpen, setPopupOpen] = useState(false);
  const [modal, setModal] = useState(null); // 'login' | 'profile' | 'settings'
  const buttonRef = useRef(null);
  const popupRef = useRef(null);

  useEffect(() => saveUser(user), [user]);
  useEffect(() => {
    localStorage.setItem("algoscope_settings", JSON.stringify(settings));
  }, [settings]);

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
          title={collapsed ? user.name : undefined}
        >
          <Avatar name={user.name} />
          {!collapsed && (
            <span
              style={{
                fontSize: "12.5px",
                fontWeight: 600,
                color: "#c8d8f0",
                overflow: "hidden",
                textOverflow: "ellipsis",
                whiteSpace: "nowrap",
              }}
            >
              {user.name}
            </span>
          )}
        </button>
      ) : (
        <button
          onClick={() => setModal("login")}
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
            <Avatar name={user.name} />
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
                {user.name}
              </div>
              {user.email && (
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
              )}
            </div>
          </div>

          <button
            style={menuItem}
            onClick={() => {
              setPopupOpen(false);
              setModal("profile");
            }}
            onMouseEnter={(e) => (e.currentTarget.style.background = "#131d2e")}
            onMouseLeave={(e) => (e.currentTarget.style.background = "transparent")}
          >
            {ICON.profile}
            Profile
          </button>
          <button
            style={menuItem}
            onClick={() => {
              setPopupOpen(false);
              setModal("settings");
            }}
            onMouseEnter={(e) => (e.currentTarget.style.background = "#131d2e")}
            onMouseLeave={(e) => (e.currentTarget.style.background = "transparent")}
          >
            {ICON.settings}
            Settings
          </button>
          <button
            style={{ ...menuItem, color: "#f87171" }}
            onClick={() => {
              setPopupOpen(false);
              setUser(null);
            }}
            onMouseEnter={(e) => (e.currentTarget.style.background = "#1d1318")}
            onMouseLeave={(e) => (e.currentTarget.style.background = "transparent")}
          >
            {ICON.logout}
            Log out
          </button>
        </div>
      )}

      {modal === "login" && (
        <LoginModal onClose={() => setModal(null)} onLogin={(u) => setUser(u)} />
      )}
      {modal === "profile" && user && (
        <ProfileModal user={user} onClose={() => setModal(null)} onSave={setUser} />
      )}
      {modal === "settings" && (
        <SettingsModal settings={settings} onClose={() => setModal(null)} onSave={setSettings} />
      )}
    </div>
  );
}

export default UserMenu;
