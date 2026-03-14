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
      {/* Container */}
      <div
        style={{
          background: "#1f2433",
          border: "1px solid #2f3547",
          borderRadius: "10px",
          padding: "14px 18px",
          boxShadow: "0 4px 14px rgba(0,0,0,0.4)",
        }}
      >
        {/* Label */}
        <div
          style={{
            fontSize: "12px",
            color: "#8aa2ff",
            marginBottom: "10px",
            letterSpacing: "1px",
          }}
        >
          {obj.id}
        </div>

        {/* Cells */}
        <div style={{ display: "flex", gap: "8px" }}>
          {obj.data.map((v, i) => (
            <div
              key={i}
              style={{
                width: "50px",
                height: "50px",
                borderRadius: "8px",
                background: "#2b3245",
                border: "1px solid #3a435c",
                color: "#ffffff",
                display: "flex",
                alignItems: "center",
                justifyContent: "center",
                fontWeight: "bold",
                fontSize: "15px",
              }}
            >
              {v ?? "∅"}
            </div>
          ))}
        </div>
      </div>
    </div>
  );
}

export default ArrayView;
