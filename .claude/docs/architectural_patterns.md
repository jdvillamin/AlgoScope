# Architectural Patterns

## 1. Single-Component State (App.jsx)

All application state lives in `frontend/src/App.jsx` with no Redux, Context, or external store. State is passed down as props; callbacks are passed up via handler props (`onRun`, `onReset`, `onMouseDown`). Before adding global state, consider whether it belongs in `App.jsx` first.

Key state fields: `code`, `instrumentedCode`, `trace` (event array), `currentStep`, `isRunning`, `isProcessing`.

## 2. Pure Trace Replay (traceEngine.js)

`buildState(trace, currentStep)` is a **pure function** — no side effects, no mutation. It replays the trace array from index 0 to `currentStep`, building the current render state. Visualization logic should never mutate trace events directly; always derive state by replaying through `buildState`.

Object positions persist via a separate drag-state map (keyed by object ID), merged in after `buildState` returns.

## 3. Type-Dispatched Visual Components (Canvas.jsx → Visuals/)

Each trace object has a `type` field. `Canvas.jsx` dispatches rendering to one of 10 components in `frontend/src/components/Visuals/` based on `type`. Adding a new data structure requires:
1. New trace functions in `tracer/tracer.c` + `tracer/tracer.h`
2. Handling new event types in `traceEngine.js:buildState()`
3. A new `Visuals/XxxView.jsx` component
4. A dispatch case in `Canvas.jsx`

## 4. Uniform Visual Object Schema

All renderable objects share a base shape passed to Visuals components:
```
{ type, id, x, y, label?, ...type-specific fields }
```
Position (`x`, `y`) is absolute on the canvas. Drag interactions update position in App state, not inside individual components.

## 5. Drag Pattern (All Visuals)

Every `Visuals/*.jsx` component accepts an `onMouseDown(id, e)` callback. The parent (`Canvas.jsx`) owns the drag logic and updates position state. Do not implement drag inside individual visual components.

## 6. Backend Pipeline: Stateless Request/Response

`POST /run` is the only endpoint (`backend/app.py:~L40`). Each request is fully self-contained:
- Input: raw C source string
- Output: `{ trace, instrumented_code, error?, stderr? }`

No database, no session state. The 5-second subprocess timeout is enforced at `backend/app.py:~L62`.

## 7. GPT-4 Instrumentation Constraints (instrumenter.py + prompt_header.py)

The prompt enforces strict rules:
- Only **insert** new trace calls — never reorder, remove, or rewrite existing code
- Always add `#include "tracer.h"` at the top
- Preserve line numbers relative to original source
- Strip markdown fences and line-number prefixes from GPT response before compiling

When modifying `prompt_header.py`, test against multiple `raw_samples/` to confirm GPT-4 still respects these constraints.

## 8. Tracer Library Convention (tracer.c / tracer.h)

Each trace function emits a single-line JSON object to stdout via `printf`. All events include a `"type"` field that matches the dispatch key used in `traceEngine.js`. Functions are grouped by data structure type. The library is compiled directly with user code (not as a separate `.so`), so functions must remain C-linkage compatible.

## 9. Vite Proxy for Local Dev

`frontend/vite.config.js` proxies `/api/*` → `http://localhost:5000`. The Axios instance in `frontend/src/api/backend.js` uses `/api/run` as the path, so no hardcoded backend URLs appear in component code.

## 10. Dark Theme Color Palette

Used consistently across all inline styles in `Visuals/` and `Canvas.jsx`:
- Backgrounds: `#0f141d`, `#141821`, `#1c2230`
- Accent/highlight: `#fbc531` (gold), `#2d8cff` (blue)
- Text: `#ffffff`, `#8aa2ff`

New visual components should use these values directly (no CSS variables are defined).
