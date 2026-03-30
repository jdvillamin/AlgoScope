import React from "react";

function VariableView({ obj, onMouseDown }) {
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
          padding: "14px 20px",
          boxShadow: "0 4px 20px rgba(0,0,0,0.5)",
          minWidth: "100px",
          textAlign: "center",
        }}
      >
        <div
          style={{
            fontSize: "11px",
            fontWeight: 600,
            color: "#506888",
            marginBottom: "8px",
            letterSpacing: "0.8px",
            textTransform: "uppercase",
          }}
        >
          {obj.id}
        </div>
        <div
          style={{
            fontSize: "22px",
            fontWeight: 700,
            color: "#dce7f8",
            fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
          }}
        >
          {obj.value ?? "∅"}
        </div>
      </div>
    </div>
  );
}

export default VariableView;
