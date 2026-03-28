// /frontend/src/engine/traceEngine.js

export function buildState(trace = [], currentStep = 0, positions = {}) {
  const newObjects = {};

  for (let i = 0; i <= currentStep && i < trace.length; i++) {
    const step = trace[i];
    if (!step) continue;

    // ================= VARIABLES =================
    if (step.type === "var_init") {
      newObjects[step.name] = {
        id: step.name,
        type: "var",
        value: step.v ?? "",
      };
    }

    if (step.type === "var" && newObjects[step.name]) {
      newObjects[step.name].value = step.v ?? "";
    }

    // ================= ARRAY =================
    if (step.type === "array_init") {
      newObjects[step.name] = {
        id: step.name,
        type: "array",
        data: Array(step.size).fill(""),
      };
    }

    if (step.type === "array" && newObjects[step.name]) {
      if (Array.isArray(newObjects[step.name].data)) {
        newObjects[step.name].data[step.i] = step.v;
      }
    }

    if (step.type === "array_highlight" && newObjects[step.name]) {
      newObjects[step.name].highlightIndex = step.i;
    }

    // ================= 2D ARRAY =================
    if (step.type === "array2d_init") {
      newObjects[step.name] = {
        id: step.name,
        type: "array2d",
        data: Array.from({ length: step.rows }, () =>
          Array(step.cols).fill(""),
        ),
      };
    }

    if (step.type === "array2d" && newObjects[step.name]) {
      if (
        Array.isArray(newObjects[step.name].data) &&
        newObjects[step.name].data[step.r]
      ) {
        newObjects[step.name].data[step.r][step.c] = step.v;
      }
    }

    if (step.type === "array2d_highlight" && newObjects[step.name]) {
      newObjects[step.name].highlightRow = step.r;
      newObjects[step.name].highlightCol = step.c;
    }

    // ================= LINKED LIST =================
    if (step.type === "ll_init") {
      newObjects[step.name] = {
        id: step.name,
        type: "linkedlist",
        nodes: {},
        links: [],
        pointers: {},
        currentHighlight: null,
      };
    }

    if (step.type === "ll_node" && newObjects[step.list]) {
      newObjects[step.list].nodes[step.id] = {
        id: step.id,
        value: step.v,
      };
    }

    if (step.type === "ll_link" && newObjects[step.list]) {
      newObjects[step.list].links.push({
        from: step.from,
        to: step.to,
      });
    }

    if (step.type === "ll_free" && newObjects[step.list]) {
      delete newObjects[step.list].nodes[step.id];
      newObjects[step.list].links = newObjects[step.list].links.filter(
        (l) => l.from !== step.id && l.to !== step.id,
      );
    }

    if (step.type === "ll_pointer" && newObjects[step.list]) {
      newObjects[step.list].pointers[step.name] = step.target;
    }

    if (step.type === "ll_highlight" && newObjects[step.list]) {
      newObjects[step.list].currentHighlight = step.id;
    }

    // ================= DLL =================
    if (step.type === "dll_init") {
      newObjects[step.name] = {
        id: step.name,
        type: "dll",
        nodes: {},
        nextLinks: [],
        prevLinks: [],
        pointers: {},
        currentHighlight: null,
      };
    }

    if (step.type === "dll_node" && newObjects[step.list]) {
      newObjects[step.list].nodes[step.id] = {
        id: step.id,
        value: step.v,
      };
    }

    if (step.type === "dll_next_link" && newObjects[step.list]) {
      newObjects[step.list].nextLinks.push({
        from: step.from,
        to: step.to,
      });
    }

    if (step.type === "dll_prev_link" && newObjects[step.list]) {
      newObjects[step.list].prevLinks.push({
        from: step.from,
        to: step.to,
      });
    }

    if (step.type === "dll_next_unlink" && newObjects[step.list]) {
      newObjects[step.list].nextLinks = newObjects[step.list].nextLinks.filter(
        (l) => !(l.from === step.from && l.to === step.to),
      );
    }

    if (step.type === "dll_prev_unlink" && newObjects[step.list]) {
      newObjects[step.list].prevLinks = newObjects[step.list].prevLinks.filter(
        (l) => !(l.from === step.from && l.to === step.to),
      );
    }

    if (step.type === "dll_free" && newObjects[step.list]) {
      delete newObjects[step.list].nodes[step.id];

      newObjects[step.list].nextLinks = newObjects[step.list].nextLinks.filter(
        (l) => l.from !== step.id && l.to !== step.id,
      );

      newObjects[step.list].prevLinks = newObjects[step.list].prevLinks.filter(
        (l) => l.from !== step.id && l.to !== step.id,
      );
    }

    if (step.type === "dll_highlight" && newObjects[step.list]) {
      newObjects[step.list].currentHighlight = step.id;
    }

    if (step.type === "dll_pointer" && newObjects[step.list]) {
      newObjects[step.list].pointers[step.name] = step.target;
    }

    // ================= STACK =================
    if (step.type === "stack_init") {
      newObjects[step.name] = {
        id: step.name,
        type: "stack",
        items: [],
        topIndex: -1,
      };
    }

    if (step.type === "stack_push" && newObjects[step.name]) {
      newObjects[step.name].items.push(step.v);
      newObjects[step.name].topIndex = newObjects[step.name].items.length - 1;
    }

    if (step.type === "stack_pop" && newObjects[step.name]) {
      newObjects[step.name].items.pop();
      newObjects[step.name].topIndex = newObjects[step.name].items.length - 1;
    }

    if (step.type === "stack_top" && newObjects[step.name]) {
      newObjects[step.name].topIndex = newObjects[step.name].items.length - 1;
    }

    // ================= QUEUE =================
    if (step.type === "queue_init") {
      newObjects[step.name] = {
        id: step.name,
        type: "queue",
        items: [],
        frontIndex: 0,
        rearIndex: -1,
      };
    }

    if (step.type === "queue_enqueue" && newObjects[step.name]) {
      newObjects[step.name].items.push(step.v);
      newObjects[step.name].rearIndex = newObjects[step.name].items.length - 1;
    }

    if (step.type === "queue_dequeue" && newObjects[step.name]) {
      newObjects[step.name].items.shift();
      newObjects[step.name].rearIndex = newObjects[step.name].items.length - 1;
    }

    if (step.type === "queue_front" && newObjects[step.name]) {
      newObjects[step.name].frontIndex = 0;
    }

    if (step.type === "queue_rear" && newObjects[step.name]) {
      newObjects[step.name].rearIndex = newObjects[step.name].items.length - 1;
    }

    // ================= HASH MAP =================
    if (step.type === "hash_init") {
      newObjects[step.name] = {
        id: step.name,
        type: "hashmap",
        size: step.size,
        buckets: Array.from({ length: step.size }, () => []),
      };
    }

    if (step.type === "hash_put" && newObjects[step.name]) {
      newObjects[step.name].buckets[step.index].push({
        key: step.key,
        value: step.value,
      });
    }

    if (step.type === "hash_remove" && newObjects[step.name]) {
      newObjects[step.name].buckets[step.index] = newObjects[step.name].buckets[
        step.index
      ].filter((entry) => entry.key !== step.key);
    }

    // ================= TREE =================
    if (step.type === "tree_init") {
      newObjects[step.name] = {
        id: step.name,
        type: "tree",
        nodes: {},
        edges: [],
        currentHighlight: null,
      };
    }

    if (step.type === "tree_node" && newObjects[step.tree]) {
      newObjects[step.tree].nodes[step.id] = {
        id: step.id,
        value: step.v,
      };
    }

    if (step.type === "tree_edge" && newObjects[step.tree]) {
      newObjects[step.tree].edges.push({
        parent: step.parent,
        child: step.child,
      });
    }

    if (step.type === "tree_highlight" && newObjects[step.tree]) {
      newObjects[step.tree].currentHighlight = step.id;
    }

    // ================= GRAPH =================
    if (step.type === "graph_init") {
      newObjects[step.name] = {
        id: step.name,
        type: "graph",
        nodes: {},
        edges: [],
        currentHighlight: null,
      };
    }

    if (step.type === "graph_node" && newObjects[step.graph]) {
      newObjects[step.graph].nodes[step.id] = {
        id: step.id,
      };
    }

    if (step.type === "graph_edge" && newObjects[step.graph]) {
      newObjects[step.graph].edges.push({
        from: step.from,
        to: step.to,
      });
    }

    if (step.type === "graph_highlight" && newObjects[step.graph]) {
      newObjects[step.graph].currentHighlight = step.id;
    }
  }

  // ================= AUTO LAYOUT =================

  const orderedIds = [];

  for (let i = 0; i <= currentStep && i < trace.length; i++) {
    const step = trace[i];
    if (!step) continue;

    if (
      step.type === "var_init" ||
      step.type === "array_init" ||
      step.type === "array2d_init" ||
      step.type === "ll_init" ||
      step.type === "dll_init" ||
      step.type === "stack_init" ||
      step.type === "queue_init" ||
      step.type === "hash_init" ||
      step.type === "tree_init" ||
      step.type === "graph_init"
    ) {
      if (!orderedIds.includes(step.name)) {
        orderedIds.push(step.name);
      }
    }
  }

  const columns = 3;
  const xStart = 120;
  const yStart = 120;
  const xGap = 300;
  const yGap = 260;

  orderedIds.forEach((id, index) => {
    const obj = newObjects[id];
    if (!obj) return;

    const saved = positions[id];

    if (saved) {
      obj.x = saved.x;
      obj.y = saved.y;
    } else {
      const col = index % columns;
      const row = Math.floor(index / columns);

      obj.x = xStart + col * xGap;
      obj.y = yStart + row * yGap;
    }
  });

  return newObjects;
}
