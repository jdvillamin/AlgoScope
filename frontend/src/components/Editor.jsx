import { useEffect, useRef, useCallback } from "react";

function Editor({
  code,
  setCode,
  instrumentedCode = "",
  currentLine,
  isRunning,
  isProcessing,
  onRun,
  onReset,
  activeTab,
  setActiveTab,
}) {
  const textareaRef = useRef(null);
  const lineNumberRef = useRef(null);
  const highlightRef = useRef(null);

  const lineHeight = 22;
  const topPadding = 16;

  const displayedCode =
    activeTab === "instrumented" ? instrumentedCode || "" : code || "";

  const lines = displayedCode.split("\n");
  const isInstrumentedTab = activeTab === "instrumented";

  const syncLineNumberScroll = useCallback(() => {
    if (!textareaRef.current || !lineNumberRef.current) return;
    lineNumberRef.current.scrollTop = textareaRef.current.scrollTop;
  }, []);

  const updateHighlightPosition = useCallback(() => {
    const textarea = textareaRef.current;
    const highlight = highlightRef.current;

    if (!textarea || !highlight) return;

    if (!isRunning || !currentLine || isInstrumentedTab) {
      highlight.style.display = "none";
      return;
    }

    const top = topPadding + (currentLine - 1) * lineHeight - textarea.scrollTop;

    highlight.style.display = "block";
    highlight.style.top = `${top}px`;
    highlight.style.height = `${lineHeight}px`;
  }, [currentLine, isRunning, isInstrumentedTab]);

  const syncOverlay = useCallback(() => {
    syncLineNumberScroll();
    updateHighlightPosition();
  }, [syncLineNumberScroll, updateHighlightPosition]);

  const scrollToCurrentLine = useCallback(() => {
    const textarea = textareaRef.current;
    if (!textarea || !isRunning || !currentLine || isInstrumentedTab) return;

    const desiredTop =
      topPadding +
      (currentLine - 1) * lineHeight -
      textarea.clientHeight / 2 +
      lineHeight / 2;

    const maxScroll = Math.max(0, textarea.scrollHeight - textarea.clientHeight);
    const clampedTop = Math.max(0, Math.min(desiredTop, maxScroll));

    textarea.scrollTop = clampedTop;
    syncOverlay();
  }, [currentLine, isRunning, isInstrumentedTab, syncOverlay]);

  const handleScroll = () => {
    syncOverlay();
  };

  useEffect(() => {
    syncOverlay();
  }, [syncOverlay, displayedCode]);

  useEffect(() => {
    scrollToCurrentLine();
  }, [scrollToCurrentLine]);

  useEffect(() => {
    const textarea = textareaRef.current;
    const lineNumbers = lineNumberRef.current;
    const highlight = highlightRef.current;

    if (textarea) textarea.scrollTop = 0;
    if (lineNumbers) lineNumbers.scrollTop = 0;
    if (highlight) highlight.style.display = "none";

    requestAnimationFrame(() => {
      syncOverlay();
      scrollToCurrentLine();
    });
  }, [activeTab, displayedCode, syncOverlay, scrollToCurrentLine]);

  const iconButton = {
    width: "36px",
    height: "36px",
    borderRadius: "8px",
    background: "#1c2230",
    border: "1px solid #2b3245",
    color: "#cfd8ff",
    cursor: isProcessing ? "not-allowed" : "pointer",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    padding: 0,
    lineHeight: 1,
    opacity: isProcessing ? 0.7 : 1,
    transition: "all 0.2s ease",
  };

  const tabStyle = (selected) => ({
    padding: "8px 14px",
    borderRadius: "8px",
    border: selected ? "1px solid #4c5a79" : "1px solid #2b3245",
    background: selected ? "#1c2230" : "#111722",
    color: selected ? "#ffffff" : "#94a3b8",
    cursor: "pointer",
    fontSize: "13px",
    fontWeight: 600,
  });

  return (
    <div
      style={{
        width: "100%",
        height: "100%",
        display: "flex",
        flexDirection: "column",
        background: "#141821",
        color: "#f5f6fa",
      }}
    >
      <div
        style={{
          padding: "12px 18px",
          borderBottom: "1px solid #1f2533",
          display: "flex",
          justifyContent: "space-between",
          alignItems: "center",
          gap: "16px",
          flexWrap: "wrap",
        }}
      >
        <div style={{ display: "flex", alignItems: "center", gap: "10px" }}>
          <span style={{ fontWeight: 600, fontSize: "14px" }}>Code Editor</span>

          <div style={{ display: "flex", gap: "8px" }}>
            <button
              onClick={() => setActiveTab("raw")}
              style={tabStyle(activeTab === "raw")}
              title="Original source code"
            >
              Raw Code
            </button>

            <button
              onClick={() => setActiveTab("instrumented")}
              style={tabStyle(activeTab === "instrumented")}
              title="Instrumented code returned by backend"
            >
              Instrumented Code
            </button>
          </div>
        </div>

        <div style={{ display: "flex", gap: "10px" }}>
          <button
            onClick={!isProcessing ? onRun : undefined}
            style={iconButton}
            title={isProcessing ? "Processing..." : "Compile & Run"}
          >
            {isProcessing ? "⋯" : "⚡"}
          </button>

          <button onClick={onReset} style={iconButton} title="Reset">
            ⟲
          </button>
        </div>
      </div>

      <div
        style={{
          flex: 1,
          display: "flex",
          background: "#0f141d",
          fontFamily: "Consolas, monospace",
          fontSize: "14px",
          lineHeight: `${lineHeight}px`,
          minHeight: 0,
        }}
      >
        <div
          ref={lineNumberRef}
          style={{
            padding: `${topPadding}px 10px`,
            background: "#0c1017",
            color: "#3e4a5a",
            textAlign: "right",
            userSelect: "none",
            overflow: "hidden",
            minWidth: "56px",
          }}
        >
          {lines.map((_, i) => (
            <div
              key={i}
              style={{
                height: `${lineHeight}px`,
                color:
                  !isInstrumentedTab && isRunning && currentLine === i + 1
                    ? "#fbc531"
                    : "#3e4a5a",
              }}
            >
              {i + 1}
            </div>
          ))}
        </div>

        <div
          style={{
            position: "relative",
            flex: 1,
          }}
        >
          <div
            ref={highlightRef}
            style={{
              position: "absolute",
              left: 0,
              right: 0,
              height: `${lineHeight}px`,
              background: "rgba(251, 197, 49, 0.15)",
              pointerEvents: "none",
              zIndex: 0,
              display: "none",
            }}
          />

          {isProcessing && (
            <div
              style={{
                position: "absolute",
                inset: 0,
                background: "rgba(15, 20, 29, 0.18)",
                zIndex: 2,
                pointerEvents: "none",
              }}
            />
          )}

          <textarea
            ref={textareaRef}
            value={displayedCode}
            readOnly={isRunning || isInstrumentedTab || isProcessing}
            wrap="off"
            onChange={(e) => {
              if (!isInstrumentedTab && !isProcessing) {
                setCode(e.target.value);
              }
            }}
            onScroll={handleScroll}
            spellCheck={false}
            style={{
              width: "100%",
              height: "100%",
              resize: "none",
              border: "none",
              outline: "none",
              background: "transparent",
              color: isInstrumentedTab ? "#cbd5e1" : "#e2e8f0",
              padding: `${topPadding}px`,
              fontFamily: "inherit",
              fontSize: "inherit",
              lineHeight: `${lineHeight}px`,
              overflow: "auto",
              whiteSpace: "pre",
              tabSize: 4,
              position: "relative",
              zIndex: 1,
              opacity: isProcessing ? 0.8 : 1,
              transition: "opacity 0.2s ease",
            }}
          />
        </div>
      </div>
    </div>
  );
}

export default Editor;
