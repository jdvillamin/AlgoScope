import { useState, useMemo, useCallback, useRef, useEffect } from "react";
import Editor from "./components/Editor";
import Canvas from "./components/Canvas";
import Controls from "./components/Controls";
import FilePanel from "./components/FilePanel";
import UnsavedPrompt from "./components/UnsavedPrompt";
import API from "./api/backend";

const STORAGE_KEY = "algoscope:state:v2";
const DEFAULT_FILE = {
  id: "1",
  name: "Untitled",
  code: "",
  instrumentedCode: "",
  stdin: "",
  trace: [],
  stdout: "",
  savedSnapshot: null,
};

function isFileUnsaved(f) {
  if (!f) return false;
  const s = f.savedSnapshot;
  if (!s) return true;
  return s.code !== f.code || s.name !== f.name || s.stdin !== f.stdin;
}

function loadPersistedState() {
  try {
    const raw = localStorage.getItem(STORAGE_KEY);
    if (!raw) return null;
    const parsed = JSON.parse(raw);
    if (!parsed || !Array.isArray(parsed.files) || parsed.files.length === 0) return null;
    // Normalize: every file must have the expected shape.
    const files = parsed.files
      .filter((f) => f && typeof f.id === "string")
      .map((f) => {
        const name = typeof f.name === "string" ? f.name : "Untitled";
        const code = typeof f.code === "string" ? f.code : "";
        const stdin = typeof f.stdin === "string" ? f.stdin : "";
        return {
          id: f.id,
          name,
          code,
          instrumentedCode: typeof f.instrumentedCode === "string" ? f.instrumentedCode : "",
          stdin,
          trace: Array.isArray(f.trace) ? f.trace : [],
          stdout: typeof f.stdout === "string" ? f.stdout : "",
          savedSnapshot: { code, name, stdin },
        };
      });
    if (files.length === 0) return null;
    const activeFileId =
      typeof parsed.activeFileId === "string" && files.some((f) => f.id === parsed.activeFileId)
        ? parsed.activeFileId
        : files[0].id;
    return { files, activeFileId };
  } catch {
    return null;
  }
}

