import React, { useMemo } from "react";
import { useChangedKeys } from "../../visuals/useFlash";
import { themeFor } from "../../visuals/visualTheme";

function Array2DView({ obj, onMouseDown }) {
  const entries = useMemo(() => {
    const out = {};
    if (Array.isArray(obj?.data)) {
      for (let r = 0; r < obj.data.length; r++) {
        const row = obj.data[r];
        if (!Array.isArray(row)) continue;
        for (let c = 0; c < row.length; c++) out[`${r},${c}`] = row[c];
      }
    }
    return out;
  }, [obj?.data]);
  const changed = useChangedKeys(entries);
  const theme = themeFor("array2d");

  if (!obj || !Array.isArray(obj.data)) return null;

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
          background: "#131d2e",
          border: `1px solid ${theme.border}`,
          borderRadius: "12px",
          padding: "14px 16px",
          boxShadow: "0 4px 20px rgba(0,0,0,0.5)",
        }}
      >
        <div
          style={{
            fontSize: "11px",
            fontWeight: 600,
            color: theme.label,
            marginBottom: "10px",
            letterSpacing: "0.8px",
          }}
        >
          {obj.id}
        </div>

        <div style={{ display: "flex", flexDirection: "column", gap: "6px" }}>
          {obj.data.map((row, rIndex) => (
            <div key={rIndex} style={{ display: "flex", gap: "6px" }}>
              {row.map((v, cIndex) => {
                const isHighlighted =
                  obj.highlightRow === rIndex && obj.highlightCol === cIndex;
                const isFlashing = changed.has(`${rIndex},${cIndex}`);
                return (
                  <div
                    key={cIndex}
                    style={{
                      width: "48px",
                      height: "48px",
                      borderRadius: "8px",
                      background: isHighlighted
                        ? "#1a2a1a"
                        : isFlashing
                        ? "#1c2440"
                        : "#192233",
                      border: isHighlighted
                        ? "1.5px solid #4ade80"
                        : isFlashing
                        ? `1.5px solid ${theme.flash}`
                        : "1px solid #243347",
                      color: isHighlighted
                        ? "#4ade80"
                        : isFlashing
                        ? theme.flash
                        : "#dce7f8",
                      display: "flex",
                      alignItems: "center",
                      justifyContent: "center",
                      fontWeight: 600,
                      fontSize: "14px",
                      fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
                      boxShadow: isHighlighted
                        ? "0 0 12px rgba(74, 222, 128, 0.25)"
                        : isFlashing
                        ? `0 0 12px ${theme.flash}33`
                        : "none",
                      transition: "all 0.2s ease",
                    }}
                  >
                    {v ?? "∅"}
                  </div>
                );
              })}
            </div>
          ))}
        </div>
      </div>
    </div>
  );
}

export default Array2DView;
