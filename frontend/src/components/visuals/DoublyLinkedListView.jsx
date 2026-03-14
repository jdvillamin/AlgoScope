import React from "react";

function DoublyLinkedListView({ obj, onMouseDown }) {
  const PREV_WIDTH = 60;
  const VALUE_WIDTH = 80;
  const NEXT_WIDTH = 60;
  const NODE_HEIGHT = 56;
  const GAP = 80;

  const NODE_TOTAL_WIDTH = PREV_WIDTH + VALUE_WIDTH + NEXT_WIDTH;

  const nodeIds = Object.keys(obj.nodes || {});
  const nextLinks = obj.nextLinks || [];
  const prevLinks = obj.prevLinks || [];

  const svgWidth =
    nodeIds.length > 0
      ? nodeIds.length * NODE_TOTAL_WIDTH +
        Math.max(0, nodeIds.length - 1) * GAP
      : NODE_TOTAL_WIDTH;

  const getNodeBaseX = (index) => index * (NODE_TOTAL_WIDTH + GAP);

  const pointerEntries = Object.entries(obj.pointers || {});
  const pointersByTarget = {};

  pointerEntries.forEach(([name, target]) => {
    if (!target || target === "NULL") return;
    if (!nodeIds.includes(target)) return;

    if (!pointersByTarget[target]) {
      pointersByTarget[target] = [];
    }

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
          marginBottom: 12,
          fontSize: 12,
          letterSpacing: 1,
          color: "#8aa2ff",
        }}
      >
        {obj.id}
      </div>

      <div style={{ position: "relative", marginTop: 8 }}>
        <div style={{ display: "flex", gap: `${GAP}px` }}>
          {nodeIds.map((id) => {
            const node = obj.nodes[id];
            return (
              <div
                key={id}
                style={{
                  display: "flex",
                  borderRadius: "10px",
                  overflow: "hidden",
                  background:
                    obj.currentHighlight === id ? "#2d8cff" : "#1f2433",
                  color: "#ffffff",
                  boxShadow: "0 4px 14px rgba(0,0,0,0.4)",
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
                    fontSize: 12,
                    color: "#8aa2ff",
                    borderRight: "1px solid #2f3547",
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
                    borderRight: "1px solid #2f3547",
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
                    fontSize: 12,
                    color: "#8aa2ff",
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
            const POINTER_BASE_Y = 18;
            const POINTER_STACK_GAP = 16;

            const NODE_TOP_IN_SVG = SVG_TOP_OFFSET;
            const CENTER_Y = NODE_TOP_IN_SVG + NODE_HEIGHT / 2;
            const NEXT_Y = CENTER_Y - 8;
            const PREV_Y = CENTER_Y + 8;

            const EDGE_PAD = 2;

            return (
              <>
                {Object.entries(pointersByTarget).flatMap(([target, names]) => {
                  const index = nodeIds.indexOf(target);
                  if (index === -1) return [];

                  const x = getNodeBaseX(index) + NODE_TOTAL_WIDTH / 2;

                  return names.map((name, stackIndex) => {
                    const y = POINTER_BASE_Y + stackIndex * POINTER_STACK_GAP;

                    return (
                      <text
                        key={`${target}-${name}`}
                        x={x}
                        y={y}
                        fill="#fbc531"
                        fontSize="13"
                        fontWeight="600"
                        textAnchor="middle"
                      >
                        {name}
                      </text>
                    );
                  });
                })}

                {nextLinks.map((link, i) => {
                  const fromIndex = nodeIds.indexOf(link.from);
                  const toIndex = nodeIds.indexOf(link.to);
                  if (fromIndex === -1 || toIndex === -1) return null;

                  const fromBaseX = getNodeBaseX(fromIndex);
                  const toBaseX = getNodeBaseX(toIndex);

                  const fromX = fromBaseX + NODE_TOTAL_WIDTH - EDGE_PAD;
                  const toX = toBaseX + EDGE_PAD;

                  return (
                    <line
                      key={`next-${i}`}
                      x1={fromX}
                      y1={NEXT_Y}
                      x2={toX}
                      y2={NEXT_Y}
                      stroke="#8aa2ff"
                      strokeWidth="2"
                      markerEnd="url(#arrow-next)"
                    />
                  );
                })}

                {prevLinks.map((link, i) => {
                  const fromIndex = nodeIds.indexOf(link.from);
                  const toIndex = nodeIds.indexOf(link.to);
                  if (fromIndex === -1 || toIndex === -1) return null;

                  const fromBaseX = getNodeBaseX(fromIndex);
                  const toBaseX = getNodeBaseX(toIndex);

                  const fromX = fromBaseX + EDGE_PAD;
                  const toX = toBaseX + NODE_TOTAL_WIDTH - EDGE_PAD;

                  return (
                    <line
                      key={`prev-${i}`}
                      x1={fromX}
                      y1={PREV_Y}
                      x2={toX}
                      y2={PREV_Y}
                      stroke="#8aa2ff"
                      strokeWidth="2"
                      strokeDasharray="6,4"
                      markerEnd="url(#arrow-prev)"
                    />
                  );
                })}
              </>
            );
          })()}

          <defs>
            <marker
              id="arrow-next"
              markerWidth="10"
              markerHeight="10"
              refX="8"
              refY="5"
              orient="auto"
            >
              <path d="M0,0 L0,10 L8,5 z" fill="#8aa2ff" />
            </marker>

            <marker
              id="arrow-prev"
              markerWidth="10"
              markerHeight="10"
              refX="8"
              refY="5"
              orient="auto"
            >
              <path d="M0,0 L0,10 L8,5 z" fill="#8aa2ff" />
            </marker>
          </defs>
        </svg>
      </div>
    </div>
  );
}

export default DoublyLinkedListView;
