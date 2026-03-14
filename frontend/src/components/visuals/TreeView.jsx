import React from "react";

function TreeView({ obj, onMouseDown }) {
  const NODE_SIZE = 50;
  const LEVEL_HEIGHT = 120;
  const HORIZONTAL_SPACING = 100;

  const nodes = obj.nodes;
  const edges = obj.edges;

  // Build parent → children map
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
      positioned[nodeId] = {
        x: currentX * HORIZONTAL_SPACING,
        y: depth * LEVEL_HEIGHT,
      };
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

  return (
    <div
      onMouseDown={(e) => onMouseDown(e, obj.id)}
      style={{
        position: "absolute",
        left: obj.x,
        top: obj.y,
        cursor: "move",
      }}
    >
      <svg width={800} height={600} style={{ position: "absolute" }}>
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
              stroke="#8aa2ff"
              strokeWidth="2"
            />
          );
        })}
      </svg>

      {Object.entries(positioned).map(([id, pos]) => (
        <div
          key={id}
          style={{
            position: "absolute",
            left: pos.x,
            top: pos.y,
            width: NODE_SIZE,
            height: NODE_SIZE,
            borderRadius: "50%",
            background: obj.currentHighlight === id ? "#2d8cff" : "#1f2433",
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
            color: "#fff",
            fontWeight: 600,
            boxShadow: "0 4px 12px rgba(0,0,0,0.4)",
          }}
        >
          {nodes[id].value}
        </div>
      ))}
    </div>
  );
}

export default TreeView;
