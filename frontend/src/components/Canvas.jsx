import { useState, useRef, useMemo } from "react";
import { buildState } from "../engine/traceEngine";
import VariableView from "./visuals/VariableView";
import ArrayView from "./visuals/ArrayView";
import Array2DView from "./visuals/Array2DView";
import LinkedListView from "./visuals/LinkedListView";
import DoublyLinkedListView from "./visuals/DoublyLinkedListView";
import StackView from "./visuals/StackView";
import QueueView from "./visuals/QueueView";
import HashMapView from "./visuals/HashMapView";
import TreeView from "./visuals/TreeView";
import GraphView from "./visuals/GraphView";

function Canvas({ trace = [], currentStep = 0 }) {
  const [scale, setScale] = useState(1);
  const [offset, setOffset] = useState({ x: 0, y: 0 });
  const [positions, setPositions] = useState({});

  const [draggingId, setDraggingId] = useState(null);
  const [dragStart, setDragStart] = useState({ x: 0, y: 0 });
  const [panning, setPanning] = useState(false);

  const canvasRef = useRef(null);

  const iconButton = {
    width: "32px",
    height: "32px",
    borderRadius: "8px",
    background: "#131d2e",
    border: "1px solid #1e2d42",
    color: "#7b96bf",
    cursor: "pointer",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    padding: 0,
    lineHeight: 1,
    fontSize: "14px",
    fontWeight: 600,
    transition: "all 0.15s ease",
  };

  // ================= BUILD OBJECTS FROM TRACE =================
  const objects = useMemo(
    () => buildState(trace, currentStep, positions),
    [trace, currentStep, positions],
  );

  // ================= DRAG =================
  const handleObjectMouseDown = (e, id) => {
    e.stopPropagation();
    setDraggingId(id);
    setDragStart({ x: e.clientX, y: e.clientY });
  };

  const handleMouseMove = (e) => {
    if (draggingId) {
      const dx = (e.clientX - dragStart.x) / scale;
      const dy = (e.clientY - dragStart.y) / scale;

      setPositions((prev) => {
        const current = prev[draggingId] ?? objects[draggingId];
        if (!current) return prev;

        return {
          ...prev,
          [draggingId]: {
            x: current.x + dx,
            y: current.y + dy,
          },
        };
      });

      setDragStart({ x: e.clientX, y: e.clientY });
    }

    if (panning) {
      setOffset((prev) => ({
        x: prev.x + e.movementX,
        y: prev.y + e.movementY,
      }));
    }
  };

  const handleMouseUp = () => {
    setDraggingId(null);
    setPanning(false);
  };

  // ================= RENDER =================
  return (
    <div
      style={{
        width: "100%",
        height: "100%",
        display: "flex",
        flexDirection: "column",
      }}
    >
      {/* Toolbar */}
      <div
        style={{
          padding: "8px 16px",
          background: "#0e1520",
          borderBottom: "1px solid #1a2535",
          display: "flex",
          gap: "6px",
          alignItems: "center",
        }}
      >
        <span style={{ fontSize: "11px", fontWeight: 700, letterSpacing: "1px", color: "#243347", textTransform: "uppercase", marginRight: "8px" }}>
          AlgoScope
        </span>
        <button
          style={iconButton}
          onClick={() => setScale((s) => Math.min(s + 0.2, 3))}
          title="Zoom in"
        >
          +
        </button>
        <button
          style={iconButton}
          onClick={() => setScale((s) => Math.max(s - 0.2, 0.3))}
          title="Zoom out"
        >
          −
        </button>
        <button
          style={iconButton}
          onClick={() => { setScale(1); setOffset({ x: 0, y: 0 }); }}
          title="Reset view"
        >
          ↺
        </button>
      </div>

      {/* Canvas */}
      <div
        ref={canvasRef}
        onMouseMove={handleMouseMove}
        onMouseUp={handleMouseUp}
        onMouseLeave={handleMouseUp}
        onMouseDown={() => setPanning(true)}
        style={{
          flex: 1,
          overflow: "hidden",
          position: "relative",
          background:
            "radial-gradient(ellipse at 25% 25%, #111c2e 0%, #080d15 65%)",
        }}
      >
        <div
          style={{
            transform: `translate(${offset.x}px, ${offset.y}px) scale(${scale})`,
            transformOrigin: "0 0",
            width: "100%",
            height: "100%",
            position: "relative",
          }}
        >
          {Object.values(objects).map((obj) => {
            if (obj.type === "var")
              return (
                <VariableView
                  key={obj.id}
                  obj={obj}
                  onMouseDown={handleObjectMouseDown}
                />
              );

            if (obj.type === "array" && Array.isArray(obj.data))
              return (
                <ArrayView
                  key={obj.id}
                  obj={obj}
                  onMouseDown={handleObjectMouseDown}
                />
              );

            if (obj.type === "array2d" && Array.isArray(obj.data))
              return (
                <Array2DView
                  key={obj.id}
                  obj={obj}
                  onMouseDown={handleObjectMouseDown}
                />
              );

            if (obj.type === "linkedlist")
              return (
                <LinkedListView
                  key={obj.id}
                  obj={obj}
                  onMouseDown={handleObjectMouseDown}
                  scale={scale}
                />
              );

            if (obj.type === "dll")
              return (
                <DoublyLinkedListView
                  key={obj.id}
                  obj={obj}
                  onMouseDown={handleObjectMouseDown}
                  scale={scale}
                />
              );

            if (obj.type === "stack")
              return (
                <StackView
                  key={obj.id}
                  obj={obj}
                  onMouseDown={handleObjectMouseDown}
                />
              );

            if (obj.type === "queue")
              return (
                <QueueView
                  key={obj.id}
                  obj={obj}
                  onMouseDown={handleObjectMouseDown}
                />
              );

            if (obj.type === "hashmap")
              return (
                <HashMapView
                  key={obj.id}
                  obj={obj}
                  onMouseDown={handleObjectMouseDown}
                />
              );

            if (obj.type === "tree")
              return (
                <TreeView
                  key={obj.id}
                  obj={obj}
                  onMouseDown={handleObjectMouseDown}
                />
              );

            if (obj.type === "graph")
              return (
                <GraphView
                  key={obj.id}
                  obj={obj}
                  onMouseDown={handleObjectMouseDown}
                />
              );

            return null;
          })}
        </div>
      </div>
    </div>
  );
}

export default Canvas;
