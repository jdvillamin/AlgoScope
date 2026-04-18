import { useEffect, useRef, useState } from "react";
import { useAuth } from "../contexts/useAuth";

const ERROR_MESSAGES = {
  oauth_failed: "Sign-in was cancelled or failed. Please try again.",
  email_not_verified:
    "Your email is not verified with this provider. Please verify your email and try again.",
};

function OAuthCallback() {
  const { exchangeOAuthCode } = useAuth();
  const processed = useRef(false);
  const [error, setError] = useState(null);

  useEffect(() => {
    if (processed.current) return;
    const params = new URLSearchParams(window.location.search);

    const err = params.get("error");
    if (err) {
      processed.current = true;
      const handle = async () => {
        setError(ERROR_MESSAGES[err] || "Something went wrong. Please try again.");
      };
      handle();
      return;
    }

    const code = params.get("code");
    if (!code) return;
    processed.current = true;

    const handle = async () => {
      try {
        await exchangeOAuthCode(code);
        window.location.href = "/";
      } catch {
        setError("Sign-in failed. Please try again.");
      }
    };
    handle();
  }, [exchangeOAuthCode]);

  if (error) {
    return (
      <div
        style={{
          display: "flex",
          flexDirection: "column",
          alignItems: "center",
          justifyContent: "center",
          height: "100vh",
          background: "#080d15",
          gap: "16px",
        }}
      >
        <div style={{ color: "#f87171", fontSize: "14px" }}>{error}</div>
        <a
          href="/"
          style={{
            color: "#4b8cf7",
            fontSize: "13px",
            textDecoration: "none",
          }}
        >
          Back to AlgoScope
        </a>
      </div>
    );
  }

  return (
    <div
      style={{
        display: "flex",
        alignItems: "center",
        justifyContent: "center",
        height: "100vh",
        background: "#080d15",
        color: "#647e9c",
        fontSize: "14px",
      }}
    >
      Signing you in...
    </div>
  );
}

export default OAuthCallback;
