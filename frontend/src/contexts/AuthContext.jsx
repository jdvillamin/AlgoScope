import { useState, useCallback, useEffect, useRef } from "react";
import API from "../api/backend";
import { AuthContext } from "./authContext";

const TOKEN_KEY = "algoscope:tokens";

function loadTokens() {
  try {
    const raw = localStorage.getItem(TOKEN_KEY);
    return raw ? JSON.parse(raw) : null;
  } catch {
    return null;
  }
}

function saveTokens(tokens) {
  if (tokens) localStorage.setItem(TOKEN_KEY, JSON.stringify(tokens));
  else localStorage.removeItem(TOKEN_KEY);
}

function applyTokens(tokens) {
  saveTokens(tokens);
  API.defaults.headers.common["Authorization"] = `Bearer ${tokens.access_token}`;
}

function clearTokens() {
  saveTokens(null);
  delete API.defaults.headers.common["Authorization"];
}

export function AuthProvider({ children }) {
  const [user, setUser] = useState(null);
  const [loading, setLoading] = useState(true);
  const refreshTimer = useRef(null);
  const scheduleRef = useRef(null);

  const clearAuth = useCallback(() => {
    setUser(null);
    clearTokens();
    if (refreshTimer.current) clearTimeout(refreshTimer.current);
  }, []);

  useEffect(() => {
    scheduleRef.current = (tokens) => {
      if (refreshTimer.current) clearTimeout(refreshTimer.current);
      refreshTimer.current = setTimeout(async () => {
        try {
          const res = await API.post("/api/auth/refresh", null, {
            headers: { Authorization: `Bearer ${tokens.refresh_token}` },
          });
          const newTokens = { ...tokens, access_token: res.data.access_token };
          applyTokens(newTokens);
          scheduleRef.current?.(newTokens);
        } catch {
          clearAuth();
        }
      }, 13 * 60 * 1000);
    };
  }, [clearAuth]);

  useEffect(() => {
    const init = async () => {
      const tokens = loadTokens();
      if (!tokens?.access_token) return;
      API.defaults.headers.common["Authorization"] = `Bearer ${tokens.access_token}`;
      try {
        const res = await API.get("/api/auth/me");
        setUser(res.data.user);
        scheduleRef.current?.(tokens);
      } catch {
        clearAuth();
      }
    };
    init().finally(() => setLoading(false));
  }, [clearAuth]);

  useEffect(() => {
    return () => {
      if (refreshTimer.current) clearTimeout(refreshTimer.current);
    };
  }, []);

  const register = useCallback(async (email, username, password) => {
    const res = await API.post("/api/auth/register", { email, username, password });
    const tokens = { access_token: res.data.access_token, refresh_token: res.data.refresh_token };
    applyTokens(tokens);
    setUser(res.data.user);
    scheduleRef.current?.(tokens);
    return res.data;
  }, []);

  const login = useCallback(async (email, password) => {
    const res = await API.post("/api/auth/login", { email, password });
    const tokens = { access_token: res.data.access_token, refresh_token: res.data.refresh_token };
    applyTokens(tokens);
    setUser(res.data.user);
    scheduleRef.current?.(tokens);
    return res.data;
  }, []);

  const loginWithTokens = useCallback(async (accessToken, refreshToken) => {
    const tokens = { access_token: accessToken, refresh_token: refreshToken };
    applyTokens(tokens);
    try {
      const res = await API.get("/api/auth/me");
      setUser(res.data.user);
      scheduleRef.current?.(tokens);
    } catch {
      clearAuth();
    }
  }, [clearAuth]);

  const logout = useCallback(() => {
    clearAuth();
  }, [clearAuth]);

  return (
    <AuthContext.Provider value={{ user, loading, register, login, loginWithTokens, logout }}>
      {children}
    </AuthContext.Provider>
  );
}
