import React, { useState } from "react";

function GraphView({ obj, onMouseDown }) {
  const NODE_SIZE = 48;
  const NODE_RADIUS = NODE_SIZE / 2;

  const WIDTH = 600;
  const HEIGHT = 440;
  const CENTER_X = WIDTH / 2;
  const CENTER_Y = HEIGHT / 2;
  const RADIUS = 145;

  const nodeIds = Object.keys(obj.nodes);

  const createInitialPosition = (index, total) => {
    const angle = (2 * Math.PI * index) / total - Math.PI / 2;
    return {
      x: CENTER_X + RADIUS * Math.cos(angle),
      y: CENTER_Y + RADIUS * Math.sin(angle),
    };
  };

  const [positions, setPositions] = useState(() => {
    const map = {};
    nodeIds.forEach((id, i) => {
      map[id] = createInitialPosition(i, nodeIds.length);
    });
    return map;
  });

  const [dragging, setDragging] = useState(null);
  const [dragOffset, setDragOffset] = useState({ x: 0, y: 0 });

  const getPosition = (id, index) =>
    positions[id] || createInitialPosition(index, nodeIds.length);

  const handleMouseMove = (e) => {
    if (!dragging) return;
    const rect = e.currentTarget.getBoundingClientRect();
    setPositions((prev) => ({
      ...prev,
      [dragging]: {
        x: e.clientX - rect.left - dragOffset.x,
        y: e.clientY - rect.top - dragOffset.y,
      },
    }));
  };

  const handleMouseUp = () => setDragging(null);

  return (
    <div
      data-viz-id={obj.id}
      onMouseDown={(e) => onMouseDown(e, obj.id)}
      style={{ position: "absolute", left: obj.x, top: obj.y, cursor: "move", userSelect: "none" }}
    >
      <svg
        width={WIDTH}
        height={HEIGHT}
        onMouseMove={handleMouseMove}
        onMouseUp={handleMouseUp}
      >
        <defs>
          <marker
            id="graph-arrow"
            viewBox="0 0 10 10"
            refX="9"
            refY="5"
            markerWidth="6"
            markerHeight="6"
            orient="auto-start-reverse"
          >
            <path d="M 0 0 L 10 5 L 0 10 z" fill="#2a4060" />
          </marker>
        </defs>

        {/* Edges */}
        {obj.edges.map((edge, i) => {
          const fromIndex = nodeIds.indexOf(edge.from);
          const toIndex = nodeIds.indexOf(edge.to);
          const from = getPosition(edge.from, fromIndex);
          const to = getPosition(edge.to, toIndex);
          if (!from || !to) return null;

          const dx = to.x - from.x;
          const dy = to.y - from.y;
          const length = Math.sqrt(dx * dx + dy * dy);
          if (length === 0) return null;

          const ux = dx / length;
          const uy = dy / length;

          return (
            <line
              key={i}
              x1={from.x + ux * NODE_RADIUS}
              y1={from.y + uy * NODE_RADIUS}
              x2={to.x - ux * NODE_RADIUS}
              y2={to.y - uy * NODE_RADIUS}
              stroke="#1e2d42"
              strokeWidth="2"
              markerEnd="url(#graph-arrow)"
            />
          );
        })}

        {/* Nodes */}
        {nodeIds.map((id, i) => {
          const pos = getPosition(id, i);
          const highlighted = obj.currentHighlight === id;

          return (
            <g
              key={id}
              onMouseDown={(e) => {
                e.stopPropagation();
                const rect = e.currentTarget.ownerSVGElement.getBoundingClientRect();
                setDragOffset({
                  x: e.clientX - rect.left - pos.x,
                  y: e.clientY - rect.top - pos.y,
                });
                setDragging(id);
              }}
              style={{ cursor: "grab" }}
            >
              <circle
                cx={pos.x}
                cy={pos.y}
                r={NODE_RADIUS}
                fill={highlighted ? "#0f2040" : "#131d2e"}
                stroke={highlighted ? "#1e3a6e" : "#1e2d42"}
                strokeWidth="1.5"
                style={{
                  filter: highlighted ? "drop-shadow(0 0 8px rgba(75,140,247,0.3))" : "none",
                  transition: "all 0.2s ease",
                }}
              />
              <text
                x={pos.x}
                y={pos.y + 5}
                textAnchor="middle"
                fill={highlighted ? "#4b8cf7" : "#dce7f8"}
                fontWeight="600"
                fontSize="14"
                fontFamily="'JetBrains Mono', 'Fira Code', 'Consolas', monospace"
                pointerEvents="none"
              >
                {id}
              </text>
            </g>
          );
        })}
      </svg>
    </div>
  );
}

export default GraphView;
