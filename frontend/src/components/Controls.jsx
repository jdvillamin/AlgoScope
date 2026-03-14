import { useEffect, useRef, useState } from "react";

function Controls({ trace, setCurrentStep }) {
  const [playing, setPlaying] = useState(false);
  const intervalRef = useRef(null);
  const traceRef = useRef(trace);

  useEffect(() => { traceRef.current = trace; }, [trace]);

  const clearTimer = () => {
    if (intervalRef.current) {
      clearInterval(intervalRef.current);
      intervalRef.current = null;
    }
  };

  const play = () => {
    if (playing || traceRef.current.length === 0) return;
    setPlaying(true);
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
    }, 500);
  };

  const pause = () => {
    clearTimer();
    setPlaying(false);
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
    </div>
  );
}

export default Controls;
