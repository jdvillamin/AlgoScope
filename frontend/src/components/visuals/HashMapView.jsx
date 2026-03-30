import React from "react";

function HashMapView({ obj, onMouseDown }) {
  const BUCKET_WIDTH = 64;
  const BUCKET_HEIGHT = 40;
  const ENTRY_WIDTH = 120;
  const ENTRY_HEIGHT = 40;
  const ROW_GAP = 48;
  const CHAIN_GAP = 36;

  const bucketIds = Object.keys(obj.buckets);

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
          marginBottom: "14px",
          textTransform: "uppercase",
        }}
      >
        {obj.id} <span style={{ color: "#3d5270", fontWeight: 500 }}>({bucketIds.length} buckets)</span>
      </div>

      <div style={{ position: "relative" }}>
        {bucketIds.map((index, row) => {
          const entries = obj.buckets[index];
          const bucketY = row * (BUCKET_HEIGHT + ROW_GAP);

          return (
            <div key={index}>
              {/* Bucket index cell */}
              <div
                style={{
                  position: "absolute",
                  top: bucketY,
                  left: 0,
                  width: BUCKET_WIDTH,
                  height: BUCKET_HEIGHT,
                  background: "#131d2e",
                  border: "1px solid #1e2d42",
                  borderRadius: "8px",
                  display: "flex",
                  alignItems: "center",
                  justifyContent: "center",
                  color: "#647e9c",
                  fontWeight: 600,
                  fontSize: "13px",
                  fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
                }}
              >
                {index}
              </div>

              {/* Entry chain */}
              {entries.map((entry, i) => {
                const entryX = BUCKET_WIDTH + 52 + i * (ENTRY_WIDTH + CHAIN_GAP);
                return (
                  <div
                    key={i}
                    style={{
                      position: "absolute",
                      top: bucketY,
                      left: entryX,
                      width: ENTRY_WIDTH,
                      height: ENTRY_HEIGHT,
                      borderRadius: "8px",
                      border: "1px solid #1e2d42",
                      background: "#131d2e",
                      boxShadow: "0 2px 10px rgba(0,0,0,0.3)",
                      display: "flex",
                      overflow: "hidden",
                    }}
                  >
                    <div
                      style={{
                        flex: 1,
                        background: "#0f2040",
                        display: "flex",
                        alignItems: "center",
                        justifyContent: "center",
                        fontWeight: 600,
                        fontSize: "13px",
                        color: "#4b8cf7",
                        fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
                      }}
                    >
                      {entry.key}
                    </div>
                    <div style={{ width: "1px", background: "#1e2d42" }} />
                    <div
                      style={{
                        flex: 1,
                        display: "flex",
                        alignItems: "center",
                        justifyContent: "center",
                        color: "#c8d8f0",
                        fontWeight: 500,
                        fontSize: "13px",
                        fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
                      }}
                    >
                      {entry.value}
                    </div>
                  </div>
                );
              })}

              {/* SVG arrows */}
              <svg
                style={{ position: "absolute", top: 0, left: 0, pointerEvents: "none" }}
                width={1200}
                height={1200}
              >
                {entries.length > 0 && (
                  <line
                    x1={BUCKET_WIDTH}
                    y1={bucketY + BUCKET_HEIGHT / 2}
                    x2={BUCKET_WIDTH + 52}
                    y2={bucketY + BUCKET_HEIGHT / 2}
                    stroke="#2a4060"
                    strokeWidth="1.5"
                    markerEnd="url(#hm-arrow)"
                  />
                )}
                {entries.map((_, i) => {
                  if (i === entries.length - 1) return null;
                  const x1 = BUCKET_WIDTH + 52 + i * (ENTRY_WIDTH + CHAIN_GAP) + ENTRY_WIDTH;
                  const x2 = BUCKET_WIDTH + 52 + (i + 1) * (ENTRY_WIDTH + CHAIN_GAP);
                  const y = bucketY + BUCKET_HEIGHT / 2;
                  return (
                    <line key={i} x1={x1} y1={y} x2={x2} y2={y}
                      stroke="#2a4060" strokeWidth="1.5" markerEnd="url(#hm-arrow)"
                    />
                  );
                })}
                <defs>
                  <marker id="hm-arrow" markerWidth="8" markerHeight="8" refX="7" refY="4" orient="auto">
                    <path d="M0,0 L8,4 L0,8 z" fill="#2a4060" />
                  </marker>
                </defs>
              </svg>
            </div>
          );
        })}
      </div>
    </div>
  );
}

export default HashMapView;