const TRACE_LINE_RE = /^(\s*)trace_line\s*\(\s*(\d+)\s*\)\s*;/;
const TRACE_CALL_RE = /^\s*(trace_\w+\s*\(|#include\s+"tracer\.h")/;
const TRACE_LOOP_RE = /^\s*for\s*\([^)]*\)\s*\{\s*trace_\w+\s*\(.*\)\s*;\s*\}/;

function isTraceLine(line) {
  return TRACE_CALL_RE.test(line) || TRACE_LOOP_RE.test(line);
}

function reverseInstrument(instrumentedCode) {
  const lines = instrumentedCode.split("\n");
  const isTrace = lines.map(isTraceLine);

  const rawLines = [];
  const instrToRaw = {};
  for (let i = 0; i < lines.length; i++) {
    if (!isTrace[i]) {
      rawLines.push(lines[i]);
      instrToRaw[i] = rawLines.length;
    }
  }

  const updatedLines = lines.map((line, i) => {
    const m = line.match(TRACE_LINE_RE);
    if (!m) return line;
    for (let j = i + 1; j < lines.length; j++) {
      if (!isTrace[j]) return `${m[1]}trace_line(${instrToRaw[j]});`;
    }
    return line;
  });

  return {
    rawCode: rawLines.join("\n"),
    updatedInstrumentedCode: updatedLines.join("\n"),
  };
}

function App() {
  // Read persisted state exactly once on mount via a lazy useState initializer
  // — lint forbids touching ref.current during render, but a useState init
  // function runs exactly once per mount.
  const [persisted] = useState(loadPersistedState);

  const nextId = useRef(
    persisted
      ? Math.max(...persisted.files.map((f) => parseInt(f.id, 10) || 0)) + 1
      : 2
  );
  const [files, setFiles] = useState(() => persisted?.files ?? [DEFAULT_FILE]);
  const [activeFileId, setActiveFileId] = useState(() => persisted?.activeFileId ?? "1");

  // Debounced write-through to localStorage. Only files that are saved (clean
  // vs. their savedSnapshot) are persisted — unsaved samples / new files /
  // dirty edits disappear on reload.
  useEffect(() => {
    const handle = setTimeout(() => {
      try {
        const cleanFiles = files.filter((f) => !isFileUnsaved(f));
        const activeStillThere = cleanFiles.some((f) => f.id === activeFileId);
        const payload = {
          files: cleanFiles,
          activeFileId: activeStillThere ? activeFileId : cleanFiles[0]?.id ?? null,
        };
        localStorage.setItem(STORAGE_KEY, JSON.stringify(payload));
      } catch {
        // Quota exceeded or storage unavailable — drop silently.
      }
    }, 300);
    return () => clearTimeout(handle);
  }, [files, activeFileId]);

  const [activeTab, setActiveTab] = useState("raw");
  const [currentStep, setCurrentStep] = useState(0);
  const [error, setError] = useState("");
  const [isProcessing, setIsProcessing] = useState(false);
  const [runPhase, setRunPhase] = useState("Idle");
  const [lockToLine, setLockToLine] = useState(true);

  // Resizable / hidable editor panel.
  const [editorWidth, setEditorWidth] = useState(() => {
    const saved = parseInt(localStorage.getItem("algoscope:editorWidth") || "", 10);
    return Number.isFinite(saved) && saved >= 320 ? saved : 560;
  });
  const [editorHidden, setEditorHidden] = useState(
    () => localStorage.getItem("algoscope:editorHidden") === "1"
  );
  const [isResizing, setIsResizing] = useState(false);

  useEffect(() => {
    localStorage.setItem("algoscope:editorWidth", String(editorWidth));
  }, [editorWidth]);
  useEffect(() => {
    localStorage.setItem("algoscope:editorHidden", editorHidden ? "1" : "0");
  }, [editorHidden]);

  useEffect(() => {
    if (!isResizing) return;
    const onMove = (e) => {
      const next = window.innerWidth - e.clientX;
      if (next < 260) {
        setEditorHidden(true);
        setIsResizing(false);
        return;
      }
      const clamped = Math.max(320, Math.min(next, window.innerWidth - 400));
      setEditorWidth(clamped);
    };
    const onUp = () => setIsResizing(false);
    window.addEventListener("mousemove", onMove);
    window.addEventListener("mouseup", onUp);
    const prevCursor = document.body.style.cursor;
    const prevSelect = document.body.style.userSelect;
    document.body.style.cursor = "col-resize";
    document.body.style.userSelect = "none";
    return () => {
      window.removeEventListener("mousemove", onMove);
      window.removeEventListener("mouseup", onUp);
      document.body.style.cursor = prevCursor;
      document.body.style.userSelect = prevSelect;
    };
  }, [isResizing]);

  // Derive code/instrumentedCode/stdin/trace/stdout from active file
  const activeFile = files.find((f) => f.id === activeFileId);
  const code = activeFile?.code || "";
  const instrumentedCode = activeFile?.instrumentedCode || "";
  const stdin = activeFile?.stdin || "";
  const trace = useMemo(() => activeFile?.trace || [], [activeFile?.trace]);
  const stdout = activeFile?.stdout || "";
  const isRunning = trace.length > 0;

  const updateActiveFile = useCallback(
    (updates) => {
      setFiles((prev) =>
        prev.map((f) => (f.id === activeFileId ? { ...f, ...updates } : f))
      );
    },
    [activeFileId]
  );

  const setCode = useCallback(
    (v) => updateActiveFile({ code: v }),
    [updateActiveFile]
  );
  const setInstrumentedCode = useCallback(
    (v) => updateActiveFile({ instrumentedCode: v }),
    [updateActiveFile]
  );
  const setStdin = useCallback(
    (v) => updateActiveFile({ stdin: v }),
    [updateActiveFile]
  );

  // --- File operations ---

  // Clears ephemeral UI state (error banners, processing spinner, active tab).
  // Persisted trace/stdout live on the file itself and are NOT cleared here —
  // use clearActiveFileTrace for that.
  const resetUiState = useCallback(() => {
    setCurrentStep(0);
    setError("");
    setIsProcessing(false);
    setRunPhase("Idle");
    setActiveTab("raw");
  }, []);

  const clearActiveFileTrace = useCallback(() => {
    updateActiveFile({ trace: [], stdout: "" });
  }, [updateActiveFile]);

  const activeFileUnsaved = isFileUnsaved(activeFile);
  const unsavedIds = useMemo(
    () => new Set(files.filter(isFileUnsaved).map((f) => f.id)),
    [files]
  );

  // Pending action + modal. When the active file is unsaved and the user
  // tries to switch away, we stash the action as a function and prompt.
  const [pendingAction, setPendingAction] = useState(null);
  const promptOpen = pendingAction !== null;

  const withUnsavedGuard = useCallback(
    (action) => {
      if (isFileUnsaved(activeFile)) {
        setPendingAction(() => action);
      } else {
        action();
      }
    },
    [activeFile]
  );

  const handleSaveActive = useCallback(() => {
    if (!activeFile) return;
    updateActiveFile({
      savedSnapshot: {
        code: activeFile.code ?? "",
        name: activeFile.name ?? "",
        stdin: activeFile.stdin ?? "",
      },
    });
  }, [activeFile, updateActiveFile]);

  const handleDiscardActive = useCallback(() => {
    if (!activeFile) return;
    const snap = activeFile.savedSnapshot;
    if (!snap) {
      // Never saved → drop the file entirely.
      setFiles((prev) => {
        const remaining = prev.filter((f) => f.id !== activeFile.id);
        if (remaining.length === 0) {
          const fresh = { ...DEFAULT_FILE, id: String(nextId.current++) };
          setActiveFileId(fresh.id);
          return [fresh];
        }
        setActiveFileId((curId) =>
          curId === activeFile.id ? remaining[0].id : curId
        );
        return remaining;
      });
      resetUiState();
    } else {
      // Revert to saved snapshot.
      updateActiveFile({ code: snap.code, name: snap.name, stdin: snap.stdin });
    }
  }, [activeFile, resetUiState, updateActiveFile]);

  const runPendingAction = useCallback(() => {
    const action = pendingAction;
    setPendingAction(null);
    if (typeof action === "function") action();
  }, [pendingAction]);

  const handlePromptSave = useCallback(() => {
    handleSaveActive();
    runPendingAction();
  }, [handleSaveActive, runPendingAction]);

  const handlePromptDiscard = useCallback(() => {
    handleDiscardActive();
    runPendingAction();
  }, [handleDiscardActive, runPendingAction]);

  const handlePromptCancel = useCallback(() => {
    setPendingAction(null);
  }, []);

  const handleNewFile = useCallback(() => {
    withUnsavedGuard(() => {
      const id = String(nextId.current++);
      setFiles((prev) => [
        ...prev,
        {
          id,
          name: "Untitled",
          code: "",
          instrumentedCode: "",
          stdin: "",
          trace: [],
          stdout: "",
          savedSnapshot: null,
        },
      ]);
      setActiveFileId(id);
      resetUiState();
    });
  }, [resetUiState, withUnsavedGuard]);

  const handleSwitchFile = useCallback(
    (id) => {
      if (id === activeFileId) return;
      withUnsavedGuard(() => {
        setActiveFileId(id);
        resetUiState();
      });
    },
    [activeFileId, resetUiState, withUnsavedGuard]
  );

  const handleRenameFile = useCallback((id, name) => {
    setFiles((prev) => prev.map((f) => (f.id === id ? { ...f, name } : f)));
  }, []);

  const handleDeleteFile = useCallback(
    (id) => {
      const doDelete = () => {
        setFiles((prev) => {
          const remaining = prev.filter((f) => f.id !== id);
          if (remaining.length === 0) return prev;
          if (id === activeFileId) {
            const idx = prev.findIndex((f) => f.id === id);
            const next = remaining[Math.min(idx, remaining.length - 1)];
            setActiveFileId(next.id);
            resetUiState();
          }
          return remaining;
        });
      };
      // Only guard when deleting the currently-active unsaved file.
      if (id === activeFileId && isFileUnsaved(activeFile)) {
        withUnsavedGuard(doDelete);
      } else {
        doDelete();
      }
    },
    [activeFile, activeFileId, resetUiState, withUnsavedGuard]
  );

  const handleImportFile = useCallback(
    (file) => {
      if (!file) return;
      withUnsavedGuard(() => {
        const reader = new FileReader();
        reader.onload = (e) => {
          const contents = typeof e.target?.result === "string" ? e.target.result : "";
          const id = String(nextId.current++);
          const name = (file.name || "untitled").replace(/\.c$/i, "");
          setFiles((prev) => [
            ...prev,
            {
              id,
              name,
              code: contents,
              instrumentedCode: "",
              stdin: "",
              trace: [],
              stdout: "",
              savedSnapshot: null,
            },
          ]);
          setActiveFileId(id);
          resetUiState();
        };
        reader.readAsText(file);
      });
    },
    [resetUiState, withUnsavedGuard]
  );

  const handleExportFile = useCallback(() => {
    const current = files.find((f) => f.id === activeFileId);
    if (!current) return;
    const safeName = (current.name || "untitled").replace(/[^a-z0-9_.-]/gi, "_");
    const filename = /\.c$/i.test(safeName) ? safeName : `${safeName}.c`;
    const blob = new Blob([current.code ?? ""], { type: "text/x-c" });
    const url = URL.createObjectURL(blob);
    const a = document.createElement("a");
    a.href = url;
    a.download = filename;
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(url);
  }, [files, activeFileId]);

  const handleLoadSample = useCallback(
    (sample) => {
      withUnsavedGuard(() => {
        const id = String(nextId.current++);
        setFiles((prev) => [
          ...prev,
          {
            id,
            name: sample.name,
            code: sample.code,
            instrumentedCode: sample.instrumentedCode || "",
            stdin: sample.stdin || "",
            trace: [],
            stdout: "",
            savedSnapshot: null,
          },
        ]);
        setActiveFileId(id);
        resetUiState();
      });
    },
    [resetUiState, withUnsavedGuard]
  );

  // --- Execution ---

  const handleTrace = useCallback(
    (lines) => {
      const parsed = [];
      const outputLines = [];

      for (const line of lines) {
        try {
          parsed.push(JSON.parse(line));
        } catch {
          if (line.trim()) outputLines.push(line);
        }
      }

      updateActiveFile({ trace: parsed, stdout: outputLines.join("\n") });
      setCurrentStep(0);
    },
    [updateActiveFile]
  );

  const runCode = async () => {
    const isInstrumentedTab = activeTab === "instrumented";
    const codeToRun = isInstrumentedTab ? instrumentedCode : code;

    if (!codeToRun.trim()) {
      alert("Please enter C code first.");
      return;
    }

    if (isInstrumentedTab) {
      const numbers = stdin.match(/-?\d+/g) || [];
      for (const n of numbers) {
        if (Math.abs(parseInt(n, 10)) > 20) {
          setError(`Input number ${n} exceeds the limit of 20.`);
          return;
        }
      }

      try {
        setIsProcessing(true);
        setRunPhase("Preparing instrumented code...");
        setError("");
        clearActiveFileTrace();
        setCurrentStep(0);

        await new Promise((r) => setTimeout(r, 120));

        setRunPhase("Compiling instrumented code...");
        await new Promise((r) => setTimeout(r, 120));

        const resPromise = API.post("/run", {
          code: instrumentedCode,
          skip_instrumentation: true,
          stdin: stdin,
        });

        setRunPhase("Executing program...");
        const res = await resPromise;

        console.log("Backend response:", res.data);

        if (res.data.error) {
          setRunPhase("Compilation or execution failed.");
          setError(res.data.error);
          setIsProcessing(false);
          return;
        }

        setRunPhase("Rendering trace...");
        await new Promise((r) => setTimeout(r, 180));

        handleTrace(res.data.trace || []);

        setRunPhase("Execution complete.");
        setTimeout(() => {
          setIsProcessing(false);
        }, 250);
      } catch (err) {
        console.error(err);
        setRunPhase("Backend error.");
        setError("Backend error. Is Flask running?");
        setIsProcessing(false);
      }
    } else {
      try {
        setIsProcessing(true);
        setRunPhase("Preparing source code...");
        setError("");
        clearActiveFileTrace();
        setCurrentStep(0);

        await new Promise((r) => setTimeout(r, 120));

        setRunPhase("Sending code to backend...");
        await new Promise((r) => setTimeout(r, 120));

        setRunPhase("Instrumenting source code...");
        const res = await API.post("/run", {
          code: code,
          instrument_only: true,
        });

        console.log("Backend response:", res.data);

        if (res.data.error) {
          setRunPhase("Instrumentation failed.");
          setError(res.data.error);
          setIsProcessing(false);
          return;
        }

        if (typeof res.data.instrumented_code === "string") {
          setInstrumentedCode(res.data.instrumented_code);
        }

        setRunPhase("Instrumentation complete.");
        setActiveTab("instrumented");
        setTimeout(() => {
          setIsProcessing(false);
        }, 250);
      } catch (err) {
        console.error(err);
        setRunPhase("Backend error.");
        setError("Backend error. Is Flask running?");
        setIsProcessing(false);
      }
    }
  };

  const deInstrument = useCallback(() => {
    if (!instrumentedCode.trim()) return;
    const { rawCode, updatedInstrumentedCode } =
      reverseInstrument(instrumentedCode);
    setCode(rawCode);
    setInstrumentedCode(updatedInstrumentedCode);
  }, [instrumentedCode, setCode, setInstrumentedCode]);

  const resetExecution = () => {
    clearActiveFileTrace();
    setCurrentStep(0);
    setError("");
    setIsProcessing(false);
    setRunPhase("Idle");
    setActiveTab("raw");
  };

  const currentLine = useMemo(() => {
    for (let i = currentStep; i >= 0; i--) {
      if (trace[i]?.type === "line") {
        return trace[i].n;
      }
    }
    return null;
  }, [currentStep, trace]);

  return (
    <div
      style={{
        display: "flex",
        height: "100vh",
        width: "100vw",
        overflow: "hidden",
        background: "#080d15",
      }}
    >
      {/* FAR LEFT: File Panel */}
      <FilePanel
        files={files}
        activeFileId={activeFileId}
        unsavedIds={unsavedIds}
        activeFileUnsaved={activeFileUnsaved}
        onNewFile={handleNewFile}
        onSwitchFile={handleSwitchFile}
        onRenameFile={handleRenameFile}
        onDeleteFile={handleDeleteFile}
        onLoadSample={handleLoadSample}
        onImportFile={handleImportFile}
        onExportFile={handleExportFile}
        onSaveFile={handleSaveActive}
      />
      <UnsavedPrompt
        open={promptOpen}
        fileName={activeFile?.name}
        onSave={handlePromptSave}
        onDiscard={handlePromptDiscard}
        onCancel={handlePromptCancel}
      />

      {/* LEFT: Canvas */}
      <div
        style={{
          flex: 1,
          minWidth: 0,
          display: "flex",
          flexDirection: "column",
          position: "relative",
        }}
      >
        <div style={{ flex: 1, position: "relative", minHeight: 0 }}>
          <Canvas trace={trace} currentStep={currentStep} />
        </div>
        {editorHidden && (
            <button
              onClick={() => setEditorHidden(false)}
              title="Show editor panel"
              style={{
                position: "absolute",
                top: 6,
                right: 12,
                height: 32,
                zIndex: 10,
                display: "flex",
                alignItems: "center",
                gap: "6px",
                padding: "0 12px",
                background: "#121c2c",
                color: "#c8d8f0",
                border: "1px solid #1e2d42",
                borderRadius: "6px",
                fontSize: "12px",
                fontWeight: 600,
                lineHeight: 1,
                cursor: "pointer",
                boxShadow: "0 2px 8px rgba(0,0,0,0.4)",
              }}
            >
              <span style={{ fontSize: "14px", lineHeight: 1, display: "inline-block", transform: "translateY(-1px)" }}>‹</span>
              Show Editor
            </button>
          )}

        <div
          style={{
            height: "100px",
            borderTop: "1px solid #1a2535",
            background: "#0e1520",
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
          }}
        >
          <Controls trace={trace} currentStep={currentStep} setCurrentStep={setCurrentStep} setActiveTab={setActiveTab} />
        </div>
      </div>

      {/* Draggable resizer */}
      {!editorHidden && (
        <div
          onMouseDown={(e) => {
            e.preventDefault();
            setIsResizing(true);
          }}
          onDoubleClick={() => setEditorWidth(560)}
          title="Drag to resize · double-click to reset"
          style={{
            width: "6px",
            cursor: "col-resize",
            background: isResizing ? "#2a3f5c" : "#1a2535",
            transition: isResizing ? "none" : "background 0.15s",
            flexShrink: 0,
            zIndex: 5,
          }}
        />
      )}

      {/* RIGHT: Editor */}
      <div
        style={{
          width: editorHidden ? 0 : `${editorWidth}px`,
          flexShrink: 0,
          display: editorHidden ? "none" : "flex",
          flexDirection: "column",
        }}
      >
        <div style={{ flex: 3, minHeight: 0 }}>
          <Editor
            code={code}
            setCode={setCode}
            instrumentedCode={instrumentedCode}
            setInstrumentedCode={setInstrumentedCode}
            currentLine={currentLine}
            isRunning={isRunning}
            isProcessing={isProcessing}
            onRun={runCode}
            onReset={resetExecution}
            activeTab={activeTab}
            setActiveTab={setActiveTab}
            stdin={stdin}
            setStdin={setStdin}
            lockToLine={lockToLine}
            setLockToLine={setLockToLine}
            onDeInstrument={deInstrument}
            onHide={() => setEditorHidden(true)}
          />
        </div>

        <div
          style={{
            flex: 1,
            display: "flex",
            flexDirection: "column",
            borderTop: "1px solid #1a2535",
            background: "#0e1520",
            position: "relative",
            overflow: "hidden",
          }}
        >
          {/* Console header */}
          <div
            style={{
              padding: "9px 16px",
              borderBottom: "1px solid #1a2535",
              display: "flex",
              justifyContent: "space-between",
              alignItems: "center",
            }}
          >
            <span
              style={{
                fontSize: "11px",
                fontWeight: 600,
                letterSpacing: "0.8px",
                color: "#647e9c",
                textTransform: "uppercase",
              }}
            >
              Console
            </span>
            <span
              style={{
                fontSize: "12px",
                fontWeight: 500,
                color: isProcessing ? "#f0a429" : "#506888",
              }}
            >
              {runPhase}
            </span>
          </div>

          {isProcessing && (
            <div
              style={{
                position: "absolute",
                top: 38,
                left: 0,
                right: 0,
                height: "2px",
                background:
                  "linear-gradient(90deg, transparent, #f0a429, transparent)",
                backgroundSize: "200% 100%",
                animation: "consoleShimmer 1.2s linear infinite",
              }}
            />
          )}

          <div
            style={{
              flex: 1,
              padding: "14px 16px",
              overflowY: "auto",
              fontSize: "12.5px",
              fontFamily:
                "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
              color: error ? "#f87171" : "#647e9c",
              whiteSpace: "pre-wrap",
              lineHeight: 1.6,
              transition: "opacity 0.2s ease",
              opacity: isProcessing ? 0.85 : 1,
            }}
          >
            {isProcessing ? (
              <div
                style={{
                  display: "flex",
                  alignItems: "flex-start",
                  gap: "12px",
                  color: "#c8d8f0",
                }}
              >
                <div
                  style={{
                    width: "13px",
                    height: "13px",
                    border: "2px solid #1e2d42",
                    borderTop: "2px solid #f0a429",
                    borderRadius: "50%",
                    animation: "spin 0.8s linear infinite",
                    marginTop: "3px",
                    flexShrink: 0,
                  }}
                />
                <div>
                  <div
                    style={{
                      fontWeight: 600,
                      color: "#f0a429",
                      fontFamily: "inherit",
                    }}
                  >
                    Processing...
                  </div>
                  <div
                    style={{
                      marginTop: "5px",
                      color: "#7b96bf",
                      fontFamily: "inherit",
                    }}
                  >
                    {runPhase}
                  </div>
                </div>
              </div>
            ) : error ? (
              error
            ) : trace.length > 0 ? (
              <>
                <div style={{ color: "#506888", marginBottom: stdout ? "10px" : 0 }}>
                  {`Trace events: ${trace.length}  ·  Step: ${currentStep}  ·  Line: ${currentLine ?? "—"}`}
                </div>
                {stdout && (
                  <>
                    <div style={{ fontSize: "11px", fontWeight: 600, letterSpacing: "0.8px", color: "#3d5270", textTransform: "uppercase", marginBottom: "6px" }}>
                      Standard Output
                    </div>
                    <div style={{ color: "#c8d8f0" }}>{stdout}</div>
                  </>
                )}
              </>
            ) : (
              "Waiting for execution..."
            )}
          </div>
        </div>
      </div>

      <style>
        {`
          @keyframes spin {
            to { transform: rotate(360deg); }
          }
          @keyframes consoleShimmer {
            0% { background-position: 200% 0; }
            100% { background-position: -200% 0; }
          }
        `}
      </style>
    </div>
  );
}

export default App;
