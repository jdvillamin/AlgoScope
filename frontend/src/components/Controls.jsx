import { useEffect, useRef, useState } from "react";

const SPEEDS = [0.25, 0.5, 1, 1.25, 1.5, 1.75, 2];

function Controls({ trace, setCurrentStep, setActiveTab }) {
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

  return (
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
  );
}

export default Controls;
