import { useCallback } from "react";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import App from "./App";
import OAuthCallback from "./components/OAuthCallback";
import { useAuth } from "./contexts/useAuth";

function CallbackPage() {
  const { loginWithTokens } = useAuth();
  const handleTokens = useCallback(
    (access, refresh) => loginWithTokens(access, refresh),
    [loginWithTokens]
  );
  return <OAuthCallback onTokens={handleTokens} />;
}

function AppRouter() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/auth/callback" element={<CallbackPage />} />
        <Route path="*" element={<App />} />
      </Routes>
    </BrowserRouter>
  );
}

export default AppRouter;
