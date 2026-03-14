import React from "react";

function HashMapView({ obj, onMouseDown }) {
  const BUCKET_WIDTH = 70;
  const BUCKET_HEIGHT = 40;

  const ENTRY_WIDTH = 130;
  const ENTRY_HEIGHT = 40;

  const ROW_GAP = 50;
  const CHAIN_GAP = 40;

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
      {/* Title */}
      <div
        style={{
          marginBottom: 20,
          fontSize: 12,
          letterSpacing: 1,
          color: "#8aa2ff",
        }}
      >
        {obj.id} (size = {bucketIds.length})
      </div>

      <div style={{ position: "relative" }}>
        {bucketIds.map((index, row) => {
          const entries = obj.buckets[index];
          const bucketY = row * (BUCKET_HEIGHT + ROW_GAP);

          return (
            <div key={index}>
              {/* Bucket Cell */}
              <div
                style={{
                  position: "absolute",
                  top: bucketY,
                  left: 0,
                  width: BUCKET_WIDTH,
                  height: BUCKET_HEIGHT,
                  background: "#2a3142",
                  borderRadius: "8px",
                  display: "flex",
                  alignItems: "center",
                  justifyContent: "center",
                  color: "#ffffff",
                  fontWeight: 600,
                }}
              >
                {index}
              </div>

              {/* Entries (Horizontal Chain) */}
              {entries.map((entry, i) => {
                const entryX =
                  BUCKET_WIDTH + 60 + i * (ENTRY_WIDTH + CHAIN_GAP);

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
                      background: "#1f2433",
                      boxShadow: "0 4px 12px rgba(0,0,0,0.4)",
                      display: "flex",
                      overflow: "hidden",
                    }}
                  >
                    {/* KEY */}
                    <div
                      style={{
                        flex: 1,
                        background: "#2d8cff",
                        display: "flex",
                        alignItems: "center",
                        justifyContent: "center",
                        fontWeight: 700,
                        color: "#ffffff",
                      }}
                    >
                      {entry.key}
                    </div>

                    {/* Divider */}
                    <div
                      style={{
                        width: "2px",
                        background: "#2f3547",
                      }}
                    />

                    {/* VALUE */}
                    <div
                      style={{
                        flex: 1,
                        display: "flex",
                        alignItems: "center",
                        justifyContent: "center",
                        color: "#e5e7eb",
                        fontWeight: 500,
                      }}
                    >
                      {entry.value}
                    </div>
                  </div>
                );
              })}

              {/* SVG Arrows */}
              <svg
                style={{
                  position: "absolute",
                  top: 0,
                  left: 0,
                  pointerEvents: "none",
                }}
                width={1000}
                height={1000}
              >
                {/* Arrow from bucket → first entry */}
                {entries.length > 0 && (
                  <line
                    x1={BUCKET_WIDTH}
                    y1={bucketY + BUCKET_HEIGHT / 2}
                    x2={BUCKET_WIDTH + 60}
                    y2={bucketY + BUCKET_HEIGHT / 2}
                    stroke="#8aa2ff"
                    strokeWidth="2"
                    markerEnd="url(#arrow-right)"
                  />
                )}

                {/* Chain arrows */}
                {entries.map((_, i) => {
                  if (i === entries.length - 1) return null;

                  const x1 =
                    BUCKET_WIDTH +
                    60 +
                    i * (ENTRY_WIDTH + CHAIN_GAP) +
                    ENTRY_WIDTH;

                  const x2 =
                    BUCKET_WIDTH + 60 + (i + 1) * (ENTRY_WIDTH + CHAIN_GAP);

                  const y = bucketY + BUCKET_HEIGHT / 2;

                  return (
                    <line
                      key={i}
                      x1={x1}
                      y1={y}
                      x2={x2}
                      y2={y}
                      stroke="#8aa2ff"
                      strokeWidth="2"
                      markerEnd="url(#arrow-right)"
                    />
                  );
                })}

                <defs>
                  <marker
                    id="arrow-right"
                    markerWidth="10"
                    markerHeight="10"
                    refX="8"
                    refY="5"
                    orient="auto"
                  >
                    <path d="M0,0 L10,5 L0,10 z" fill="#8aa2ff" />
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
