import { useState, useCallback, useEffect, useRef } from "react";
import API from "../api/backend";
import { AuthContext } from "./authContext";

function setAuthHeader(token) {
  if (token) {
    API.defaults.headers.common["Authorization"] = `Bearer ${token}`;
  } else {
    delete API.defaults.headers.common["Authorization"];
  }
}

export function AuthProvider({ children }) {
  const [user, setUser] = useState(null);
  const [loading, setLoading] = useState(true);
  const refreshTimer = useRef(null);
  const scheduleRef = useRef(null);

  const clearAuth = useCallback(() => {
    setUser(null);
    setAuthHeader(null);
    if (refreshTimer.current) clearTimeout(refreshTimer.current);
  }, []);

  useEffect(() => {
    scheduleRef.current = () => {
      if (refreshTimer.current) clearTimeout(refreshTimer.current);
      refreshTimer.current = setTimeout(async () => {
        try {
          const res = await API.post("/api/auth/refresh");
          setAuthHeader(res.data.access_token);
          scheduleRef.current?.();
        } catch {
          clearAuth();
        }
      }, 13 * 60 * 1000);
    };
  }, [clearAuth]);

  useEffect(() => {
    const init = async () => {
      try {
        const res = await API.post("/api/auth/refresh");
        setAuthHeader(res.data.access_token);
        setUser(res.data.user);
        scheduleRef.current?.();
      } catch {
        // No valid session
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
    setAuthHeader(res.data.access_token);
    setUser(res.data.user);
    scheduleRef.current?.();
    return res.data;
  }, []);

  const login = useCallback(async (email, password) => {
    const res = await API.post("/api/auth/login", { email, password });
    setAuthHeader(res.data.access_token);
    setUser(res.data.user);
    scheduleRef.current?.();
    return res.data;
  }, []);

  const exchangeOAuthCode = useCallback(async (code) => {
    const res = await API.post("/api/auth/exchange", { code });
    setAuthHeader(res.data.access_token);
    setUser(res.data.user);
    scheduleRef.current?.();
    return res.data;
  }, []);

  const logout = useCallback(async () => {
    clearAuth();
    try {
      await API.post("/api/auth/logout");
    } catch {
      // Best effort
    }
  }, [clearAuth]);

  return (
    <AuthContext.Provider value={{ user, loading, register, login, exchangeOAuthCode, logout }}>
      {children}
    </AuthContext.Provider>
  );
}
