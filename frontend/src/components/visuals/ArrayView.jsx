import React from "react";

function ArrayView({ obj, onMouseDown }) {
  if (!obj || !Array.isArray(obj.data)) return null;

  return (
    <div
      onMouseDown={(e) => onMouseDown(e, obj.id)}
      style={{
        position: "absolute",
        left: obj.x,
        top: obj.y,
        cursor: "move",
        userSelect: "none",
      }}
    >
      <div
        style={{
          background: "#131d2e",
          border: "1px solid #1e2d42",
          borderRadius: "12px",
          padding: "14px 16px",
          boxShadow: "0 4px 20px rgba(0,0,0,0.5)",
        }}
      >
        <div
          style={{
            fontSize: "11px",
            fontWeight: 600,
            color: "#506888",
            marginBottom: "10px",
            letterSpacing: "0.8px",
            textTransform: "uppercase",
          }}
        >
          {obj.id}
        </div>

        <div style={{ display: "flex", gap: "6px" }}>
          {obj.data.map((v, i) => {
            const isHighlighted = obj.highlightIndex === i;
            return (
              <div
                key={i}
                style={{
                  width: "48px",
                  height: "48px",
                  borderRadius: "8px",
                  background: isHighlighted ? "#1a2a1a" : "#192233",
                  border: isHighlighted ? "1.5px solid #4ade80" : "1px solid #243347",
                  color: isHighlighted ? "#4ade80" : "#dce7f8",
                  display: "flex",
                  alignItems: "center",
                  justifyContent: "center",
                  fontWeight: 600,
                  fontSize: "14px",
                  fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
                  boxShadow: isHighlighted ? "0 0 12px rgba(74, 222, 128, 0.25)" : "none",
                  transition: "all 0.15s ease",
                }}
              >
                {v ?? "∅"}
              </div>
            );
          })}
        </div>
      </div>
    </div>
  );
}

export default ArrayView;
