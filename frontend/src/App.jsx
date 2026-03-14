import { useState, useMemo } from "react";
import Editor from "./components/Editor";
import Canvas from "./components/Canvas";
import Controls from "./components/Controls";
import API from "./api/backend";

function App() {
  const [code, setCode] = useState("");
  const [instrumentedCode, setInstrumentedCode] = useState("");
  const [activeTab, setActiveTab] = useState("raw");

  const [trace, setTrace] = useState([]);
  const [currentStep, setCurrentStep] = useState(0);
  const [isRunning, setIsRunning] = useState(false);
  const [error, setError] = useState("");

  const [isProcessing, setIsProcessing] = useState(false);
  const [runPhase, setRunPhase] = useState("Idle");

  const handleTrace = (lines) => {
    const parsed = lines
      .map((line) => {
        try {
          return JSON.parse(line);
        } catch {
          return null;
        }
      })
      .filter(Boolean);

    setTrace(parsed);
    setCurrentStep(0);
    setIsRunning(parsed.length > 0);
  };

  const runCode = async () => {
    const isInstrumentedTab = activeTab === "instrumented";
    const codeToRun = isInstrumentedTab ? instrumentedCode : code;

    if (!codeToRun.trim()) {
      alert("Please enter C code first.");
      return;
    }

    try {
      setIsProcessing(true);
      setRunPhase("Preparing source code...");
      setError("");
      setTrace([]);
      setCurrentStep(0);
      setIsRunning(false);

      await new Promise((r) => setTimeout(r, 120));

      setRunPhase("Sending code to backend...");
      await new Promise((r) => setTimeout(r, 120));

      const resPromise = API.post("/run", {
        code: codeToRun,
        skip_instrumentation: isInstrumentedTab,
      });

      if (!isInstrumentedTab) {
        setRunPhase("Instrumenting source code...");
        await new Promise((r) => setTimeout(r, 220));
      }

      setRunPhase("Compiling instrumented code...");
      await new Promise((r) => setTimeout(r, 220));

      setRunPhase("Executing program...");
      const res = await resPromise;

      console.log("Backend response:", res.data);

      if (typeof res.data.instrumented_code === "string") {
        setInstrumentedCode(res.data.instrumented_code);
      } else {
        setInstrumentedCode("");
      }

      if (res.data.error) {
        setRunPhase("Compilation or execution failed.");
        setError(res.data.error);
        setActiveTab("instrumented");
        setIsProcessing(false);
        return;
      }

      setRunPhase("Rendering trace...");
      await new Promise((r) => setTimeout(r, 180));

      handleTrace(res.data.trace || []);
      setActiveTab("raw");

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
  };

  const resetExecution = () => {
    setIsRunning(false);
    setCurrentStep(0);
    setTrace([]);
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
        background: "#0f141d",
      }}
    >
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
            height: "120px",
            borderTop: "1px solid #1f2533",
            background: "#141821",
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
          }}
        >
          <Controls trace={trace} setCurrentStep={setCurrentStep} />
        </div>
      </div>

      {/* RIGHT: Editor */}
      <div
        style={{
          flex: 1.5,
          display: "flex",
          flexDirection: "column",
          borderLeft: "1px solid #1f2533",
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
          />
        </div>

        <div
          style={{
            flex: 1,
            display: "flex",
            flexDirection: "column",
            borderTop: "1px solid #1f2533",
            background: "#141821",
            position: "relative",
            overflow: "hidden",
          }}
        >
          <div
            style={{
              padding: "10px 16px",
              borderBottom: "1px solid #1f2533",
              fontSize: "13px",
              fontWeight: 600,
              color: "#9aa4c7",
              letterSpacing: "0.5px",
              display: "flex",
              justifyContent: "space-between",
              alignItems: "center",
            }}
          >
            <span>OBJECT DETAILS / CONSOLE</span>
            <span
              style={{
                fontSize: "12px",
                color: isProcessing ? "#fbc531" : "#6f7ea8",
              }}
            >
              {runPhase}
            </span>
          </div>

          {isProcessing && (
            <div
              style={{
                position: "absolute",
                top: 41,
                left: 0,
                right: 0,
                height: "3px",
                background:
                  "linear-gradient(90deg, transparent, #fbc531, transparent)",
                backgroundSize: "200% 100%",
                animation: "consoleShimmer 1.2s linear infinite",
                opacity: 0.9,
              }}
            />
          )}

          <div
            style={{
              flex: 1,
              padding: "12px 16px",
              overflowY: "auto",
              fontSize: "13px",
              fontFamily: "monospace",
              color: error ? "#ffb4b4" : "#7f8fa6",
              whiteSpace: "pre-wrap",
              transition: "opacity 0.2s ease",
              opacity: isProcessing ? 0.92 : 1,
            }}
          >
            {isProcessing ? (
              <div
                style={{
                  display: "flex",
                  alignItems: "flex-start",
                  gap: "12px",
                  color: "#d7def7",
                }}
              >
                <div
                  style={{
                    width: "14px",
                    height: "14px",
                    border: "2px solid #2f3547",
                    borderTop: "2px solid #fbc531",
                    borderRadius: "50%",
                    animation: "spin 0.9s linear infinite",
                    marginTop: "2px",
                    flexShrink: 0,
                  }}
                />
                <div>
                  <div style={{ fontWeight: 600, color: "#fbc531" }}>
                    Processing source code...
                  </div>
                  <div style={{ marginTop: "6px", color: "#9aa4c7" }}>
                    {runPhase}
                  </div>
                  <div style={{ marginTop: "10px", color: "#6f7ea8" }}>
                    Please wait while AlgoScope instruments, compiles, and executes your code.
                  </div>
                </div>
              </div>
            ) : error ? (
              error
            ) : trace.length > 0 ? (
              `Trace events: ${trace.length}\nCurrent step: ${currentStep}\nCurrent line: ${
                currentLine ?? "None"
              }`
            ) : (
              "Waiting for execution..."
            )}
          </div>
        </div>
      </div>

      <style>
        {`
          @keyframes spin {
            0% { transform: rotate(0deg); }
            100% { transform: rotate(360deg); }
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
