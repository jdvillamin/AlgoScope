import { useState, useEffect, useCallback, useRef, useMemo } from "react";

const STORAGE_KEY = "algoscope:tutorial-done";

const STEPS = [
  {
    target: null,
    title: "Welcome to AlgoScope",
    body: "AlgoScope visualizes C algorithms and data structures in real-time. Let's take a quick tour of the interface.",
    position: "center",
  },
  {
    target: "[data-tutorial='file-panel']",
    title: "File Panel",
    body: "Manage your files here. Create new files, import existing ones, or load pre-built samples to explore different algorithms.",
    position: "right",
  },
  {
    target: "[data-tutorial='samples']",
    title: "Sample Algorithms",
    body: "Try one of the built-in samples to see AlgoScope in action. Each sample demonstrates a different data structure or algorithm.",
    position: "right",
  },
  {
    target: "[data-tutorial='editor']",
    title: "Code Editor",
    body: "Write or edit your C code here. The editor supports syntax highlighting and will show the current execution line during playback.",
    position: "left",
  },
  {
    target: "[data-tutorial='run-btn']",
    title: "Instrument & Run",
    body: "Click here to instrument your code. This adds tracing calls so the visualizer can track data structures. Then run the instrumented code to generate a trace.",
    position: "left",
  },
  {
    target: "[data-tutorial='canvas']",
    title: "Visualization Canvas",
    body: "Data structures appear here as your program runs. You can pan around and drag objects to rearrange them.",
    position: "right",
  },
  {
    target: "[data-tutorial='controls']",
    title: "Playback Controls",
    body: "Step through the execution one event at a time, or press play to animate. You can also adjust the playback speed.",
    position: "top",
  },
  {
    target: "[data-tutorial='console']",
    title: "Console Output",
    body: "Program output, errors, and trace info appear here. Keep an eye on it for compilation errors or runtime messages.",
    position: "left",
  },
  {
    target: null,
    title: "You're all set!",
    body: "Load a sample from the file panel to get started, or write your own C code. Happy visualizing!",
    position: "center",
  },
];

