import { useEffect, useRef, useState } from "react";

const ERROR_MESSAGES = {
  oauth_failed: "Sign-in was cancelled or failed. Please try again.",
  email_not_verified: "Your email is not verified with this provider. Please verify your email and try again.",
};

function OAuthCallback({ onTokens }) {
  const processed = useRef(false);
  const [error, setError] = useState(null);

  useEffect(() => {
    if (processed.current) return;
    const hash = window.location.hash.slice(1);
    if (!hash) return;
    processed.current = true;

    const params = new URLSearchParams(hash);

    const err = params.get("error");
    if (err) {
      setError(ERROR_MESSAGES[err] || "Something went wrong. Please try again.");
      window.history.replaceState(null, "", "/");
      return;
    }

    const accessToken = params.get("access_token");
    const refreshToken = params.get("refresh_token");

    if (accessToken && refreshToken) {
      onTokens(accessToken, refreshToken).then(() => {
        window.location.href = "/";
      });
    } else {
      window.location.href = "/";
    }
  }, [onTokens]);

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
