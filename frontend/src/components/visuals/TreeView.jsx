import React from "react";

function TreeView({ obj, onMouseDown }) {
  const NODE_SIZE = 48;
  const LEVEL_HEIGHT = 110;
  const HORIZONTAL_SPACING = 90;

  const nodes = obj.nodes;
  const edges = obj.edges;

  const childrenMap = {};
  edges.forEach(({ parent, child }) => {
    if (!childrenMap[parent]) childrenMap[parent] = [];
    childrenMap[parent].push(child);
  });

  const rootId = Object.keys(nodes)[0];
  const positioned = {};
  let currentX = 0;

  function layout(nodeId, depth) {
    const children = childrenMap[nodeId] || [];
    if (children.length === 0) {
      positioned[nodeId] = { x: currentX * HORIZONTAL_SPACING, y: depth * LEVEL_HEIGHT };
      currentX++;
    } else {
      const startX = currentX;
      children.forEach((child) => layout(child, depth + 1));
      const endX = currentX - 1;
      positioned[nodeId] = {
        x: ((startX + endX) / 2) * HORIZONTAL_SPACING,
        y: depth * LEVEL_HEIGHT,
      };
    }
  }

  if (rootId) layout(rootId, 0);

  // Tight bbox of all node centers so the root div has a real measurable size.
  const nodeXs = Object.values(positioned).map((p) => p.x);
  const nodeYs = Object.values(positioned).map((p) => p.y);
  const tightW = nodeXs.length ? Math.max(...nodeXs) + NODE_SIZE : NODE_SIZE;
  const tightH = nodeYs.length ? Math.max(...nodeYs) + NODE_SIZE : NODE_SIZE;

  return (
    <div
      data-viz-id={obj.id}
      onMouseDown={(e) => onMouseDown(e, obj.id)}
      style={{
        position: "absolute",
        left: obj.x,
        top: obj.y,
        width: tightW,
        height: tightH,
        cursor: "move",
      }}
    >
      <svg width={tightW} height={tightH} style={{ position: "absolute", top: 0, left: 0 }}>
        {edges.map((edge, i) => {
          const p = positioned[edge.parent];
          const c = positioned[edge.child];
          if (!p || !c) return null;
          return (
            <line
              key={i}
              x1={p.x + NODE_SIZE / 2}
              y1={p.y + NODE_SIZE}
              x2={c.x + NODE_SIZE / 2}
              y2={c.y}
              stroke="#1e2d42"
              strokeWidth="2"
            />
          );
        })}
      </svg>

      {Object.entries(positioned).map(([id, pos]) => {
        const highlighted = obj.currentHighlight === id;
        return (
          <div
            key={id}
            style={{
              position: "absolute",
              left: pos.x,
              top: pos.y,
              width: NODE_SIZE,
              height: NODE_SIZE,
              borderRadius: "50%",
              background: highlighted ? "#0f2040" : "#131d2e",
              border: `1px solid ${highlighted ? "#1e3a6e" : "#1e2d42"}`,
              boxShadow: highlighted ? "0 0 14px rgba(75,140,247,0.2)" : "0 4px 14px rgba(0,0,0,0.4)",
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              color: highlighted ? "#4b8cf7" : "#dce7f8",
              fontWeight: 600,
              fontSize: "14px",
              fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
              transition: "all 0.2s ease",
            }}
          >
            {nodes[id].value}
          </div>
        );
      })}
    </div>
  );
}

export default TreeView;
