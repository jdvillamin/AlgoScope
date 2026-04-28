import React, { useMemo } from "react";
import { useChangedKeys } from "../../visuals/useFlash";
import { themeFor } from "../../visuals/visualTheme";

const CELL = 48;
const CELL_BORDER = 1;
const CELL_GAP = 6;
const CARD_PADDING_X = 16;
const CARD_PADDING_Y = 14;
const CARD_BORDER = 1;
const LABEL_HEIGHT = 16;
const LABEL_MARGIN = 10;
const MARKER_HEIGHT = 18;

const BAR_WIDTH = 24;
const BAR_GAP = 3;
const BAR_MAX_HEIGHT = 160;
const BAR_AREA_PADDING = 12;

const MARKER_COLORS = [
  "#f59e0b", "#38bdf8", "#a78bfa", "#f472b6", "#34d399", "#fb923c", "#818cf8",
];

function buildIndexMarkers(cellMarkers) {
  if (!cellMarkers) return {};
  const byIndex = {};
  for (const [varName, idx] of Object.entries(cellMarkers)) {
    const key = String(idx);
    if (!byIndex[key]) byIndex[key] = [];
    byIndex[key].push(varName);
  }
  return byIndex;
}

function markerColor(varName, cellMarkers) {
  const names = Object.keys(cellMarkers || {}).sort();
  return MARKER_COLORS[names.indexOf(varName) % MARKER_COLORS.length];
}

// eslint-disable-next-line react-refresh/only-export-components
export function estimateArraySize(obj) {
  const n = Array.isArray(obj?.data) ? obj.data.length : 0;
  const hasMarkers = obj?.cellMarkers && Object.keys(obj.cellMarkers).length > 0;
  const markerExtra = hasMarkers ? MARKER_HEIGHT : 0;
  if (obj?.display === "bars") {
    const barOuter = BAR_WIDTH + BAR_GAP;
    const rowWidth = n === 0 ? 0 : n * barOuter - BAR_GAP;
    const w = rowWidth + BAR_AREA_PADDING * 2 + CARD_PADDING_X * 2 + CARD_BORDER * 2;
    const h = LABEL_HEIGHT + LABEL_MARGIN + BAR_MAX_HEIGHT + BAR_AREA_PADDING + markerExtra + CARD_PADDING_Y * 2 + CARD_BORDER * 2;
    return { w, h };
  }
  const cellOuter = CELL + CELL_BORDER * 2;
  const rowWidth = n === 0 ? 0 : n * cellOuter + (n - 1) * CELL_GAP;
  const w = rowWidth + CARD_PADDING_X * 2 + CARD_BORDER * 2;
  const h =
    LABEL_HEIGHT +
    LABEL_MARGIN +
    cellOuter +
    markerExtra +
    CARD_PADDING_Y * 2 +
    CARD_BORDER * 2;
  return { w, h };
}

