import React, { useMemo } from "react";
import { useChangedKeys } from "../../visuals/useFlash";
import { themeFor } from "../../visuals/visualTheme";
import { chainOrder, latestLinkTargets } from "../../visuals/listLayout";

// Link / glyph palette. Data-structure cards deliberately keep their dark
// styling in both app themes, so these stay literal (see architectural docs).
const LINK = "#3a5a86";
const LINK_DOT = "#6a93c8";
const POINTER = "#f0a429";
const FAINT = "#3d5270";

function LinkedListView({ obj, onMouseDown }) {
  const nodes = obj?.nodes;
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
  const theme = themeFor("list");

  const VALUE_WIDTH = 76;
  const NEXT_WIDTH = 52;
  const NODE_HEIGHT = 52;
  const GAP = 72;
  const NODE_TOTAL_WIDTH = VALUE_WIDTH + NEXT_WIDTH;

  // Vertical bands the SVG overlay claims around the node row: pointer
  // labels and forward arcs live above, backward arcs dip below.
  const TOP_BAND = 64;
  const BOTTOM_BAND = 56;
  const POINTER_BASE_Y = 14;
  const POINTER_STACK_GAP = 15;

  // Live next-pointers (latest assignment wins) and chain-following row order.
  const nextByFrom = latestLinkTargets(obj.links || []);
  const nodeIds = chainOrder(Object.keys(obj.nodes || {}), nextByFrom);
  const idSet = new Set(nodeIds);
  const hasLiveNext = (id) => idSet.has(nextByFrom[id]);

  const svgWidth =
    nodeIds.length > 0
      ? nodeIds.length * NODE_TOTAL_WIDTH + Math.max(0, nodeIds.length - 1) * GAP
      : NODE_TOTAL_WIDTH;

  const getNodeBaseX = (index) => index * (NODE_TOTAL_WIDTH + GAP);
  const getDotX = (index) => getNodeBaseX(index) + VALUE_WIDTH + NEXT_WIDTH / 2;

  const nodeTop = TOP_BAND;
  const nodeBottom = TOP_BAND + NODE_HEIGHT;
  const centerY = TOP_BAND + NODE_HEIGHT / 2;

  const pointerEntries = Object.entries(obj.pointers || {});
  const pointersByTarget = {};
  pointerEntries.forEach(([name, target]) => {
    if (!target || target === "NULL") return;
    if (!idSet.has(target)) return;
    if (!pointersByTarget[target]) pointersByTarget[target] = [];
    pointersByTarget[target].push(name);
  });

  // SVG marker ids are document-global; namespace them per list instance.
  const uid = `${String(obj.id).replace(/[^a-zA-Z0-9_-]/g, "")}-ll`;

  const captionStyle = {
    position: "absolute",
    top: 3,
    left: 0,
    right: 0,
    textAlign: "center",
    fontSize: "8px",
    fontWeight: 600,
    letterSpacing: "0.5px",
    color: FAINT,
    whiteSpace: "nowrap",
    overflow: "hidden",
    textOverflow: "ellipsis",
    padding: "0 4px",
    fontFamily: "Inter, system-ui, sans-serif",
  };

  return (
    <div
      data-viz-id={obj.id}
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
          color: theme.label,
          marginBottom: "10px",
        }}
      >
        {obj.id}
      </div>

      <div style={{ position: "relative", marginTop: 8 }}>
        {nodeIds.length === 0 ? (
          <div
            style={{
              width: "96px",
              height: "40px",
              border: `1px dashed ${theme.border}`,
              borderRadius: "8px",
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              color: FAINT,
              fontSize: "11px",
            }}
          >
            empty
          </div>
        ) : (
          <div style={{ display: "flex", gap: `${GAP}px` }}>
            {nodeIds.map((id) => {
              const node = obj.nodes[id];
              const highlighted = obj.currentHighlight === id;
              const isFlashing = changed.has(id);
              return (
                <div
                  key={id}
                  style={{
                    display: "flex",
                    borderRadius: "10px",
                    overflow: "hidden",
                    background: highlighted ? "#0f2040" : "#131d2e",
                    border: `1px solid ${
                      highlighted ? "#1e3a6e" : isFlashing ? theme.flash : theme.border
                    }`,
                    boxShadow: highlighted
                      ? "0 0 14px rgba(75,140,247,0.2)"
                      : isFlashing
                      ? `0 0 14px ${theme.flash}33, 0 4px 16px rgba(0,0,0,0.4)`
                      : "0 4px 16px rgba(0,0,0,0.4)",
                    transition: "all 0.2s ease",
                  }}
                >
                  <div
                    style={{
                      position: "relative",
                      width: `${VALUE_WIDTH}px`,
                      height: `${NODE_HEIGHT}px`,
                      display: "flex",
                      alignItems: "center",
                      justifyContent: "center",
                      fontWeight: 600,
                      fontSize: "15px",
                      color: highlighted
                        ? "#4b8cf7"
                        : isFlashing
                        ? theme.flash
                        : "#dce7f8",
                      borderRight: `1px solid ${theme.border}`,
                      fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
                    }}
                  >
                    <span style={captionStyle}>{id}</span>
                    {node.value}
                  </div>
                  <div
                    style={{
                      position: "relative",
                      width: `${NEXT_WIDTH}px`,
                      height: `${NODE_HEIGHT}px`,
                      display: "flex",
                      alignItems: "center",
                      justifyContent: "center",
                    }}
                  >
                    <span style={captionStyle}>next</span>
                    {/* The live link renders as an SVG dot + arrow; a missing
                        link is the classic NULL slash. */}
                    {!hasLiveNext(id) && (
                      <span style={{ fontSize: "15px", fontWeight: 500, color: FAINT }}>∅</span>
                    )}
                  </div>
                </div>
              );
            })}
          </div>
        )}

        <svg
          width={svgWidth}
          height={TOP_BAND + NODE_HEIGHT + BOTTOM_BAND}
          style={{
            position: "absolute",
            top: -TOP_BAND,
            left: 0,
            pointerEvents: "none",
            overflow: "visible",
          }}
        >
          <defs>
            {/* refX sits behind the tip so the stroke terminates inside the
                head where it is wider than the line — otherwise the flat
                line end pokes out around the pointed tip. The head extends
                ~3px beyond the path endpoint. */}
            <marker
              id={`${uid}-next`}
              viewBox="0 0 10 8"
              markerWidth="10"
              markerHeight="8"
              refX="7"
              refY="4"
              orient="auto"
              markerUnits="userSpaceOnUse"
            >
              <path d="M0,0 L10,4 L0,8 z" fill={LINK} />
            </marker>
            <marker
              id={`${uid}-ptr`}
              viewBox="0 0 8 7"
              markerWidth="8"
              markerHeight="7"
              refX="5.5"
              refY="3.5"
              orient="auto"
              markerUnits="userSpaceOnUse"
            >
              <path d="M0,0 L8,3.5 L0,7 z" fill={POINTER} />
            </marker>
          </defs>

          {/* Live next links: straight to the right-hand neighbour, arcs over
              the top for forward jumps / self loops, arcs under the row for
              backward links. */}
          {Object.entries(nextByFrom).map(([from, to]) => {
            const fromIndex = nodeIds.indexOf(from);
            const toIndex = nodeIds.indexOf(to);
            if (fromIndex === -1 || toIndex === -1) return null;
            const dotX = getDotX(fromIndex);
            const marker = `url(#${uid}-next)`;
            if (toIndex === fromIndex + 1) {
              return (
                <line
                  key={`link-${from}`}
                  x1={dotX + 5}
                  y1={centerY}
                  x2={getNodeBaseX(toIndex) - 4}
                  y2={centerY}
                  stroke={LINK}
                  strokeWidth="2"
                  markerEnd={marker}
                />
              );
            }
            const span = Math.abs(toIndex - fromIndex);
            const lift = Math.min(22 + span * 6, 42);
            if (toIndex >= fromIndex) {
              const entryX = getNodeBaseX(toIndex) + 18;
              const apexY = nodeTop - lift;
              return (
                <path
                  key={`link-${from}`}
                  d={`M ${dotX} ${centerY - 5} C ${dotX} ${apexY}, ${entryX} ${apexY}, ${entryX} ${nodeTop - 4}`}
                  fill="none"
                  stroke={LINK}
                  strokeWidth="2"
                  markerEnd={marker}
                />
              );
            }
            const entryX = getNodeBaseX(toIndex) + NODE_TOTAL_WIDTH / 2;
            const dipY = nodeBottom + lift;
            return (
              <path
                key={`link-${from}`}
                d={`M ${dotX} ${centerY + 5} C ${dotX} ${dipY}, ${entryX} ${dipY}, ${entryX} ${nodeBottom + 4}`}
                fill="none"
                stroke={LINK}
                strokeWidth="2"
                markerEnd={marker}
              />
            );
          })}

          {/* Pointer-origin dots in the next cells. */}
          {nodeIds.map((id, i) =>
            hasLiveNext(id) ? (
              <circle key={`dot-${id}`} cx={getDotX(i)} cy={centerY} r="3.5" fill={LINK_DOT} />
            ) : null,
          )}

          {/* User pointers (head, curr, ...): stacked gold labels with an
              arrow down to the node they reference. */}
          {Object.entries(pointersByTarget).flatMap(([target, names]) => {
            const index = nodeIds.indexOf(target);
            if (index === -1) return [];
            const x = getNodeBaseX(index) + NODE_TOTAL_WIDTH / 2;
            const lastY = POINTER_BASE_Y + (names.length - 1) * POINTER_STACK_GAP;
            return [
              ...names.map((name, stackIndex) => (
                <text
                  key={`${target}-${name}`}
                  x={x}
                  y={POINTER_BASE_Y + stackIndex * POINTER_STACK_GAP}
                  fill={POINTER}
                  fontSize="12"
                  fontWeight="600"
                  textAnchor="middle"
                  fontFamily="Inter, system-ui, sans-serif"
                >
                  {name}
                </text>
              )),
              <line
                key={`${target}-ptr-arrow`}
                x1={x}
                y1={lastY + 4}
                x2={x}
                y2={nodeTop - 3}
                stroke={POINTER}
                strokeWidth="1.5"
                opacity="0.85"
                markerEnd={`url(#${uid}-ptr)`}
              />,
            ];
          })}
        </svg>
      </div>
    </div>
  );
}

export default LinkedListView;
