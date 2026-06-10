import React, { useMemo } from "react";
import { useChangedKeys } from "../../visuals/useFlash";
import { themeFor } from "../../visuals/visualTheme";

// Distinct colors so each pointer label (x, y, T2, curr, …) reads as its own
// thing — letting students follow rotation pivots at a glance.
const POINTER_COLORS = [
  "#f0a429",
  "#4fc9d9",
  "#e586b8",
  "#63d188",
  "#b29bff",
  "#f5944a",
  "#7ab8ff",
  "#eb7785",
];

// Red-black tree node fills. The node's semantic color always shows as the
// fill; highlight/flash are expressed through the border + glow so the
// red/black reading is never lost mid-traversal.
const RB_STYLES = {
  R: { bg: "#7f1d1d", border: "#ef4444", text: "#fecaca" },
  B: { bg: "#0b0f14", border: "#566176", text: "#dce7f8" },
};

// Hash the name to a palette slot so a given pointer keeps the same color across
// every step (stable, not order-dependent).
function colorForPointer(name) {
  let h = 0;
  for (let i = 0; i < name.length; i++) {
    h = (h * 31 + name.charCodeAt(i)) >>> 0;
  }
  return POINTER_COLORS[h % POINTER_COLORS.length];
}

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

  // Roots = nodes that are no other node's left/right child. We lay out a
  // FOREST, not just one root: during construction the nodes are created before
  // any edges, so every node is parentless and must still be drawn. Each
  // parentless node lays out at depth 0 (a row); as edges are added, children
  // drop under their parents and the tree assembles.
  const childIds = new Set();
  Object.values(nodes).forEach((n) => {
    if (n.left) childIds.add(n.left);
    if (n.right) childIds.add(n.right);
  });
  const roots = Object.keys(nodes).filter((id) => !childIds.has(id));

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

  roots.forEach((rootId) => layout(rootId, 0));

  // Safety net: place any node not reached from a root (e.g. a malformed
  // cycle) so a created node is never invisible.
  Object.keys(nodes).forEach((id) => {
    if (!positioned[id]) {
      positioned[id] = { x: counter * HORIZONTAL_SPACING, y: 0 };
      counter++;
    }
  });

  // Edges derived from each node's left/right pointers.
  const edges = [];
  Object.values(nodes).forEach((n) => {
    if (n.left && positioned[n.left]) edges.push({ parent: n.id, child: n.left });
    if (n.right && positioned[n.right])
      edges.push({ parent: n.id, child: n.right });
  });

  // Named pointer labels attached to nodes, grouped by the node they target.
  // Stale labels (target missing/null/deleted) are dropped.
  const pointersByTarget = {};
  Object.entries(obj.pointers || {}).forEach(([name, target]) => {
    if (!target || target === "NULL") return;
    if (!positioned[target]) return;
    if (!pointersByTarget[target]) pointersByTarget[target] = [];
    pointersByTarget[target].push(name);
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
        const rb = RB_STYLES[nodes[id].color] || null;
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
              background: rb ? rb.bg : highlighted ? "#0f2040" : "#131d2e",
              border: rb
                ? `2px solid ${
                    highlighted ? "#4b8cf7" : isFlashing ? theme.flash : rb.border
                  }`
                : `1px solid ${
                    highlighted ? "#1e3a6e" : isFlashing ? theme.flash : "#1e2d42"
                  }`,
              boxShadow: highlighted
                ? "0 0 14px rgba(75,140,247,0.35)"
                : isFlashing
                ? `0 0 14px ${theme.flash}33, 0 4px 14px rgba(0,0,0,0.4)`
                : "0 4px 14px rgba(0,0,0,0.4)",
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              color: rb
                ? isFlashing
                  ? theme.flash
                  : rb.text
                : highlighted
                ? "#4b8cf7"
                : isFlashing
                ? theme.flash
                : "#dce7f8",
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

      {Object.entries(pointersByTarget).flatMap(([target, names]) => {
        const pos = positioned[target];
        if (!pos) return [];
        return names.map((name, stackIndex) => {
          const color = colorForPointer(name);
          return (
            <div
              key={`${target}-${name}`}
              style={{
                position: "absolute",
                left: pos.x + NODE_SIZE - 4,
                top: pos.y - 12 + stackIndex * 20,
                padding: "1px 6px",
                borderRadius: "6px",
                background: `${color}22`,
                border: `1px solid ${color}`,
                color,
                fontSize: "11px",
                fontWeight: 700,
                fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
                whiteSpace: "nowrap",
                pointerEvents: "none",
                zIndex: 5,
              }}
            >
              {name}
            </div>
          );
        });
      })}
    </div>
  );
}

export default BinaryTreeView;
