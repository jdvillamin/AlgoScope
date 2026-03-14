import { useEffect, useRef, useCallback } from "react";

function Editor({
  code,
  setCode,
  instrumentedCode = "",
  setInstrumentedCode,
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

  useEffect(() => { syncOverlay(); }, [syncOverlay, displayedCode]);
  useEffect(() => { scrollToCurrentLine(); }, [scrollToCurrentLine]);

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

  const iconBtn = (active = true) => ({
    width: "32px",
    height: "32px",
    borderRadius: "8px",
    background: active ? "#19243a" : "transparent",
    border: `1px solid ${active ? "#243347" : "transparent"}`,
    color: isProcessing ? "#3d5270" : "#8fa3c8",
    cursor: isProcessing ? "not-allowed" : "pointer",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    fontSize: "15px",
    padding: 0,
    lineHeight: 1,
    flexShrink: 0,
  });

  const tabStyle = (selected) => ({
    padding: "6px 2px",
    background: "none",
    border: "none",
    borderBottom: selected ? "2px solid #4b8cf7" : "2px solid transparent",
    color: selected ? "#c8d8f0" : "#4e6180",
    cursor: "pointer",
    fontSize: "13px",
    fontWeight: selected ? 600 : 500,
    letterSpacing: "0.1px",
    marginBottom: "-1px",
    transition: "color 0.15s, border-color 0.15s",
  });

  return (
    <div
      style={{
        width: "100%",
        height: "100%",
        display: "flex",
        flexDirection: "column",
        background: "#0e1520",
        color: "#dce7f8",
      }}
    >
      {/* Header */}
      <div
        style={{
          padding: "0 16px",
          borderBottom: "1px solid #1a2535",
          display: "flex",
          justifyContent: "space-between",
          alignItems: "stretch",
          gap: "16px",
          height: "44px",
        }}
      >
        {/* Tabs */}
        <div style={{ display: "flex", alignItems: "stretch", gap: "20px" }}>
          <button
            onClick={() => setActiveTab("raw")}
            style={tabStyle(activeTab === "raw")}
            title="Original source code"
          >
            Raw code
          </button>
          <button
            onClick={() => setActiveTab("instrumented")}
            style={tabStyle(activeTab === "instrumented")}
            title="Instrumented code"
          >
            Instrumented code
          </button>
        </div>

        {/* Actions */}
        <div style={{ display: "flex", gap: "8px", alignItems: "center" }}>
          <button
            onClick={!isProcessing ? onRun : undefined}
            style={{
              ...iconBtn(),
              width: "auto",
              padding: "0 12px",
              gap: "6px",
              fontSize: "12.5px",
              fontWeight: 600,
              color: isProcessing ? "#3d5270" : "#4b8cf7",
              border: `1px solid ${isProcessing ? "#1a2535" : "#1e3a6e"}`,
              background: isProcessing ? "#0f1928" : "#0f1e3a",
            }}
            title={isProcessing ? "Processing..." : "Compile & run"}
          >
            {isProcessing ? "⋯" : "▶"}&nbsp;{isProcessing ? "Running" : "Run"}
          </button>

          <button
            onClick={onReset}
            style={iconBtn()}
            title="Reset"
          >
            ↺
          </button>
        </div>
      </div>

      {/* Editor body */}
      <div
        style={{
          flex: 1,
          display: "flex",
          background: "#080d15",
          fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
          fontSize: "13.5px",
          lineHeight: `${lineHeight}px`,
          minHeight: 0,
        }}
      >
        {/* Line numbers */}
        <div
          ref={lineNumberRef}
          style={{
            padding: `${topPadding}px 12px`,
            background: "#080d15",
            color: "#2a3d56",
            textAlign: "right",
            userSelect: "none",
            overflow: "hidden",
            minWidth: "52px",
            borderRight: "1px solid #111c2c",
          }}
        >
          {lines.map((_, i) => (
            <div
              key={i}
              style={{
                height: `${lineHeight}px`,
                color:
                  !isInstrumentedTab && isRunning && currentLine === i + 1
                    ? "#f0a429"
                    : "#2a3d56",
                fontWeight: !isInstrumentedTab && isRunning && currentLine === i + 1 ? 600 : 400,
                transition: "color 0.1s",
              }}
            >
              {i + 1}
            </div>
          ))}
        </div>

        {/* Code area */}
        <div style={{ position: "relative", flex: 1 }}>
          <div
            ref={highlightRef}
            style={{
              position: "absolute",
              left: 0,
              right: 0,
              height: `${lineHeight}px`,
              background: "rgba(240, 164, 41, 0.08)",
              borderLeft: "2px solid rgba(240, 164, 41, 0.5)",
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
                background: "rgba(8, 13, 21, 0.3)",
                zIndex: 2,
                pointerEvents: "none",
              }}
            />
          )}

          <textarea
            ref={textareaRef}
            value={displayedCode}
            readOnly={isRunning || isProcessing}
            wrap="off"
            onChange={(e) => {
              if (isProcessing) return;
              if (isInstrumentedTab) {
                setInstrumentedCode?.(e.target.value);
              } else {
                setCode(e.target.value);
              }
            }}
            onScroll={syncOverlay}
            spellCheck={false}
            style={{
              width: "100%",
              height: "100%",
              resize: "none",
              border: "none",
              outline: "none",
              background: "transparent",
              color: isInstrumentedTab ? "#a8bedd" : "#cdd9f0",
              padding: `${topPadding}px 16px`,
              fontFamily: "inherit",
              fontSize: "inherit",
              lineHeight: `${lineHeight}px`,
              overflow: "auto",
              whiteSpace: "pre",
              tabSize: 4,
              position: "relative",
              zIndex: 1,
              opacity: isProcessing ? 0.6 : 1,
              transition: "opacity 0.2s ease",
              caretColor: "#4b8cf7",
            }}
          />
        </div>
      </div>
    </div>
  );
}

export default Editor;
