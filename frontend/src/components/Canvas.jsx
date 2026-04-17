import { useState, useRef, useMemo, useEffect, useCallback } from "react";
import { buildState } from "../engine/traceEngine";
import { optimalLayout } from "../engine/layout";

const LAYOUT_PADDING = 24;
import VariableView from "./visuals/VariableView";
import ArrayView, { estimateArraySize } from "./visuals/ArrayView";
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

  // Manual positions: items the user dragged. Override greedy placement.
  const [manualPositions, setManualPositions] = useState({});

  // Append-only greedy positions: once an id is placed, it never moves on its
  // own. New ids drop into the next free shelf slot as their size is measured.
  const [greedyPositions, setGreedyPositions] = useState({});

  // Continuous optimal-fit mode. When on, positions come from optimalLayout
  // every render and objects are allowed to jump around.
  const [optimalMode, setOptimalMode] = useState(false);

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

  // Append-only greedy placement. For each id in orderedIds: if already placed,
  // just advance the cursor past it; if new and sized, place it at the cursor
  // (wrapping to a new shelf when it won't fit). Recomputing the cursor from
  // scratch keeps this idempotent under strict-mode double invocation.
  useEffect(() => {
    setGreedyPositions((prev) => {
      const next = { ...prev };
      let mutated = false;
      for (const id of Object.keys(next)) {
        if (!orderedIds.includes(id)) {
          delete next[id];
          mutated = true;
        }
      }
      let cursor = { x: LAYOUT_PADDING, y: LAYOUT_PADDING, shelfH: 0 };
      for (const id of orderedIds) {
        const sz = sizes[id];
        if (next[id]) {
          if (!sz) continue;
          const p = next[id];
          if (p.y > cursor.y) cursor = { x: LAYOUT_PADDING, y: p.y, shelfH: 0 };
          cursor.x = Math.max(cursor.x, p.x + sz.w + LAYOUT_PADDING);
          cursor.shelfH = Math.max(cursor.shelfH, sz.h);
          continue;
        }
        if (!sz || sz.w === 0) continue;
        if (cursor.x > LAYOUT_PADDING && cursor.x + sz.w + LAYOUT_PADDING > canvasWidth) {
          cursor = {
            x: LAYOUT_PADDING,
            y: cursor.y + cursor.shelfH + LAYOUT_PADDING,
            shelfH: 0,
          };
        }
        next[id] = { x: cursor.x, y: cursor.y };
        cursor = {
          x: cursor.x + sz.w + LAYOUT_PADDING,
          y: cursor.y,
          shelfH: Math.max(cursor.shelfH, sz.h),
        };
        mutated = true;
      }
      return mutated ? next : prev;
    });
  }, [orderedIds, sizes, canvasWidth]);

  // Optimal positions: continuously recomputed while optimalMode is on.
  const optimalPositions = useMemo(() => {
    if (!optimalMode) return {};
    const items = orderedIds.map((id) => ({
      id,
      w: sizes[id]?.w ?? 0,
      h: sizes[id]?.h ?? 0,
    }));
    return optimalLayout(items, canvasWidth);
  }, [optimalMode, orderedIds, sizes, canvasWidth]);

  // Final positions: optimal mode ignores manual/greedy and uses the DP
  // output; greedy mode layers manual drags on top of append-only greedy.
  const objects = useMemo(() => {
    const merged = optimalMode
      ? optimalPositions
      : { ...greedyPositions, ...manualPositions };
    return buildState(trace, currentStep, merged);
  }, [trace, currentStep, optimalMode, optimalPositions, greedyPositions, manualPositions]);

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

  // Dev-only: sanity-check ArrayView size estimator vs. measured bounding box.
  useEffect(() => {
    if (!import.meta.env.DEV) return;
    for (const id of orderedIds) {
      const obj = objects[id];
      if (!obj || obj.type !== "array" || !Array.isArray(obj.data)) continue;
      const measured = sizes[id];
      if (!measured) continue;
      const est = estimateArraySize(obj);
      const dw = est.w - measured.w;
      const dh = est.h - measured.h;
      if (Math.abs(dw) > 2 || Math.abs(dh) > 2) {
        console.warn(
          `[estimateArraySize drift] ${id} n=${obj.data.length} ` +
            `measured=${measured.w.toFixed(1)}x${measured.h.toFixed(1)} ` +
            `est=${est.w}x${est.h} Δ=${dw.toFixed(1)},${dh.toFixed(1)}`,
        );
      }
    }
  }, [objects, orderedIds, sizes]);

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

  // ================= AUTO-FIT (optimal mode) =================
  // Whenever optimal positions or sizes change while in optimal mode, compute
  // the bounding box of all placed objects and set scale/offset so the whole
  // layout fits inside the canvas viewport.
  useEffect(() => {
    if (!optimalMode) return;
    let maxX = 0;
    let maxY = 0;
    for (const id of orderedIds) {
      const p = optimalPositions[id];
      const sz = sizes[id];
      if (!p || !sz) continue;
      const right = p.x + sz.w;
      const bottom = p.y + sz.h;
      if (right > maxX) maxX = right;
      if (bottom > maxY) maxY = bottom;
    }
    if (maxX === 0 || maxY === 0) return;
    const el = canvasRef.current;
    if (!el) return;
    const viewW = el.clientWidth;
    const viewH = el.clientHeight;
    if (viewW === 0 || viewH === 0) return;
    const pad = LAYOUT_PADDING;
    const sx = (viewW - pad * 2) / (maxX + pad);
    const sy = (viewH - pad * 2) / (maxY + pad);
    const s = Math.min(1, sx, sy);
    if (s > 0 && isFinite(s)) {
      setScale(s);
      setOffset({ x: 0, y: 0 });
    }
  }, [optimalMode, optimalPositions, sizes, orderedIds]);

  // ================= DRAG =================
  const handleObjectMouseDown = (e, id) => {
    if (optimalMode) return;
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
  // Toggling off freezes the current optimal positions into the greedy
  // baseline, so existing objects stay put and only future objects follow
  // append-only greedy placement.
  const toggleOptimalMode = () => {
    setOptimalMode((wasOn) => {
      if (wasOn) {
        setGreedyPositions({ ...optimalPositions });
        setManualPositions({});
      }
      return !wasOn;
    });
  };

  const handleResetLayout = () => {
    setManualPositions({});
    setGreedyPositions({});
    setOptimalMode(false);
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
          overflow: "hidden",
          minWidth: 0,
        }}
      >
        <span style={{ fontSize: "11px", fontWeight: 700, letterSpacing: "1px", color: "#a9c2e8", textTransform: "uppercase", marginRight: "8px" }}>
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
          style={{
            ...iconButton,
            width: "auto",
            padding: "0 12px",
            fontSize: "12px",
            whiteSpace: "nowrap",
            flexShrink: 0,
            ...(optimalMode
              ? {
                  background: "#1a2f5a",
                  borderColor: "#3d6fc4",
                  color: "#7ab8ff",
                  boxShadow: "0 0 0 1px #3d6fc4",
                }
              : {}),
          }}
          onClick={toggleOptimalMode}
          title="Optimal fit — continuous DP layout with auto zoom-to-fit"
        >
          ⊞ Optimal fit{optimalMode ? " ✓" : ""}
        </button>
        <button
          style={{ ...iconButton, width: "auto", padding: "0 12px", fontSize: "12px", whiteSpace: "nowrap", flexShrink: 0 }}
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
            "radial-gradient(ellipse at 25% 25%, #050912 0%, #02040a 65%)",
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
