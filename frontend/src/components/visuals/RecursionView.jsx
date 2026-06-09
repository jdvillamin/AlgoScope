import React, { useMemo } from "react";
import { useChangedKeys } from "../../visuals/useFlash";
import { themeFor } from "../../visuals/visualTheme";

// A recursion (call) tree. Each function INVOCATION is a rectangular node whose
// parameters are shown as separate partitions (cells), and a directed edge runs
// from each caller to the callee it spawned. The frames still on the call stack
// (root → currently-executing call) are highlighted so the live recursion stack
// reads as a glowing path; frames that have returned are dimmed and show their
// result. Rectangular, partitioned nodes deliberately set this apart from the
// circular nodes used by the tree/graph views.

const HEADER_H = 22;
const CELL_H = 30;
const NODE_H = HEADER_H + CELL_H;
const CELL_W = 44;
const MIN_NODE_W = 48;
const HGAP = 26;
const LEVEL_HEIGHT = 104;

const ACTIVE = "#f0a429"; // executing frame (top of stack)
const STACK = "#3d6fc4"; // caller frames still on the stack
const RETURN = "#5ad6a0"; // returned value accent

function nodeWidth(node) {
  const np = node.params?.length || 0;
  const paramW = np > 0 ? np * CELL_W : MIN_NODE_W;
  const headerW = (node.func?.length || 1) * 8 + 18;
  return Math.max(paramW, headerW, MIN_NODE_W);
}

