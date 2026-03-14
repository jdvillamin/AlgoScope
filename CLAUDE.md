# AlgoScope

An educational tool that visualizes algorithm and data structure execution in real-time. Users write C code, the backend instruments it via GPT-4, compiles and runs it, and the frontend renders animated visualizations of data structures as they evolve step-by-step.

## Tech Stack

**Frontend:** React 19, Vite 7, D3.js 7, Monaco Editor, Axios
**Backend:** Python/Flask, Flask-CORS, OpenAI API (GPT-4.1)
**Tracer:** C (header-only library, compiled with user code via GCC)

## Project Structure

```
frontend/src/
  App.jsx              # Root orchestrator; owns all state
  api/backend.js       # Axios instance, single POST /run call
  components/
    Canvas.jsx         # Left panel; renders visual objects on a pannable canvas
    Editor.jsx         # Right panel; Monaco-based code editor
    Controls.jsx       # Playback controls (step/play/reset)
    Visuals/           # 10 data-structure renderers (one component per type)
  traceEngine.js       # buildState(): pure fn replaying trace events → render state

backend/
  app.py               # Flask app; single POST /run endpoint (port 5000)
  ml/
    instrumenter.py    # Calls GPT-4 to insert tracer calls into user code
    prompt_header.py   # System prompt enforcing strict instrumentation rules

tracer/
  tracer.h / tracer.c  # 40+ C functions emitting JSON trace events via printf

samples/
  raw_samples/         # Original C algorithm examples
  traced_samples/      # Pre-instrumented versions of raw_samples
```

## Build & Run

**Frontend**
```bash
cd frontend
npm install
npm run dev      # dev server (Vite proxies /api → localhost:5000)
npm run build
npm run lint
```

**Backend**
```bash
cd backend
source ../venv/bin/activate
python app.py    # Flask dev server on :5000
```

## Key Data Flow

1. User edits C code in Editor → `App.jsx` state
2. `POST /run { code }` → Flask
3. Flask calls GPT-4 via `instrumenter.py` → inserts `trace_*()` calls
4. GCC compiles instrumented code linked with `tracer.c` → runs with 5s timeout
5. Stdout = newline-delimited JSON events; returned in response as `trace[]`
6. `traceEngine.buildState(trace, currentStep)` replays events → object list
7. `Canvas.jsx` renders each object with the matching `Visuals/` component

## Additional Documentation

| File | When to read |
|------|--------------|
| `.claude/docs/architectural_patterns.md` | Before modifying state flow, adding new data structure support, or extending the backend pipeline |
