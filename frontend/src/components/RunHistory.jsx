import { useState, useEffect, useCallback } from "react";
import { useAuth } from "../contexts/useAuth";
import { listHistory } from "../api/history";

function formatTime(iso) {
  try {
    const d = new Date(iso);
    const now = new Date();
    const diff = now - d;
    if (diff < 60000) return "just now";
    if (diff < 3600000) return `${Math.floor(diff / 60000)}m ago`;
    if (diff < 86400000) return `${Math.floor(diff / 3600000)}h ago`;
    return d.toLocaleDateString(undefined, { month: "short", day: "numeric" });
  } catch {
    return "";
  }
}

const STATUS_COLORS = {
  success: "#4ade80",
  compile_error: "#f87171",
  runtime_error: "#fb923c",
  timeout: "#fbbf24",
};

function RunHistory({ onLoadRun }) {
  const { user } = useAuth();
  const [runs, setRuns] = useState([]);
  const [page, setPage] = useState(1);
  const [totalPages, setTotalPages] = useState(1);
  const [expanded, setExpanded] = useState(false);

  const refresh = useCallback(() => {
    if (!user) return;
    listHistory(page)
      .then((data) => {
        setRuns(data.history);
        setTotalPages(data.pages);
      })
      .catch(() => {});
  }, [user, page]);

  useEffect(() => {
    if (expanded && user) refresh();
  }, [expanded, user, refresh]);

  if (!user) return null;

  return (
    <div style={{ padding: "8px 0" }}>
      <div
        onClick={() => setExpanded((v) => !v)}
        style={{
          padding: "0 14px 6px",
          fontSize: "10px",
          fontWeight: 700,
          letterSpacing: "1px",
          color: "#3d5270",
          textTransform: "uppercase",
          cursor: "pointer",
          display: "flex",
          alignItems: "center",
          gap: "6px",
        }}
      >
        <span
          style={{
            fontSize: "9px",
            transition: "transform 0.15s",
            transform: expanded ? "rotate(90deg)" : "rotate(0deg)",
            display: "inline-block",
          }}
        >
          ▶
        </span>
        Run History
      </div>

      {expanded && (
        <div>
          {runs.length === 0 ? (
            <div
              style={{
                padding: "6px 14px",
                fontSize: "11.5px",
                color: "#3d5270",
                fontStyle: "italic",
              }}
            >
              No runs yet
            </div>
          ) : (
            <>
              {runs.map((run) => (
                <div
                  key={run.id}
                  onClick={() => onLoadRun(run)}
                  style={{
                    padding: "6px 14px",
                    margin: "1px 6px",
                    borderRadius: "6px",
                    cursor: "pointer",
                    display: "flex",
                    alignItems: "center",
                    gap: "8px",
                    fontSize: "12px",
                    color: "#647e9c",
                    transition: "background 0.1s",
                  }}
                  onMouseEnter={(e) => {
                    e.currentTarget.style.background = "#0f1928";
                  }}
                  onMouseLeave={(e) => {
                    e.currentTarget.style.background = "transparent";
                  }}
                >
                  <span
                    style={{
                      width: "6px",
                      height: "6px",
                      borderRadius: "50%",
                      background: STATUS_COLORS[run.status] || "#506888",
                      flexShrink: 0,
                    }}
                    title={run.status}
                  />
                  <span
                    style={{
                      overflow: "hidden",
                      textOverflow: "ellipsis",
                      whiteSpace: "nowrap",
                      minWidth: 0,
                      flex: 1,
                    }}
                  >
                    {run.code.split("\n")[0].slice(0, 40) || "empty"}
                  </span>
                  <span
                    style={{
                      fontSize: "10px",
                      color: "#3d5270",
                      flexShrink: 0,
                      whiteSpace: "nowrap",
                    }}
                  >
                    {formatTime(run.created_at)}
                  </span>
                </div>
              ))}
              {totalPages > 1 && (
                <div
                  style={{
                    display: "flex",
                    justifyContent: "center",
                    gap: "8px",
                    padding: "6px 14px",
                    fontSize: "11px",
                  }}
                >
                  <button
                    onClick={() => setPage((p) => Math.max(1, p - 1))}
                    disabled={page <= 1}
                    style={{
                      background: "none",
                      border: "none",
                      color: page <= 1 ? "#2a3a52" : "#4b8cf7",
                      cursor: page <= 1 ? "default" : "pointer",
                      fontFamily: "inherit",
                      fontSize: "11px",
                    }}
                  >
                    Prev
                  </button>
                  <span style={{ color: "#3d5270" }}>
                    {page}/{totalPages}
                  </span>
                  <button
                    onClick={() => setPage((p) => Math.min(totalPages, p + 1))}
                    disabled={page >= totalPages}
                    style={{
                      background: "none",
                      border: "none",
                      color: page >= totalPages ? "#2a3a52" : "#4b8cf7",
                      cursor: page >= totalPages ? "default" : "pointer",
                      fontFamily: "inherit",
                      fontSize: "11px",
                    }}
                  >
                    Next
                  </button>
                </div>
              )}
            </>
          )}
        </div>
      )}
    </div>
  );
}

export default RunHistory;
