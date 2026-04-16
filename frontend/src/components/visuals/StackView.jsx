import React, { useMemo } from "react";
import { useChangedKeys } from "../../visuals/useFlash";
import { themeFor } from "../../visuals/visualTheme";

function StackView({ obj, onMouseDown }) {
  const entries = useMemo(() => {
    const out = {};
    if (Array.isArray(obj?.items)) {
      for (let i = 0; i < obj.items.length; i++) out[i] = obj.items[i];
    }
    return out;
  }, [obj?.items]);
  const changed = useChangedKeys(entries);
  const theme = themeFor("stack");
  const CELL_WIDTH = 96;
  const CELL_HEIGHT = 48;
  const GAP = 6;

  return (
    <div
      data-viz-id={obj.id}
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
          color: theme.label,
          textAlign: "center",
          marginBottom: "10px",
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
        {obj.items.map((value, index) => {
          const isTop = index === obj.topIndex;
          const isFlashing = changed.has(String(index));
          return (
          <div
            key={index}
            style={{
              width: CELL_WIDTH,
              height: CELL_HEIGHT,
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              background: isTop ? "#0f2040" : "#131d2e",
              border: `1px solid ${isTop ? "#1e3a6e" : isFlashing ? theme.flash : theme.border}`,
              color: isTop ? "#4b8cf7" : isFlashing ? theme.flash : "#c8d8f0",
              borderRadius: "8px",
              boxShadow: isTop
                ? "0 0 12px rgba(75,140,247,0.15)"
                : isFlashing
                ? `0 0 12px ${theme.flash}33`
                : "none",
              transition: "all 0.2s ease",
              fontWeight: 600,
              fontSize: "15px",
              fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
            }}
          >
            {value}
          </div>
          );
        })}

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
