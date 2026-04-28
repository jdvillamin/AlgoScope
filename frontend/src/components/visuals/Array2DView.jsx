import React, { useMemo } from "react";
import { useChangedKeys } from "../../visuals/useFlash";
import { themeFor } from "../../visuals/visualTheme";

const MARKER_COLORS = [
  "#f59e0b", "#38bdf8", "#a78bfa", "#f472b6", "#34d399", "#fb923c", "#818cf8",
];

function markerColor2d(varName, cellMarkers) {
  const names = Object.keys(cellMarkers || {}).sort();
  return MARKER_COLORS[names.indexOf(varName) % MARKER_COLORS.length];
}

function buildCellMarkers2d(cellMarkers) {
  if (!cellMarkers) return {};
  const byCell = {};
  for (const [varName, pos] of Object.entries(cellMarkers)) {
    const key = `${pos.r},${pos.c}`;
    if (!byCell[key]) byCell[key] = [];
    byCell[key].push(varName);
  }
  return byCell;
}

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

  const cellMarkersMap = useMemo(
    () => buildCellMarkers2d(obj?.cellMarkers),
    [obj?.cellMarkers]
  );

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
                const cellKey = `${rIndex},${cIndex}`;
                const vars = cellMarkersMap[cellKey];
                const hasCell = vars && vars.length > 0;
                const cellColor = hasCell ? markerColor2d(vars[0], obj.cellMarkers) : null;
                return (
                  <div key={cIndex} style={{ position: "relative" }}>
                    <div
                      style={{
                        width: "48px",
                        height: "48px",
                        borderRadius: "8px",
                        background: isHighlighted
                          ? "#1a2a1a"
                          : hasCell
                          ? `${cellColor}15`
                          : isFlashing
                          ? "#1c2440"
                          : "#192233",
                        border: isHighlighted
                          ? "1.5px solid #4ade80"
                          : hasCell
                          ? `1.5px solid ${cellColor}`
                          : isFlashing
                          ? `1.5px solid ${theme.flash}`
                          : "1px solid #243347",
                        color: isHighlighted
                          ? "#4ade80"
                          : hasCell
                          ? cellColor
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
                          : hasCell
                          ? `0 0 8px ${cellColor}33`
                          : isFlashing
                          ? `0 0 12px ${theme.flash}33`
                          : "none",
                        transition: "all 0.2s ease",
                      }}
                    >
                      {v ?? "∅"}
                    </div>
                    {hasCell && (
                      <div style={{
                        position: "absolute",
                        top: "-8px",
                        left: "50%",
                        transform: "translateX(-50%)",
                        display: "flex",
                        gap: "1px",
                      }}>
                        {vars.map((vn) => (
                          <span
                            key={vn}
                            style={{
                              fontSize: "8px",
                              fontWeight: 700,
                              fontFamily: "'JetBrains Mono', monospace",
                              color: markerColor2d(vn, obj.cellMarkers),
                              lineHeight: 1,
                              padding: "1px 3px",
                              borderRadius: "3px",
                              background: `${markerColor2d(vn, obj.cellMarkers)}22`,
                              whiteSpace: "nowrap",
                            }}
                          >
                            {vn}
                          </span>
                        ))}
                      </div>
                    )}
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
