import { BrowserRouter, Routes, Route } from "react-router-dom";
import App from "./App";
import OAuthCallback from "./components/OAuthCallback";

function AppRouter() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/auth/callback" element={<OAuthCallback />} />
        <Route path="*" element={<App />} />
      </Routes>
    </BrowserRouter>
  );
}

export default AppRouter;
