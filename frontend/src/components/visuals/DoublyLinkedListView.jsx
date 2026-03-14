import React from "react";

function DoublyLinkedListView({ obj, onMouseDown }) {
  const PREV_WIDTH = 52;
  const VALUE_WIDTH = 76;
  const NEXT_WIDTH = 52;
  const NODE_HEIGHT = 52;
  const GAP = 72;

  const NODE_TOTAL_WIDTH = PREV_WIDTH + VALUE_WIDTH + NEXT_WIDTH;

  const nodeIds = Object.keys(obj.nodes || {});
  const nextLinks = obj.nextLinks || [];
  const prevLinks = obj.prevLinks || [];

  const svgWidth =
    nodeIds.length > 0
      ? nodeIds.length * NODE_TOTAL_WIDTH + Math.max(0, nodeIds.length - 1) * GAP
      : NODE_TOTAL_WIDTH;

  const getNodeBaseX = (index) => index * (NODE_TOTAL_WIDTH + GAP);

  const pointerEntries = Object.entries(obj.pointers || {});
  const pointersByTarget = {};
  pointerEntries.forEach(([name, target]) => {
    if (!target || target === "NULL") return;
    if (!nodeIds.includes(target)) return;
    if (!pointersByTarget[target]) pointersByTarget[target] = [];
    pointersByTarget[target].push(name);
  });

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
          color: "#3d5270",
          marginBottom: "10px",
          textTransform: "uppercase",
        }}
      >
        {obj.id}
      </div>

      <div style={{ position: "relative", marginTop: 8 }}>
        <div style={{ display: "flex", gap: `${GAP}px` }}>
          {nodeIds.map((id) => {
            const node = obj.nodes[id];
            const highlighted = obj.currentHighlight === id;
            return (
              <div
                key={id}
                style={{
                  display: "flex",
                  borderRadius: "10px",
                  overflow: "hidden",
                  background: highlighted ? "#0f2040" : "#131d2e",
                  border: `1px solid ${highlighted ? "#1e3a6e" : "#1e2d42"}`,
                  boxShadow: highlighted ? "0 0 14px rgba(75,140,247,0.2)" : "0 4px 16px rgba(0,0,0,0.4)",
                  transition: "all 0.2s ease",
                }}
              >
                <div
                  style={{
                    width: `${PREV_WIDTH}px`,
                    height: `${NODE_HEIGHT}px`,
                    display: "flex",
                    alignItems: "center",
                    justifyContent: "center",
                    fontSize: "11px",
                    fontWeight: 500,
                    color: "#2a3d56",
                    borderRight: "1px solid #1e2d42",
                    letterSpacing: "0.3px",
                  }}
                >
                  prev
                </div>
                <div
                  style={{
                    width: `${VALUE_WIDTH}px`,
                    height: `${NODE_HEIGHT}px`,
                    display: "flex",
                    alignItems: "center",
                    justifyContent: "center",
                    fontWeight: 600,
                    fontSize: "15px",
                    color: highlighted ? "#4b8cf7" : "#dce7f8",
                    borderRight: "1px solid #1e2d42",
                    fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
                  }}
                >
                  {node.value}
                </div>
                <div
                  style={{
                    width: `${NEXT_WIDTH}px`,
                    height: `${NODE_HEIGHT}px`,
                    display: "flex",
                    alignItems: "center",
                    justifyContent: "center",
                    fontSize: "11px",
                    fontWeight: 500,
                    color: "#2a3d56",
                    letterSpacing: "0.3px",
                  }}
                >
                  next
                </div>
              </div>
            );
          })}
        </div>

        <svg
          width={svgWidth}
          height={NODE_HEIGHT + 110}
          style={{
            position: "absolute",
            top: -60,
            left: 0,
            pointerEvents: "none",
            overflow: "visible",
          }}
        >
          {(() => {
            const SVG_TOP_OFFSET = 60;
            const POINTER_BASE_Y = 16;
            const POINTER_STACK_GAP = 16;
            const CENTER_Y = SVG_TOP_OFFSET + NODE_HEIGHT / 2;
            const NEXT_Y = CENTER_Y - 8;
            const PREV_Y = CENTER_Y + 8;
            const EDGE_PAD = 2;

            return (
              <>
                {Object.entries(pointersByTarget).flatMap(([target, names]) => {
                  const index = nodeIds.indexOf(target);
                  if (index === -1) return [];
                  const x = getNodeBaseX(index) + NODE_TOTAL_WIDTH / 2;
                  return names.map((name, stackIndex) => (
                    <text
                      key={`${target}-${name}`}
                      x={x}
                      y={POINTER_BASE_Y + stackIndex * POINTER_STACK_GAP}
                      fill="#f0a429"
                      fontSize="12"
                      fontWeight="600"
                      textAnchor="middle"
                      fontFamily="Inter, system-ui, sans-serif"
                    >
                      {name}
                    </text>
                  ));
                })}

                {nextLinks.map((link, i) => {
                  const fromIndex = nodeIds.indexOf(link.from);
                  const toIndex = nodeIds.indexOf(link.to);
                  if (fromIndex === -1 || toIndex === -1) return null;
                  return (
                    <line
                      key={`next-${i}`}
                      x1={getNodeBaseX(fromIndex) + NODE_TOTAL_WIDTH - EDGE_PAD}
                      y1={NEXT_Y}
                      x2={getNodeBaseX(toIndex) + EDGE_PAD}
                      y2={NEXT_Y}
                      stroke="#2a4060"
                      strokeWidth="2"
                      markerEnd="url(#arrow-next)"
                    />
                  );
                })}

                {prevLinks.map((link, i) => {
                  const fromIndex = nodeIds.indexOf(link.from);
                  const toIndex = nodeIds.indexOf(link.to);
                  if (fromIndex === -1 || toIndex === -1) return null;
                  return (
                    <line
                      key={`prev-${i}`}
                      x1={getNodeBaseX(fromIndex) + EDGE_PAD}
                      y1={PREV_Y}
                      x2={getNodeBaseX(toIndex) + NODE_TOTAL_WIDTH - EDGE_PAD}
                      y2={PREV_Y}
                      stroke="#1e3a6e"
                      strokeWidth="2"
                      strokeDasharray="5,4"
                      markerEnd="url(#arrow-prev)"
                    />
                  );
                })}
              </>
            );
          })()}

          <defs>
            <marker id="arrow-next" markerWidth="10" markerHeight="10" refX="8" refY="5" orient="auto">
              <path d="M0,0 L0,10 L8,5 z" fill="#2a4060" />
            </marker>
            <marker id="arrow-prev" markerWidth="10" markerHeight="10" refX="8" refY="5" orient="auto">
              <path d="M0,0 L0,10 L8,5 z" fill="#1e3a6e" />
            </marker>
          </defs>
        </svg>
      </div>
    </div>
  );
}

export default DoublyLinkedListView;
