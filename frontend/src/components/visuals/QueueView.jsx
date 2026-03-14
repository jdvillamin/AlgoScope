import React from "react";

function QueueView({ obj, onMouseDown }) {
  const CELL_WIDTH = 80;
  const CELL_HEIGHT = 50;
  const GAP = 12;

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

      <div style={{ position: "relative" }}>
        {/* Cells */}
        <div style={{ display: "flex", gap: GAP }}>
          {obj.items.map((value, index) => (
            <div
              key={index}
              style={{
                width: CELL_WIDTH,
                height: CELL_HEIGHT,
                display: "flex",
                alignItems: "center",
                justifyContent: "center",
                background: "#1f2433",
                color: "#ffffff",
                borderRadius: 8,
                boxShadow: "0 4px 14px rgba(0,0,0,0.4)",
                fontWeight: 600,
              }}
            >
              {value}
            </div>
          ))}
        </div>

        {/* Pointer Labels */}
        {obj.items.length > 0 && (
          <>
            {obj.items.length === 1 ? (
              // 🔥 Single element case
              <div
                style={{
                  position: "absolute",
                  top: -22,
                  left: 0,
                  width: CELL_WIDTH,
                  textAlign: "center",
                  fontSize: 12,
                  fontWeight: 600,
                  color: "#fbc531",
                }}
              >
                FRONT / REAR
              </div>
            ) : (
              <>
                {/* FRONT */}
                <div
                  style={{
                    position: "absolute",
                    top: -22,
                    left: 0,
                    width: CELL_WIDTH,
                    textAlign: "center",
                    fontSize: 12,
                    fontWeight: 600,
                    color: "#fbc531",
                  }}
                >
                  FRONT
                </div>

                {/* REAR */}
                <div
                  style={{
                    position: "absolute",
                    top: -22,
                    left: obj.rearIndex * (CELL_WIDTH + GAP),
                    width: CELL_WIDTH,
                    textAlign: "center",
                    fontSize: 12,
                    fontWeight: 600,
                    color: "#2d8cff",
                  }}
                >
                  REAR
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
