import { useState, useEffect, useCallback } from "react";
import { useAuth } from "../contexts/useAuth";
import { listCodes, createCode, deleteCode } from "../api/codes";

function SavedCodes({ onLoadCode, currentCode, currentName }) {
  const { user } = useAuth();
  const [codes, setCodes] = useState([]);
  const [expanded, setExpanded] = useState(false);
  const [saving, setSaving] = useState(false);
  const [error, setError] = useState("");

  const refresh = useCallback(() => {
    if (!user) return;
    listCodes().then(setCodes).catch(() => {});
  }, [user]);

  useEffect(() => {
    if (expanded && user) refresh();
  }, [expanded, user, refresh]);

  const handleSave = async () => {
    if (!currentCode?.trim()) return;
    setSaving(true);
    setError("");
    try {
      await createCode(currentName || "Untitled", currentCode);
      refresh();
    } catch (err) {
      const msgs = err.response?.data?.errors;
      setError(msgs ? msgs.join(" ") : "Failed to save.");
    } finally {
      setSaving(false);
    }
  };

  const handleDelete = async (e, id) => {
    e.stopPropagation();
    try {
      await deleteCode(id);
      setCodes((prev) => prev.filter((c) => c.id !== id));
    } catch {
      // ignore
    }
  };

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
        Cloud Saves
      </div>

      {expanded && (
        <div>
          <div style={{ padding: "0 8px 6px" }}>
            <button
              onClick={handleSave}
              disabled={saving || !currentCode?.trim()}
              style={{
                width: "100%",
                padding: "6px 10px",
                borderRadius: "6px",
                border: "1px solid #1e3a6e",
                background: "#0f1e3a",
                color: saving ? "#506888" : "#4b8cf7",
                fontSize: "11.5px",
                fontWeight: 600,
                cursor: saving ? "default" : "pointer",
                fontFamily: "inherit",
              }}
            >
              {saving ? "Saving..." : "Save current file"}
            </button>
            {error && (
              <div style={{ fontSize: "11px", color: "#f87171", marginTop: "4px", padding: "0 2px" }}>
                {error}
              </div>
            )}
          </div>

          {codes.length === 0 ? (
            <div
              style={{
                padding: "6px 14px",
                fontSize: "11.5px",
                color: "#3d5270",
                fontStyle: "italic",
              }}
            >
              No saved files yet
            </div>
          ) : (
            codes.map((code) => (
              <div
                key={code.id}
                onClick={() => onLoadCode(code)}
                style={{
                  padding: "6px 14px",
                  margin: "1px 6px",
                  borderRadius: "6px",
                  cursor: "pointer",
                  display: "flex",
                  alignItems: "center",
                  justifyContent: "space-between",
                  gap: "6px",
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
                    overflow: "hidden",
                    textOverflow: "ellipsis",
                    whiteSpace: "nowrap",
                    minWidth: 0,
                  }}
                >
                  {code.title}
                </span>
                <span
                  onClick={(e) => handleDelete(e, code.id)}
                  style={{
                    fontSize: "14px",
                    color: "#3d5270",
                    cursor: "pointer",
                    lineHeight: 1,
                    padding: "0 2px",
                    flexShrink: 0,
                  }}
                  title="Delete saved file"
                >
                  ×
                </span>
              </div>
            ))
          )}
        </div>
      )}
    </div>
  );
}

export default SavedCodes;
