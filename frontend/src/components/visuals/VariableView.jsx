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
      {/* Container */}
      <div
        style={{
          background: "#1f2433",
          border: "1px solid #2f3547",
          borderRadius: "10px",
          padding: "12px 18px",
          boxShadow: "0 4px 14px rgba(0,0,0,0.4)",
          minWidth: "120px",
          textAlign: "center",
        }}
      >
        {/* Variable Name */}
        <div
          style={{
            fontSize: "12px",
            color: "#8aa2ff",
            marginBottom: "6px",
            letterSpacing: "1px",
          }}
        >
          {obj.id}
        </div>

        {/* Value */}
        <div
          style={{
            fontSize: "20px",
            fontWeight: "bold",
            color: "#ffffff",
          }}
        >
          {obj.value ?? "∅"}
        </div>
      </div>
    </div>
  );
}

export default VariableView;
