import { useEffect, useRef, useState } from "react";

const SPEEDS = [0.25, 0.5, 1, 1.25, 1.5, 1.75, 2];

function Controls({ trace, currentStep, setCurrentStep, setActiveTab }) {
  const barRef = useRef(null);
  const [hoverRatio, setHoverRatio] = useState(null);
  const [playing, setPlaying] = useState(false);
  const [speed, setSpeed] = useState(1);
  const intervalRef = useRef(null);
  const traceRef = useRef(trace);
  const speedRef = useRef(speed);

  useEffect(() => { traceRef.current = trace; }, [trace]);
  useEffect(() => { speedRef.current = speed; }, [speed]);

  const clearTimer = () => {
    if (intervalRef.current) {
      clearInterval(intervalRef.current);
      intervalRef.current = null;
    }
  };

  const startInterval = (spd) => {
    clearTimer();
    intervalRef.current = setInterval(() => {
      setCurrentStep((prev) => {
        const next = prev + 1;
        if (next >= traceRef.current.length) {
          clearTimer();
          setPlaying(false);
          return prev;
        }
        return next;
      });
    }, 500 / spd);
  };

  const play = () => {
    if (playing || traceRef.current.length === 0) return;
    setPlaying(true);
    setActiveTab("raw");
    startInterval(speedRef.current);
  };

  const pause = () => {
    clearTimer();
    setPlaying(false);
  };

  const cycleSpeed = () => {
    setSpeed((prev) => {
      const idx = SPEEDS.indexOf(prev);
      const next = SPEEDS[(idx + 1) % SPEEDS.length];
      if (playing) startInterval(next);
      return next;
    });
  };

  useEffect(() => () => clearTimer(), []);

  const disabled = trace.length === 0;
  const effectivePlaying = playing && !disabled;

  const stepBtn = {
    width: "36px",
    height: "36px",
    borderRadius: "10px",
    background: "#131d2e",
    border: "1px solid #1e2d42",
    color: disabled ? "#243347" : "#7b96bf",
    cursor: disabled ? "default" : "pointer",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    fontSize: "16px",
    transition: "all 0.15s ease",
  };

  const playBtn = {
    width: "44px",
    height: "44px",
    borderRadius: "12px",
    background: disabled ? "#0f1928" : "#0f1e3a",
    border: `1px solid ${disabled ? "#1a2535" : "#1e3a6e"}`,
    color: disabled ? "#243347" : "#4b8cf7",
    cursor: disabled ? "default" : "pointer",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    fontSize: "18px",
    transition: "all 0.15s ease",
  };

  const lastIndex = Math.max(trace.length - 1, 0);
  const ratio = disabled ? 0 : lastIndex === 0 ? 0 : currentStep / lastIndex;
  const fillPct = Math.min(100, Math.max(0, ratio * 100));
  const hoverPct = hoverRatio == null ? null : Math.min(100, Math.max(0, hoverRatio * 100));

  const seekFromEvent = (e) => {
    if (disabled || !barRef.current) return null;
    const rect = barRef.current.getBoundingClientRect();
    const r = (e.clientX - rect.left) / rect.width;
    return Math.min(1, Math.max(0, r));
  };

  const handleBarClick = (e) => {
    const r = seekFromEvent(e);
    if (r == null) return;
    pause();
    setCurrentStep(Math.round(r * lastIndex));
  };

  const handleBarMove = (e) => {
    const r = seekFromEvent(e);
    if (r != null) setHoverRatio(r);
  };

  return (
    <div
      style={{
        display: "flex",
        flexDirection: "column",
        alignItems: "stretch",
        gap: "10px",
        width: "100%",
        padding: "0 24px",
        boxSizing: "border-box",
      }}
    >
      <div
        ref={barRef}
        onClick={handleBarClick}
        onMouseMove={handleBarMove}
        onMouseLeave={() => setHoverRatio(null)}
        title={disabled ? "No trace loaded" : `Step ${currentStep} / ${lastIndex}`}
        style={{
          position: "relative",
          height: "6px",
          borderRadius: "3px",
          background: "#131d2e",
          border: "1px solid #1a2535",
          cursor: disabled ? "default" : "pointer",
          overflow: "hidden",
        }}
      >
        {hoverPct != null && !disabled && (
          <div
            style={{
              position: "absolute",
              inset: 0,
              width: `${hoverPct}%`,
              background: "#243854",
            }}
          />
        )}
        <div
          style={{
            position: "absolute",
            inset: 0,
            width: `${fillPct}%`,
            background: disabled
              ? "#1a2535"
              : "linear-gradient(90deg, #3d6fc4 0%, #4b8cf7 100%)",
            boxShadow: disabled ? "none" : "0 0 8px rgba(75,140,247,0.45)",
            transition: "width 0.12s linear",
          }}
        />
      </div>
      <div
        style={{
          display: "flex",
          alignItems: "center",
          justifyContent: "center",
          gap: "12px",
          width: "100%",
        }}
      >
      <button
        onClick={() => !disabled && setCurrentStep((s) => Math.max(0, s - 1))}
        style={stepBtn}
        title="Step back"
      >
        ←
      </button>

      <button
        onClick={effectivePlaying ? pause : play}
        disabled={disabled}
        style={playBtn}
        title={effectivePlaying ? "Pause" : "Play"}
      >
        {effectivePlaying ? "⏸" : "▶"}
      </button>

      <button
        onClick={() => !disabled && setCurrentStep((s) => Math.min(Math.max(trace.length - 1, 0), s + 1))}
        style={stepBtn}
        title="Step forward"
      >
        →
      </button>

      <button
        onClick={cycleSpeed}
        style={{
          ...stepBtn,
          width: "auto",
          padding: "0 10px",
          fontSize: "12px",
          fontWeight: 600,
          fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
          color: disabled ? "#243347" : speed === 1 ? "#647e9c" : "#f0a429",
          border: `1px solid ${speed === 1 ? "#1e2d42" : "#3d2e10"}`,
          background: speed === 1 ? "#131d2e" : "#1a1810",
        }}
        title="Cycle playback speed"
      >
        {speed}x
      </button>
      </div>
    </div>
  );
}

export default Controls;
