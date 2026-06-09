import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import "./index.css";
import App from "./App.jsx";
import AppRouter from "./AppRouter.jsx";
import { AuthProvider } from "./contexts/AuthContext.jsx";

// Apply the saved theme before first paint so reloads don't flash the wrong one.
document.documentElement.setAttribute(
  "data-theme",
  localStorage.getItem("algoscope:theme") || "dark",
);

createRoot(document.getElementById("root")).render(
  <StrictMode>
    <AuthProvider>
      <AppRouter />
    </AuthProvider>
  </StrictMode>,
);
