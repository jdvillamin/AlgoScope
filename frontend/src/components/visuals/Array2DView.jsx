import React from "react";

function Array2DView({ obj, onMouseDown }) {
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
            color: "#3d5270",
            marginBottom: "10px",
            letterSpacing: "0.8px",
            textTransform: "uppercase",
          }}
        >
          {obj.id}
        </div>

        <div style={{ display: "flex", flexDirection: "column", gap: "6px" }}>
          {obj.data.map((row, rIndex) => (
            <div key={rIndex} style={{ display: "flex", gap: "6px" }}>
              {row.map((v, cIndex) => (
                <div
                  key={cIndex}
                  style={{
                    width: "48px",
                    height: "48px",
                    borderRadius: "8px",
                    background: "#192233",
                    border: "1px solid #243347",
                    color: "#dce7f8",
                    display: "flex",
                    alignItems: "center",
                    justifyContent: "center",
                    fontWeight: 600,
                    fontSize: "14px",
                    fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
                  }}
                >
                  {v ?? "∅"}
                </div>
              ))}
            </div>
          ))}
        </div>
      </div>
    </div>
  );
}

export default Array2DView;
