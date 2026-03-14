import { useEffect, useRef, useState } from "react";

function Controls({ trace, setCurrentStep }) {
  const [playing, setPlaying] = useState(false);
  const intervalRef = useRef(null);
  const traceRef = useRef(trace);

  useEffect(() => {
    traceRef.current = trace;
  }, [trace]);

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
        const currentTraceLength = traceRef.current.length;

        if (next >= currentTraceLength) {
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

  useEffect(() => {
    return () => {
      clearTimer();
    };
  }, []);

  const baseButton = {
    width: "42px",
    height: "42px",
    borderRadius: "10px",
    background: "#1c2230",
    border: "1px solid #2b3245",
    color: "#cfd8ff",
    fontSize: "16px",
    cursor: "pointer",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    transition: "all 0.2s ease",
  };

  const effectivePlaying = playing && trace.length > 0;

  return (
    <div
      style={{
        display: "flex",
        alignItems: "center",
        justifyContent: "center",
        gap: "18px",
        width: "100%",
      }}
    >
      <button
        onClick={() => setCurrentStep((s) => Math.max(0, s - 1))}
        style={baseButton}
        title="Step Back"
      >
        ⟵
      </button>

      <button
        onClick={effectivePlaying ? pause : play}
        disabled={trace.length === 0}
        style={{
          ...baseButton,
          width: "50px",
          height: "50px",
          fontSize: "18px",
          opacity: trace.length === 0 ? 0.4 : 1,
        }}
        title={effectivePlaying ? "Pause" : "Play"}
      >
        {effectivePlaying ? "❚❚" : "▶"}
      </button>

      <button
        onClick={() =>
          setCurrentStep((s) => Math.min(Math.max(trace.length - 1, 0), s + 1))
        }
        style={baseButton}
        title="Step Forward"
      >
        ⟶
      </button>
    </div>
  );
}

export default Controls;
