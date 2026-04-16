import React, { useMemo } from "react";
import { useChangedKeys } from "../../visuals/useFlash";
import { themeFor } from "../../visuals/visualTheme";

function QueueView({ obj, onMouseDown }) {
  const entries = useMemo(() => {
    const out = {};
    if (Array.isArray(obj?.items)) {
      for (let i = 0; i < obj.items.length; i++) out[i] = obj.items[i];
    }
    return out;
  }, [obj?.items]);
  const changed = useChangedKeys(entries);
  const theme = themeFor("queue");
  const CELL_WIDTH = 76;
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

      <div style={{ position: "relative" }}>
        <div style={{ display: "flex", gap: GAP }}>
          {obj.items.map((value, index) => {
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
                  background: "#131d2e",
                  border: `1px solid ${isFlashing ? theme.flash : theme.border}`,
                  color: isFlashing ? theme.flash : "#c8d8f0",
                  borderRadius: "8px",
                  boxShadow: isFlashing ? `0 0 12px ${theme.flash}33` : "none",
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
        </div>

        {obj.items.length > 0 && (
          <>
            {obj.items.length === 1 ? (
              <div
                style={{
                  position: "absolute",
                  top: -20,
                  left: 0,
                  width: CELL_WIDTH,
                  textAlign: "center",
                  fontSize: "11px",
                  fontWeight: 600,
                  letterSpacing: "0.3px",
                  color: "#f0a429",
                }}
              >
                Front / Rear
              </div>
            ) : (
              <>
                <div
                  style={{
                    position: "absolute",
                    top: -20,
                    left: 0,
                    width: CELL_WIDTH,
                    textAlign: "center",
                    fontSize: "11px",
                    fontWeight: 600,
                    letterSpacing: "0.3px",
                    color: "#f0a429",
                  }}
                >
                  Front
                </div>
                <div
                  style={{
                    position: "absolute",
                    top: -20,
                    left: obj.rearIndex * (CELL_WIDTH + GAP),
                    width: CELL_WIDTH,
                    textAlign: "center",
                    fontSize: "11px",
                    fontWeight: 600,
                    letterSpacing: "0.3px",
                    color: "#4b8cf7",
                  }}
                >
                  Rear
                </div>
              </>
            )}
          </>
        )}
      </div>
    </div>
  );
}

export default QueueView;
