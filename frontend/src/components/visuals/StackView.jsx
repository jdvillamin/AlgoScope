import React from "react";

function StackView({ obj, onMouseDown }) {
  const CELL_WIDTH = 96;
  const CELL_HEIGHT = 48;
  const GAP = 6;

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
          fontSize: "11px",
          fontWeight: 600,
          letterSpacing: "0.8px",
          color: "#506888",
          textAlign: "center",
          marginBottom: "10px",
          textTransform: "uppercase",
        }}
      >
        {obj.id}
      </div>

      <div
        style={{
          position: "relative",
          display: "flex",
          flexDirection: "column-reverse",
          gap: GAP,
        }}
      >
        {obj.items.map((value, index) => (
          <div
            key={index}
            style={{
              width: CELL_WIDTH,
              height: CELL_HEIGHT,
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              background: index === obj.topIndex ? "#0f2040" : "#131d2e",
              border: `1px solid ${index === obj.topIndex ? "#1e3a6e" : "#1e2d42"}`,
              color: index === obj.topIndex ? "#4b8cf7" : "#c8d8f0",
              borderRadius: "8px",
              boxShadow: index === obj.topIndex ? "0 0 12px rgba(75,140,247,0.15)" : "none",
              transition: "all 0.2s ease",
              fontWeight: 600,
              fontSize: "15px",
              fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
            }}
          >
            {value}
          </div>
        ))}

        {obj.topIndex >= 0 && (
          <div
            style={{
              position: "absolute",
              bottom: obj.topIndex * (CELL_HEIGHT + GAP) + CELL_HEIGHT + 5,
              left: 0,
              width: CELL_WIDTH,
              textAlign: "center",
              fontSize: "11px",
              fontWeight: 600,
              letterSpacing: "0.5px",
              color: "#f0a429",
            }}
          >
            Top
          </div>
        )}
      </div>
    </div>
  );
}

export default StackView;
