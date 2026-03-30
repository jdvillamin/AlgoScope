import { useState, useMemo, useCallback, useRef } from "react";
import Editor from "./components/Editor";
import Canvas from "./components/Canvas";
import Controls from "./components/Controls";
import FilePanel from "./components/FilePanel";
import API from "./api/backend";

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
  const nextId = useRef(2);
  const [files, setFiles] = useState([
    { id: "1", name: "Untitled", code: "", instrumentedCode: "", stdin: "" },
  ]);
  const [activeFileId, setActiveFileId] = useState("1");

  const [activeTab, setActiveTab] = useState("raw");
  const [trace, setTrace] = useState([]);
  const [currentStep, setCurrentStep] = useState(0);
  const [isRunning, setIsRunning] = useState(false);
  const [error, setError] = useState("");
  const [isProcessing, setIsProcessing] = useState(false);
  const [runPhase, setRunPhase] = useState("Idle");
  const [lockToLine, setLockToLine] = useState(true);
  const [stdout, setStdout] = useState("");

  // Derive code/instrumentedCode/stdin from active file
  const activeFile = files.find((f) => f.id === activeFileId);
  const code = activeFile?.code || "";
  const instrumentedCode = activeFile?.instrumentedCode || "";
  const stdin = activeFile?.stdin || "";

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

  const resetExecutionState = useCallback(() => {
    setTrace([]);
    setCurrentStep(0);
    setIsRunning(false);
    setError("");
    setStdout("");
    setIsProcessing(false);
    setRunPhase("Idle");
    setActiveTab("raw");
  }, []);

  const handleNewFile = useCallback(() => {
    const id = String(nextId.current++);
    setFiles((prev) => [
      ...prev,
      { id, name: "Untitled", code: "", instrumentedCode: "", stdin: "" },
    ]);
    setActiveFileId(id);
    resetExecutionState();
  }, [resetExecutionState]);

  const handleSwitchFile = useCallback(
    (id) => {
      if (id === activeFileId) return;
      setActiveFileId(id);
      resetExecutionState();
    },
    [activeFileId, resetExecutionState]
  );

  const handleRenameFile = useCallback((id, name) => {
    setFiles((prev) => prev.map((f) => (f.id === id ? { ...f, name } : f)));
  }, []);

  const handleDeleteFile = useCallback(
    (id) => {
      setFiles((prev) => {
        const remaining = prev.filter((f) => f.id !== id);
        if (remaining.length === 0) return prev;
        if (id === activeFileId) {
          const idx = prev.findIndex((f) => f.id === id);
          const next = remaining[Math.min(idx, remaining.length - 1)];
          setActiveFileId(next.id);
          resetExecutionState();
        }
        return remaining;
      });
    },
    [activeFileId, resetExecutionState]
  );

  const handleLoadSample = useCallback(
    (sample) => {
      const id = String(nextId.current++);
      setFiles((prev) => [
        ...prev,
        {
          id,
          name: sample.name,
          code: sample.code,
          instrumentedCode: sample.instrumentedCode || "",
          stdin: sample.stdin || "",
        },
      ]);
      setActiveFileId(id);
      resetExecutionState();
    },
    [resetExecutionState]
  );

  // --- Execution ---

  const handleTrace = (lines) => {
    const parsed = [];
    const outputLines = [];

    for (const line of lines) {
      try {
        parsed.push(JSON.parse(line));
      } catch {
        if (line.trim()) outputLines.push(line);
      }
    }

    setTrace(parsed);
    setCurrentStep(0);
    setIsRunning(parsed.length > 0);
    setStdout(outputLines.join("\n"));
  };

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
        setStdout("");
        setTrace([]);
        setCurrentStep(0);
        setIsRunning(false);

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
        setStdout("");
        setTrace([]);
        setCurrentStep(0);
        setIsRunning(false);

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
    setIsRunning(false);
    setCurrentStep(0);
    setTrace([]);
    setError("");
    setStdout("");
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
        onNewFile={handleNewFile}
        onSwitchFile={handleSwitchFile}
        onRenameFile={handleRenameFile}
        onDeleteFile={handleDeleteFile}
        onLoadSample={handleLoadSample}
      />

      {/* LEFT: Canvas */}
      <div
        style={{
          flex: 2,
          display: "flex",
          flexDirection: "column",
        }}
      >
        <div style={{ flex: 1, position: "relative" }}>
          <Canvas trace={trace} currentStep={currentStep} />
        </div>

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
          <Controls trace={trace} setCurrentStep={setCurrentStep} setActiveTab={setActiveTab} />
        </div>
      </div>

      {/* RIGHT: Editor */}
      <div
        style={{
          flex: 1.5,
          display: "flex",
          flexDirection: "column",
          borderLeft: "1px solid #1a2535",
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
