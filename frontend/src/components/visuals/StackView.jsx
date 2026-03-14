import React from "react";

function StackView({ obj, onMouseDown }) {
  const CELL_WIDTH = 100;
  const CELL_HEIGHT = 50;
  const GAP = 8;

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
      {/* Title */}
      <div
        style={{
          marginBottom: 12,
          fontSize: 12,
          letterSpacing: 1,
          color: "#8aa2ff",
          textAlign: "center",
        }}
      >
        {obj.id}
      </div>

      {/* Stack Container */}
      <div
        style={{
          position: "relative",
          display: "flex",
          flexDirection: "column-reverse",
          gap: GAP,
        }}
      >
        {/* Stack Cells */}
        {obj.items.map((value, index) => (
          <div
            key={index}
            style={{
              width: CELL_WIDTH,
              height: CELL_HEIGHT,
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              background: index === obj.topIndex ? "#2d8cff" : "#1f2433",
              color: "#ffffff",
              borderRadius: 8,
              boxShadow: "0 4px 14px rgba(0,0,0,0.4)",
              transition: "all 0.2s ease",
              fontWeight: 600,
            }}
          >
            {value}
          </div>
        ))}

        {/* 🔥 TOP Label (Corrected Position Logic) */}
        {obj.topIndex >= 0 && (
          <div
            style={{
              position: "absolute",
              bottom: obj.topIndex * (CELL_HEIGHT + GAP) + CELL_HEIGHT + 6,
              left: 0,
              width: CELL_WIDTH,
              textAlign: "center",
              fontSize: 12,
              color: "#fbc531",
              fontWeight: 600,
            }}
          >
            TOP
          </div>
        )}
      </div>
    </div>
  );
}

export default StackView;