function RecursionView({ obj, onMouseDown }) {
  const nodes = obj.nodes || {};
  const edges = obj.edges || [];
  const activeId = obj.activeId;
  const theme = themeFor("recursion");

  // Flash a node when it first appears (call) or when it returns.
  const nodeEntries = useMemo(() => {
    const out = {};
    for (const [id, n] of Object.entries(obj.nodes || {})) {
      out[id] = `${n.returned ? 1 : 0}:${n.ret ?? ""}`;
    }
    return out;
  }, [obj.nodes]);
  const changed = useChangedKeys(nodeEntries);

  // ── Width-aware tidy layout ──────────────────────────────────────────────
  // Leaves consume horizontal space left-to-right via a pixel cursor; every
  // parent centers over its children. This keeps variable-width nodes from
  // overlapping (unlike a fixed-slot grid). Computed inline each render, like
  // TreeView/BinaryTreeView.
  const childrenMap = {};
  const childIds = new Set();
  edges.forEach(({ parent, child }) => {
    (childrenMap[parent] = childrenMap[parent] || []).push(child);
    childIds.add(child);
  });
  const roots = Object.keys(nodes).filter((id) => !childIds.has(id));

  const pos = {};
  const placed = new Set();
  let cursor = 0;

  const place = (id, depth) => {
    if (placed.has(id) || !nodes[id]) return;
    placed.add(id);
    const w = nodeWidth(nodes[id]);
    const kids = (childrenMap[id] || []).filter((k) => nodes[k]);
    if (kids.length === 0) {
      pos[id] = { cx: cursor + w / 2, y: depth * LEVEL_HEIGHT };
      cursor += w + HGAP;
      return;
    }
    kids.forEach((k) => place(k, depth + 1));
    const cxs = kids.filter((k) => pos[k]).map((k) => pos[k].cx);
    const cx = cxs.length
      ? (Math.min(...cxs) + Math.max(...cxs)) / 2
      : cursor + w / 2;
    pos[id] = { cx, y: depth * LEVEL_HEIGHT };
    if (cxs.length === 0) cursor += w + HGAP;
  };

  roots.forEach((r) => place(r, 0));
  // Safety net so a node is never invisible if it wasn't reached from a root.
  Object.keys(nodes).forEach((id) => {
    if (!pos[id]) {
      const w = nodeWidth(nodes[id]);
      pos[id] = { cx: cursor + w / 2, y: 0 };
      cursor += w + HGAP;
    }
  });

  let maxX = MIN_NODE_W;
  let maxY = NODE_H;
  Object.keys(pos).forEach((id) => {
    const w = nodeWidth(nodes[id]);
    maxX = Math.max(maxX, pos[id].cx + w / 2);
    maxY = Math.max(maxY, pos[id].y + NODE_H);
  });
  const tightW = maxX + 4;
  const tightH = maxY + 18;

  const arrowId = `rec-arrow-${obj.id}`;
  const stackArrowId = `rec-arrow-stack-${obj.id}`;

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
      <svg
        width={tightW}
        height={tightH}
        style={{ position: "absolute", top: 0, left: 0 }}
      >
        <defs>
          <marker
            id={arrowId}
            viewBox="0 0 10 10"
            refX="8"
            refY="5"
            markerWidth="6"
            markerHeight="6"
            orient="auto-start-reverse"
          >
            <path d="M 0 0 L 10 5 L 0 10 z" fill="#27406a" />
          </marker>
          <marker
            id={stackArrowId}
            viewBox="0 0 10 10"
            refX="8"
            refY="5"
            markerWidth="6"
            markerHeight="6"
            orient="auto-start-reverse"
          >
            <path d="M 0 0 L 10 5 L 0 10 z" fill={ACTIVE} />
          </marker>
        </defs>

        {edges.map((edge, i) => {
          const p = pos[edge.parent];
          const c = pos[edge.child];
          if (!p || !c) return null;
          // An edge whose child has not returned is part of the live call stack.
          const onStack = nodes[edge.child] && !nodes[edge.child].returned;
          return (
            <line
              key={i}
              x1={p.cx}
              y1={p.y + NODE_H}
              x2={c.cx}
              y2={c.y - 2}
              stroke={onStack ? ACTIVE : "#27406a"}
              strokeWidth={onStack ? 2.5 : 1.5}
              markerEnd={`url(#${onStack ? stackArrowId : arrowId})`}
              style={{ transition: "stroke 0.2s ease" }}
            />
          );
        })}
      </svg>

      {Object.entries(pos).map(([id, p]) => {
        const node = nodes[id];
        if (!node) return null;
        const w = nodeWidth(node);
        const isActive = activeId === id;
        const returned = node.returned;
        const onStack = !returned && !isActive;
        const isFlashing = changed.has(id);

        const accent = isActive
          ? ACTIVE
          : onStack
          ? STACK
          : isFlashing
          ? theme.flash
          : "#25324a";
        const bg = isActive ? "#241d0e" : onStack ? "#101d33" : "#0f1622";

        return (
          <div
            key={id}
            style={{
              position: "absolute",
              left: p.cx - w / 2,
              top: p.y,
              width: w,
              height: NODE_H,
              borderRadius: "8px",
              background: bg,
              border: `1.5px solid ${accent}`,
              boxShadow: isActive
                ? `0 0 16px ${ACTIVE}55, 0 4px 14px rgba(0,0,0,0.45)`
                : onStack
                ? `0 0 10px ${STACK}33, 0 4px 14px rgba(0,0,0,0.4)`
                : "0 4px 12px rgba(0,0,0,0.4)",
              opacity: returned ? 0.82 : 1,
              overflow: "visible",
              fontFamily:
                "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
              transition: "all 0.2s ease",
            }}
          >
            {/* Function name header */}
            <div
              style={{
                height: HEADER_H,
                display: "flex",
                alignItems: "center",
                justifyContent: "center",
                fontSize: "12px",
                fontWeight: 700,
                color: isActive
                  ? ACTIVE
                  : onStack
                  ? "#9cc0ff"
                  : "#8aa0c0",
                borderBottom: `1px solid ${accent}55`,
                whiteSpace: "nowrap",
                overflow: "hidden",
                textOverflow: "ellipsis",
                padding: "0 4px",
                boxSizing: "border-box",
              }}
            >
              {node.func}
            </div>

            {/* Parameter partitions */}
            <div style={{ display: "flex", height: CELL_H }}>
              {node.params && node.params.length > 0 ? (
                node.params.map((param, idx) => (
                  <div
                    key={idx}
                    style={{
                      flex: 1,
                      minWidth: 0,
                      display: "flex",
                      flexDirection: "column",
                      alignItems: "center",
                      justifyContent: "center",
                      borderLeft:
                        idx > 0 ? `1px solid ${accent}44` : "none",
                      padding: "1px 2px",
                      boxSizing: "border-box",
                    }}
                  >
                    <span
                      style={{
                        fontSize: "8px",
                        lineHeight: 1,
                        color: "#5d6b86",
                        whiteSpace: "nowrap",
                        overflow: "hidden",
                        textOverflow: "ellipsis",
                        maxWidth: "100%",
                      }}
                    >
                      {param.name}
                    </span>
                    <span
                      style={{
                        fontSize: "13px",
                        fontWeight: 600,
                        lineHeight: 1.1,
                        color: "#dce7f8",
                      }}
                    >
                      {String(param.value)}
                    </span>
                  </div>
                ))
              ) : (
                <div
                  style={{
                    flex: 1,
                    display: "flex",
                    alignItems: "center",
                    justifyContent: "center",
                    fontSize: "12px",
                    color: "#5d6b86",
                  }}
                >
                  ( )
                </div>
              )}
            </div>

            {/* Return value badge */}
            {returned && node.ret !== undefined && (
              <div
                style={{
                  position: "absolute",
                  bottom: -11,
                  left: "50%",
                  transform: "translateX(-50%)",
                  padding: "1px 7px",
                  borderRadius: "8px",
                  background: "#0b1f1a",
                  border: `1px solid ${RETURN}`,
                  color: RETURN,
                  fontSize: "11px",
                  fontWeight: 700,
                  whiteSpace: "nowrap",
                  pointerEvents: "none",
                  zIndex: 3,
                }}
              >
                → {String(node.ret)}
              </div>
            )}
          </div>
        );
      })}
    </div>
  );
}

export default RecursionView;
