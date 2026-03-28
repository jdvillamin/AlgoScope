import { useState, useMemo } from "react";
import Editor from "./components/Editor";
import Canvas from "./components/Canvas";
import Controls from "./components/Controls";
import API from "./api/backend";

function App() {
  const [code, setCode] = useState("");
  const [instrumentedCode, setInstrumentedCode] = useState("");
  const [activeTab, setActiveTab] = useState("raw");
  const [stdin, setStdin] = useState("");

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

    const numbers = stdin.match(/-?\d+/g) || [];
    for (const n of numbers) {
      if (Math.abs(parseInt(n, 10)) > 20) {
        setError(`Input number ${n} exceeds the limit of 20.`);
        return;
      }
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
        stdin: stdin,
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
        background: "#080d15",
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
            height: "100px",
            borderTop: "1px solid #1a2535",
            background: "#0e1520",
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
            <span style={{ fontSize: "11px", fontWeight: 600, letterSpacing: "0.8px", color: "#4e6180", textTransform: "uppercase" }}>
              Console
            </span>
            <span style={{ fontSize: "12px", fontWeight: 500, color: isProcessing ? "#f0a429" : "#3d5270" }}>
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
                background: "linear-gradient(90deg, transparent, #f0a429, transparent)",
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
              fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
              color: error ? "#f87171" : "#4e6180",
              whiteSpace: "pre-wrap",
              lineHeight: 1.6,
              transition: "opacity 0.2s ease",
              opacity: isProcessing ? 0.85 : 1,
            }}
          >
            {isProcessing ? (
              <div style={{ display: "flex", alignItems: "flex-start", gap: "12px", color: "#c8d8f0" }}>
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
                  <div style={{ fontWeight: 600, color: "#f0a429", fontFamily: "inherit" }}>
                    Processing...
                  </div>
                  <div style={{ marginTop: "5px", color: "#7b96bf", fontFamily: "inherit" }}>
                    {runPhase}
                  </div>
                </div>
              </div>
            ) : error ? (
              error
            ) : trace.length > 0 ? (
              `Trace events: ${trace.length}\nCurrent step: ${currentStep}\nCurrent line: ${currentLine ?? "—"}`
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
