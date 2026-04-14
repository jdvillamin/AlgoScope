import { useState, useRef, useMemo, useEffect, useCallback } from "react";
import { buildState } from "../engine/traceEngine";
import { greedyLayout, optimalLayout } from "../engine/layout";
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

  // Manual positions: items the user dragged (or that were pinned by an
  // Optimal-fit click). These override the greedy auto-layout.
  const [manualPositions, setManualPositions] = useState({});

  // Measured bounding boxes per object id.
  const [sizes, setSizes] = useState({});

  // Available canvas width (logical, ignoring zoom).
  const [canvasWidth, setCanvasWidth] = useState(1200);

  const [draggingId, setDraggingId] = useState(null);
  const [dragStart, setDragStart] = useState({ x: 0, y: 0 });
  const [panning, setPanning] = useState(false);

  const canvasRef = useRef(null);
  const worldRef = useRef(null);

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

  // ================= GREEDY AUTO-LAYOUT =================
  // First pass: build state with current positions to know which ids exist
  // and in what order they were introduced.
  const baseObjects = useMemo(
    () => buildState(trace, currentStep, manualPositions),
    [trace, currentStep, manualPositions],
  );

  // Insertion order is preserved by buildState (it iterates the trace).
  const orderedIds = useMemo(() => Object.keys(baseObjects), [baseObjects]);

  // Run the greedy packer using whatever sizes we currently know about.
  const autoPositions = useMemo(() => {
    const items = orderedIds.map((id) => ({
      id,
      w: sizes[id]?.w ?? 0,
      h: sizes[id]?.h ?? 0,
    }));
    return greedyLayout(items, manualPositions, canvasWidth);
  }, [orderedIds, sizes, manualPositions, canvasWidth]);

  // Final positions = manual ⊕ auto. Re-run buildState so the visuals see the
  // resolved x/y. Manual takes precedence on overlap.
  const objects = useMemo(() => {
    const merged = { ...autoPositions, ...manualPositions };
    return buildState(trace, currentStep, merged);
  }, [trace, currentStep, autoPositions, manualPositions]);

  // ================= MEASUREMENT =================
  // One ResizeObserver watches every visual via [data-viz-id]. Re-attach
  // whenever the set of object ids changes.
  const idsKey = orderedIds.join("|");

  const handleResize = useCallback((entries) => {
    setSizes((prev) => {
      let next = prev;
      let changed = false;
      for (const entry of entries) {
        const id = entry.target.getAttribute("data-viz-id");
        if (!id) continue;
        const { width, height } = entry.contentRect;
        const cur = next[id];
        if (!cur || Math.abs(cur.w - width) > 0.5 || Math.abs(cur.h - height) > 0.5) {
          if (next === prev) next = { ...prev };
          next[id] = { w: width, h: height };
          changed = true;
        }
      }
      return changed ? next : prev;
    });
  }, []);

  useEffect(() => {
    const root = worldRef.current;
    if (!root) return;
    const els = root.querySelectorAll("[data-viz-id]");
    if (els.length === 0) return;
    const ro = new ResizeObserver(handleResize);
    els.forEach((el) => ro.observe(el));
    return () => ro.disconnect();
  }, [idsKey, handleResize]);

  // Drop sizes for objects that no longer exist.
  useEffect(() => {
    setSizes((prev) => {
      const next = {};
      let changed = false;
      for (const id of orderedIds) {
        if (prev[id]) next[id] = prev[id];
      }
      for (const id of Object.keys(prev)) {
        if (!(id in next)) changed = true;
      }
      if (Object.keys(next).length !== Object.keys(prev).length) changed = true;
      return changed ? next : prev;
    });
    setManualPositions((prev) => {
      const next = {};
      let changed = false;
      for (const id of orderedIds) {
        if (prev[id]) next[id] = prev[id];
      }
      if (Object.keys(next).length !== Object.keys(prev).length) changed = true;
      return changed ? next : prev;
    });
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [idsKey]);

  // Track canvas width via ResizeObserver.
  useEffect(() => {
    const el = canvasRef.current;
    if (!el) return;
    const ro = new ResizeObserver((entries) => {
      for (const entry of entries) {
        const w = entry.contentRect.width;
        if (w > 0) setCanvasWidth(w);
      }
    });
    ro.observe(el);
    return () => ro.disconnect();
  }, []);

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

      setManualPositions((prev) => {
        const cur = prev[draggingId] ?? objects[draggingId];
        if (!cur) return prev;
        return {
          ...prev,
          [draggingId]: { x: cur.x + dx, y: cur.y + dy },
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

  // ================= LAYOUT BUTTONS =================
  const handleOptimalFit = () => {
    const items = orderedIds.map((id) => ({
      id,
      w: sizes[id]?.w ?? 0,
      h: sizes[id]?.h ?? 0,
    }));
    const positions = optimalLayout(items, canvasWidth);
    // Pin all items to the optimal positions so the result sticks across
    // future size changes until the user resets.
    setManualPositions(positions);
  };

  const handleResetLayout = () => {
    setManualPositions({});
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
          height: "44px",
          padding: "0 16px",
          background: "#0e1520",
          borderBottom: "1px solid #1a2535",
          display: "flex",
          gap: "6px",
          alignItems: "center",
          boxSizing: "border-box",
        }}
      >
        <span style={{ fontSize: "11px", fontWeight: 700, letterSpacing: "1px", color: "#3d5270", textTransform: "uppercase", marginRight: "8px" }}>
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
          title="Reset view (zoom & pan)"
        >
          ↺
        </button>

        <div style={{ width: 1, height: 20, background: "#1a2535", margin: "0 4px" }} />

        <button
          style={{ ...iconButton, width: "auto", padding: "0 12px", fontSize: "12px" }}
          onClick={handleOptimalFit}
          title="Optimal fit (DP shelf packing)"
        >
          ⊞ Optimal fit
        </button>
        <button
          style={{ ...iconButton, width: "auto", padding: "0 12px", fontSize: "12px" }}
          onClick={handleResetLayout}
          title="Reset layout — unpin all objects, return to greedy auto-layout"
        >
          ⤺ Reset layout
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
          ref={worldRef}
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
