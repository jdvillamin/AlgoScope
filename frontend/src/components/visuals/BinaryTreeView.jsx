import React, { useMemo } from "react";
import { useChangedKeys } from "../../visuals/useFlash";
import { themeFor } from "../../visuals/visualTheme";

function BinaryTreeView({ obj, onMouseDown }) {
  const NODE_SIZE = 48;
  const LEVEL_HEIGHT = 110;
  const HORIZONTAL_SPACING = 90;

  const nodes = obj.nodes;

  const nodeEntries = useMemo(() => {
    const out = {};
    if (nodes) {
      for (const [id, node] of Object.entries(nodes)) {
        out[id] = node?.value;
      }
    }
    return out;
  }, [nodes]);
  const changed = useChangedKeys(nodeEntries);
  const theme = themeFor("btree");

  // Root = the node that is no other node's left/right child.
  const childIds = new Set();
  Object.values(nodes).forEach((n) => {
    if (n.left) childIds.add(n.left);
    if (n.right) childIds.add(n.right);
  });
  const rootId =
    Object.keys(nodes).find((id) => !childIds.has(id)) ??
    Object.keys(nodes)[0];

  // In-order x assignment: each node gets the next horizontal slot between its
  // left and right subtrees. This is what makes a left-only child render to the
  // left of its parent and a right-only child to the right — the distinguishing
  // visual property of a binary tree. y is the depth.
  const positioned = {};
  const visited = new Set();
  let counter = 0;

  function layout(nodeId, depth) {
    if (!nodeId || !nodes[nodeId] || visited.has(nodeId)) return;
    visited.add(nodeId);
    const node = nodes[nodeId];
    layout(node.left, depth + 1);
    positioned[nodeId] = {
      x: counter * HORIZONTAL_SPACING,
      y: depth * LEVEL_HEIGHT,
    };
    counter++;
    layout(node.right, depth + 1);
  }

  if (rootId) layout(rootId, 0);

  // Edges derived from each node's left/right pointers.
  const edges = [];
  Object.values(nodes).forEach((n) => {
    if (n.left && positioned[n.left]) edges.push({ parent: n.id, child: n.left });
    if (n.right && positioned[n.right])
      edges.push({ parent: n.id, child: n.right });
  });

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
        const isFlashing = changed.has(id);
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
              border: `1px solid ${
                highlighted ? "#1e3a6e" : isFlashing ? theme.flash : "#1e2d42"
              }`,
              boxShadow: highlighted
                ? "0 0 14px rgba(75,140,247,0.2)"
                : isFlashing
                ? `0 0 14px ${theme.flash}33, 0 4px 14px rgba(0,0,0,0.4)`
                : "0 4px 14px rgba(0,0,0,0.4)",
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              color: highlighted ? "#4b8cf7" : isFlashing ? theme.flash : "#dce7f8",
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

export default BinaryTreeView;