function ArrayView({ obj, onMouseDown }) {
  const entries = useMemo(() => {
    const out = {};
    if (Array.isArray(obj?.data)) {
      for (let i = 0; i < obj.data.length; i++) out[i] = obj.data[i];
    }
    return out;
  }, [obj?.data]);
  const changed = useChangedKeys(entries);
  const theme = themeFor("array");

  const isBars = obj?.display === "bars";
  const maxVal = useMemo(() => {
    if (!isBars || !Array.isArray(obj?.data)) return 1;
    let m = 0;
    for (const v of obj.data) {
      const n = typeof v === "number" ? Math.abs(v) : (parseInt(v, 10) || 0);
      if (n > m) m = n;
    }
    return m || 1;
  }, [isBars, obj?.data]);

  const indexMarkers = useMemo(
    () => buildIndexMarkers(obj?.cellMarkers),
    [obj?.cellMarkers]
  );

  if (!obj || !Array.isArray(obj.data)) return null;

  const hasMarkers = obj.cellMarkers && Object.keys(obj.cellMarkers).length > 0;

  const renderMarkerRow = (index) => {
    const vars = indexMarkers[String(index)];
    if (!vars || vars.length === 0) return null;
    return (
      <div style={{ display: "flex", justifyContent: "center", gap: "2px", marginTop: "3px", minHeight: `${MARKER_HEIGHT - 3}px` }}>
        {vars.map((v) => (
          <span
            key={v}
            style={{
              fontSize: "9px",
              fontWeight: 700,
              fontFamily: "'JetBrains Mono', monospace",
              color: markerColor(v, obj.cellMarkers),
              lineHeight: 1,
              padding: "1px 3px",
              borderRadius: "3px",
              background: `${markerColor(v, obj.cellMarkers)}18`,
              whiteSpace: "nowrap",
            }}
          >
            {v}
          </span>
        ))}
      </div>
    );
  };

  const renderEmptyMarkerRow = () => {
    if (!hasMarkers) return null;
    return <div style={{ minHeight: `${MARKER_HEIGHT - 3}px`, marginTop: "3px" }} />;
  };

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

        {isBars ? (
          <div>
            <div style={{ display: "flex", alignItems: "flex-end", gap: `${BAR_GAP}px`, height: `${BAR_MAX_HEIGHT}px`, padding: `0 ${BAR_AREA_PADDING}px` }}>
              {obj.data.map((v, i) => {
                const numVal = typeof v === "number" ? v : (parseInt(v, 10) || 0);
                const barH = Math.max(4, (Math.abs(numVal) / maxVal) * (BAR_MAX_HEIGHT - 20));
                const isHighlighted = obj.highlightIndex === i;
                const hasCell = indexMarkers[String(i)];
                const isFlashing = changed.has(String(i));
                return (
                  <div
                    key={i}
                    style={{
                      display: "flex",
                      flexDirection: "column",
                      alignItems: "center",
                      justifyContent: "flex-end",
                      height: "100%",
                    }}
                  >
                    <span
                      style={{
                        fontSize: "10px",
                        fontWeight: 600,
                        fontFamily: "'JetBrains Mono', monospace",
                        color: isHighlighted ? "#4ade80" : hasCell ? markerColor(indexMarkers[String(i)][0], obj.cellMarkers) : isFlashing ? theme.flash : "#8fa3c8",
                        marginBottom: "4px",
                      }}
                    >
                      {v ?? ""}
                    </span>
                    <div
                      style={{
                        width: `${BAR_WIDTH}px`,
                        height: `${barH}px`,
                        borderRadius: "4px 4px 2px 2px",
                        background: isHighlighted
                          ? "linear-gradient(180deg, #4ade80 0%, #166534 100%)"
                          : hasCell
                          ? `linear-gradient(180deg, ${markerColor(indexMarkers[String(i)][0], obj.cellMarkers)} 0%, #1e3a6e 100%)`
                          : isFlashing
                          ? `linear-gradient(180deg, ${theme.flash} 0%, #1e3a6e 100%)`
                          : "linear-gradient(180deg, #4b8cf7 0%, #1e3a6e 100%)",
                        border: isHighlighted
                          ? "1px solid #4ade80"
                          : hasCell
                          ? `1px solid ${markerColor(indexMarkers[String(i)][0], obj.cellMarkers)}`
                          : isFlashing
                          ? `1px solid ${theme.flash}`
                          : "1px solid #2a5090",
                        boxShadow: isHighlighted
                          ? "0 0 12px rgba(74, 222, 128, 0.3)"
                          : hasCell
                          ? `0 0 10px ${markerColor(indexMarkers[String(i)][0], obj.cellMarkers)}44`
                          : isFlashing
                          ? `0 0 10px ${theme.flash}44`
                          : "0 2px 8px rgba(30, 58, 110, 0.3)",
                        transition: "height 0.25s ease, background 0.2s ease, box-shadow 0.2s ease",
                      }}
                    />
                  </div>
                );
              })}
            </div>
            {hasMarkers && (
              <div style={{ display: "flex", gap: `${BAR_GAP}px`, padding: `0 ${BAR_AREA_PADDING}px` }}>
                {obj.data.map((_, i) => (
                  <div key={i} style={{ width: `${BAR_WIDTH}px`, textAlign: "center" }}>
                    {indexMarkers[String(i)] ? renderMarkerRow(i) : renderEmptyMarkerRow()}
                  </div>
                ))}
              </div>
            )}
          </div>
        ) : (
          <div>
            <div style={{ display: "flex", gap: "6px" }}>
              {obj.data.map((v, i) => {
                const isHighlighted = obj.highlightIndex === i;
                const hasCell = indexMarkers[String(i)];
                const isFlashing = changed.has(String(i));
                const cellColor = hasCell ? markerColor(indexMarkers[String(i)][0], obj.cellMarkers) : null;
                return (
                  <div
                    key={i}
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
                );
              })}
            </div>
            {hasMarkers && (
              <div style={{ display: "flex", gap: "6px" }}>
                {obj.data.map((_, i) => (
                  <div key={i} style={{ width: "48px", textAlign: "center" }}>
                    {indexMarkers[String(i)] ? renderMarkerRow(i) : renderEmptyMarkerRow()}
                  </div>
                ))}
              </div>
            )}
          </div>
        )}
      </div>
    </div>
  );
}

export default ArrayView;