function Tutorial() {
  const [visible, setVisible] = useState(false);
  const [step, setStep] = useState(0);
  const [resizeTick, setResizeTick] = useState(0);
  const tooltipRef = useRef(null);

  useEffect(() => {
    if (localStorage.getItem(STORAGE_KEY)) return;
    const timer = setTimeout(() => setVisible(true), 600);
    return () => clearTimeout(timer);
  }, []);

  useEffect(() => {
    if (!visible) return;
    const handler = () => setResizeTick((t) => t + 1);
    window.addEventListener("resize", handler);
    return () => window.removeEventListener("resize", handler);
  }, [visible]);

  const spotlightRect = useMemo(() => {
    void resizeTick;
    const s = STEPS[step];
    if (!s?.target) return null;
    const el = document.querySelector(s.target);
    if (!el) return null;
    const r = el.getBoundingClientRect();
    const pad = 8;
    return {
      x: r.left - pad,
      y: r.top - pad,
      w: r.width + pad * 2,
      h: r.height + pad * 2,
    };
  }, [step, resizeTick]);

  const dismiss = useCallback(() => {
    setVisible(false);
    localStorage.setItem(STORAGE_KEY, "1");
  }, []);

  const next = useCallback(() => {
    if (step >= STEPS.length - 1) {
      dismiss();
    } else {
      setStep((s) => s + 1);
    }
  }, [step, dismiss]);

  const prev = useCallback(() => {
    setStep((s) => Math.max(0, s - 1));
  }, []);

  if (!visible) return null;

  const current = STEPS[step];
  const isFirst = step === 0;
  const isLast = step === STEPS.length - 1;
  const isCentered = current.position === "center";

  const getTooltipStyle = () => {
    const base = {
      position: "fixed",
      zIndex: 10002,
      background: "#0e1a2e",
      border: "1px solid #1e3a6e",
      borderRadius: "12px",
      padding: "20px 24px",
      maxWidth: "340px",
      width: "340px",
      boxShadow: "0 8px 32px rgba(0,0,0,0.6), 0 0 0 1px rgba(75,140,247,0.1)",
    };

    if (isCentered || !spotlightRect) {
      return {
        ...base,
        top: "50%",
        left: "50%",
        transform: "translate(-50%, -50%)",
      };
    }

    const margin = 16;
    const r = spotlightRect;

    switch (current.position) {
      case "right":
        return {
          ...base,
          top: `${Math.max(16, r.y)}px`,
          left: `${r.x + r.w + margin}px`,
        };
      case "left":
        return {
          ...base,
          top: `${Math.max(16, r.y)}px`,
          right: `${window.innerWidth - r.x + margin}px`,
        };
      case "top":
        return {
          ...base,
          bottom: `${window.innerHeight - r.y + margin}px`,
          left: `${Math.max(16, r.x + r.w / 2 - 170)}px`,
        };
      case "bottom":
        return {
          ...base,
          top: `${r.y + r.h + margin}px`,
          left: `${Math.max(16, r.x + r.w / 2 - 170)}px`,
        };
      default:
        return {
          ...base,
          top: "50%",
          left: "50%",
          transform: "translate(-50%, -50%)",
        };
    }
  };

  return (
    <>
      <svg
        style={{
          position: "fixed",
          inset: 0,
          width: "100%",
          height: "100%",
          zIndex: 10000,
          pointerEvents: "none",
        }}
      >
        <defs>
          <mask id="tutorial-mask">
            <rect x="0" y="0" width="100%" height="100%" fill="white" />
            {spotlightRect && (
              <rect
                x={spotlightRect.x}
                y={spotlightRect.y}
                width={spotlightRect.w}
                height={spotlightRect.h}
                rx="8"
                fill="black"
              />
            )}
          </mask>
        </defs>
        <rect
          x="0"
          y="0"
          width="100%"
          height="100%"
          fill="rgba(2, 4, 10, 0.75)"
          mask="url(#tutorial-mask)"
        />
      </svg>

      {spotlightRect && (
        <div
          style={{
            position: "fixed",
            left: spotlightRect.x,
            top: spotlightRect.y,
            width: spotlightRect.w,
            height: spotlightRect.h,
            borderRadius: "8px",
            border: "2px solid rgba(75, 140, 247, 0.4)",
            boxShadow: "0 0 20px rgba(75, 140, 247, 0.15)",
            zIndex: 10001,
            pointerEvents: "none",
            transition: "all 0.3s ease",
          }}
        />
      )}

      <div
        style={{
          position: "fixed",
          inset: 0,
          zIndex: 10001,
          pointerEvents: "auto",
        }}
        onClick={(e) => {
          if (tooltipRef.current && !tooltipRef.current.contains(e.target)) {
            next();
          }
        }}
      />

      <div ref={tooltipRef} style={getTooltipStyle()}>
        <div
          style={{
            display: "flex",
            justifyContent: "space-between",
            alignItems: "flex-start",
            marginBottom: "8px",
          }}
        >
          <div
            style={{
              fontSize: "15px",
              fontWeight: 700,
              color: "#c8d8f0",
              lineHeight: 1.3,
            }}
          >
            {current.title}
          </div>
          <button
            onClick={dismiss}
            style={{
              background: "none",
              border: "none",
              color: "#506888",
              fontSize: "18px",
              cursor: "pointer",
              padding: "0 0 0 8px",
              lineHeight: 1,
            }}
            title="Skip tutorial"
          >
            x
          </button>
        </div>

        <div
          style={{
            fontSize: "13px",
            color: "#8fa3c8",
            lineHeight: 1.6,
            marginBottom: "16px",
          }}
        >
          {current.body}
        </div>

        <div
          style={{
            display: "flex",
            justifyContent: "space-between",
            alignItems: "center",
          }}
        >
          <span
            style={{
              fontSize: "12px",
              color: "#3d5270",
              fontWeight: 600,
            }}
          >
            {step + 1} / {STEPS.length}
          </span>

          <div style={{ display: "flex", gap: "8px" }}>
            {!isFirst && (
              <button
                onClick={prev}
                style={{
                  padding: "6px 14px",
                  borderRadius: "6px",
                  border: "1px solid #1e2d42",
                  background: "#0f1928",
                  color: "#8fa3c8",
                  fontSize: "12.5px",
                  fontWeight: 600,
                  cursor: "pointer",
                  fontFamily: "inherit",
                }}
              >
                Back
              </button>
            )}
            <button
              onClick={next}
              style={{
                padding: "6px 14px",
                borderRadius: "6px",
                border: "1px solid #1e3a6e",
                background: "#0f1e3a",
                color: "#4b8cf7",
                fontSize: "12.5px",
                fontWeight: 600,
                cursor: "pointer",
                fontFamily: "inherit",
              }}
            >
              {isLast ? "Get Started" : "Next"}
            </button>
          </div>
        </div>
      </div>
    </>
  );
}

export default Tutorial;
