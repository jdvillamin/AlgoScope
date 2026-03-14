import React, { useState } from "react";

function GraphView({ obj, onMouseDown }) {
  const NODE_SIZE = 50;
  const NODE_RADIUS = NODE_SIZE / 2;

  const WIDTH = 600;
  const HEIGHT = 450;

  const CENTER_X = WIDTH / 2;
  const CENTER_Y = HEIGHT / 2;
  const RADIUS = 150;

  const nodeIds = Object.keys(obj.nodes);

  const createInitialPosition = (index, total) => {
    const angle = (2 * Math.PI * index) / total;
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

  const getPosition = (id, index) => {
    return positions[id] || createInitialPosition(index, nodeIds.length);
  };

  // ================= DRAG =================
  const handleMouseMove = (e) => {
    if (!dragging) return;

    const rect = e.currentTarget.getBoundingClientRect();
    const mouseX = e.clientX - rect.left;
    const mouseY = e.clientY - rect.top;

    const x = mouseX - dragOffset.x;
    const y = mouseY - dragOffset.y;

    setPositions((prev) => ({
      ...prev,
      [dragging]: { x, y },
    }));
  };

  const handleMouseUp = () => setDragging(null);

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
      <svg
        width={WIDTH}
        height={HEIGHT}
        onMouseMove={handleMouseMove}
        onMouseUp={handleMouseUp}
      >
        {/* Arrow definition */}
        <defs>
          <marker
            id="arrow"
            viewBox="0 0 10 10"
            refX="9"
            refY="5"
            markerWidth="6"
            markerHeight="6"
            orient="auto-start-reverse"
          >
            <path d="M 0 0 L 10 5 L 0 10 z" fill="#8aa2ff" />
          </marker>
        </defs>

        {/* ================= EDGES ================= */}
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

          const offsetX = (dx / length) * NODE_RADIUS;
          const offsetY = (dy / length) * NODE_RADIUS;

          return (
            <line
              key={i}
              x1={from.x + offsetX}
              y1={from.y + offsetY}
              x2={to.x - offsetX}
              y2={to.y - offsetY}
              stroke="#8aa2ff"
              strokeWidth="2"
              markerEnd="url(#arrow)"
            />
          );
        })}

        {/* ================= NODES ================= */}
        {nodeIds.map((id, i) => {
          const pos = getPosition(id, i);

          return (
            <g
              key={id}
              onMouseDown={(e) => {
                e.stopPropagation();

                const rect =
                  e.currentTarget.ownerSVGElement.getBoundingClientRect();
                const mouseX = e.clientX - rect.left;
                const mouseY = e.clientY - rect.top;

                setDragOffset({
                  x: mouseX - pos.x,
                  y: mouseY - pos.y,
                });

                setDragging(id);
              }}
              style={{ cursor: "grab" }}
            >
              <circle
                cx={pos.x}
                cy={pos.y}
                r={NODE_RADIUS}
                fill={obj.currentHighlight === id ? "#2d8cff" : "#1f2433"}
                stroke="#8aa2ff"
                strokeWidth="2"
              />
              <text
                x={pos.x}
                y={pos.y + 5}
                textAnchor="middle"
                fill="#ffffff"
                fontWeight="600"
                fontSize="14"
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
