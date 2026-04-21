import { useEffect, useRef } from "react";
import MonacoEditor from "@monaco-editor/react";

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
  stdin,
  setStdin,
  lockToLine,
  setLockToLine,
  onDeInstrument,
  securityViolations = [],
  onHide,
  editorWidth = 560,
  isMobile = false,
}) {
  const editorRef = useRef(null);
  const monacoRef = useRef(null);
  const decorationsRef = useRef(null);

  const displayedCode =
    activeTab === "instrumented" ? instrumentedCode || "" : code || "";

  const isInstrumentedTab = activeTab === "instrumented";

  const handleMount = (editor, monaco) => {
    editorRef.current = editor;
    monacoRef.current = monaco;

    monaco.editor.defineTheme("algoscope-dark", {
      base: "vs-dark",
      inherit: true,
      rules: [],
      colors: {
        "editor.background": "#080d15",
        "editor.foreground": "#cdd9f0",
        "editor.lineHighlightBackground": "#0e1520",
        "editor.lineHighlightBorder": "#0e1520",
        "editorLineNumber.foreground": "#3d5270",
        "editorLineNumber.activeForeground": "#8fa3c8",
        "editorCursor.foreground": "#4b8cf7",
        "editorGutter.background": "#080d15",
        "editorIndentGuide.background1": "#111c2c",
        "editorIndentGuide.activeBackground1": "#1a2535",
        "scrollbarSlider.background": "#1a253580",
        "scrollbarSlider.hoverBackground": "#243347a0",
        "scrollbarSlider.activeBackground": "#243347",
      },
    });
    monaco.editor.setTheme("algoscope-dark");

    decorationsRef.current = editor.createDecorationsCollection([]);
  };

  // Current-line highlight decoration
  useEffect(() => {
    const editor = editorRef.current;
    const monaco = monacoRef.current;
    const decos = decorationsRef.current;
    if (!editor || !monaco || !decos) return;

    if (!isRunning || !currentLine || isInstrumentedTab) {
      decos.clear();
      return;
    }

    decos.set([
      {
        range: new monaco.Range(currentLine, 1, currentLine, 1),
        options: {
          isWholeLine: true,
          className: "algoscope-current-line",
          linesDecorationsClassName: "algoscope-current-line-gutter",
        },
      },
    ]);
  }, [currentLine, isRunning, isInstrumentedTab, displayedCode]);

  // Lock-to-line auto-scroll
  useEffect(() => {
    const editor = editorRef.current;
    if (!editor || !isRunning || !currentLine || isInstrumentedTab || !lockToLine) return;
    editor.revealLineInCenter(currentLine);
  }, [currentLine, isRunning, isInstrumentedTab, lockToLine]);

  // Security violation markers
  useEffect(() => {
    const monaco = monacoRef.current;
    const editor = editorRef.current;
    if (!monaco || !editor) return;

    const model = editor.getModel();
    if (!model) return;

    if (isInstrumentedTab || securityViolations.length === 0) {
      monaco.editor.setModelMarkers(model, "security", []);
      return;
    }

    const markers = securityViolations.map((v) => ({
      startLineNumber: v.line,
      startColumn: 1,
      endLineNumber: v.line,
      endColumn: model.getLineMaxColumn(v.line),
      message: v.message,
      severity: monaco.MarkerSeverity.Error,
      source: "Security",
    }));
    monaco.editor.setModelMarkers(model, "security", markers);
  }, [securityViolations, isInstrumentedTab]);

  const hasViolations = !isInstrumentedTab && securityViolations.length > 0;

  const iconBtn = (active = true) => ({
    width: isMobile ? "28px" : "32px",
    height: isMobile ? "28px" : "32px",
    borderRadius: isMobile ? "6px" : "8px",
    background: active ? "#19243a" : "transparent",
    border: `1px solid ${active ? "#243347" : "transparent"}`,
    color: isProcessing ? "#506888" : "#8fa3c8",
    cursor: isProcessing ? "not-allowed" : "pointer",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    fontSize: isMobile ? "13px" : "15px",
    padding: 0,
    lineHeight: 1,
    flexShrink: 0,
  });

  const tabStyle = (selected) => ({
    padding: isMobile ? "4px 1px" : "6px 2px",
    background: "none",
    border: "none",
    borderBottom: selected ? "2px solid #4b8cf7" : "2px solid transparent",
    color: selected ? "#c8d8f0" : "#647e9c",
    cursor: "pointer",
    fontSize: isMobile ? "11px" : "13px",
    fontWeight: selected ? 600 : 500,
    letterSpacing: "0.1px",
    marginBottom: "-1px",
    transition: "color 0.15s, border-color 0.15s",
    whiteSpace: "nowrap",
    overflow: "hidden",
    textOverflow: "ellipsis",
    flexShrink: 1,
    minWidth: 0,
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
          padding: isMobile ? "0 8px" : "0 16px",
          borderBottom: "1px solid #1a2535",
          display: "flex",
          justifyContent: "space-between",
          alignItems: "stretch",
          gap: isMobile ? "6px" : "16px",
          height: isMobile ? "36px" : "44px",
          overflow: "hidden",
          minWidth: 0,
        }}
      >
        {/* Tabs */}
        <div style={{ display: "flex", alignItems: "stretch", gap: isMobile ? "10px" : "20px", minWidth: 0, overflow: "hidden" }}>
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
        <div style={{ display: "flex", gap: "8px", alignItems: "center", flexShrink: 0 }}>
          <button
            onClick={() => setLockToLine((v) => !v)}
            style={{
              ...iconBtn(lockToLine),
              color: lockToLine ? "#f0a429" : "#647e9c",
              border: `1px solid ${lockToLine ? "#3d2e10" : "#1a2535"}`,
              background: lockToLine ? "#1a1810" : "transparent",
              cursor: "pointer",
            }}
            title={lockToLine ? "Auto-scroll to current line (on)" : "Auto-scroll to current line (off)"}
          >
            ⊙
          </button>

          {isInstrumentedTab && (
            <button
              onClick={!isProcessing ? onDeInstrument : undefined}
              style={{
                ...iconBtn(),
                cursor: isProcessing ? "not-allowed" : "pointer",
              }}
              title="Generate raw code from instrumented code"
            >
              ⇤
            </button>
          )}

          <button
            onClick={!isProcessing && !hasViolations ? onRun : undefined}
            style={{
              ...iconBtn(),
              width: "auto",
              padding: "0 12px",
              gap: "6px",
              fontSize: "12.5px",
              fontWeight: 600,
              color: hasViolations ? "#f87171" : isProcessing ? "#506888" : "#4b8cf7",
              border: `1px solid ${hasViolations ? "#5c1e1e" : isProcessing ? "#1a2535" : "#1e3a6e"}`,
              background: hasViolations ? "#1a0f0f" : isProcessing ? "#0f1928" : "#0f1e3a",
              cursor: isProcessing || hasViolations ? "not-allowed" : "pointer",
            }}
            title={hasViolations ? "Fix security violations before running" : isProcessing ? "Processing..." : isInstrumentedTab ? "Compile & run" : "Instrument"}
          >
            {isProcessing ? "⋯" : hasViolations ? "!" : "▶"}{(isMobile || editorWidth >= 480) && <>&nbsp;{isProcessing ? "Running" : hasViolations ? "Blocked" : isInstrumentedTab ? "Run" : "Instrument"}</>}
          </button>

          <button
            onClick={onReset}
            style={iconBtn()}
            title="Reset"
          >
            ↺
          </button>

          {onHide && !isMobile && (
            <button
              onClick={onHide}
              style={iconBtn()}
              title="Hide editor panel"
            >
              ›
            </button>
          )}
        </div>
      </div>

      {/* Editor body */}
      <div style={{ flex: 1, minHeight: 0, position: "relative", background: "#080d15" }}>
        <MonacoEditor
          height="100%"
          language="c"
          value={displayedCode}
          onChange={(value) => {
            if (isProcessing || isRunning) return;
            if (isInstrumentedTab) {
              setInstrumentedCode?.(value ?? "");
            } else {
              setCode(value ?? "");
            }
          }}
          onMount={handleMount}
          options={{
            readOnly: isRunning || isProcessing,
            fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
            fontSize: isMobile ? 11 : 13.5,
            lineHeight: isMobile ? 18 : 22,
            minimap: { enabled: false },
            scrollBeyondLastLine: false,
            smoothScrolling: true,
            renderLineHighlight: "none",
            tabSize: 4,
            automaticLayout: true,
            padding: { top: isMobile ? 8 : 16, bottom: isMobile ? 8 : 16 },
            scrollbar: {
              verticalScrollbarSize: isMobile ? 6 : 10,
              horizontalScrollbarSize: isMobile ? 6 : 10,
            },
            overviewRulerLanes: 0,
            hideCursorInOverviewRuler: true,
            overviewRulerBorder: false,
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
      </div>

      {/* Stdin */}
      <div
        style={{
          borderTop: "1px solid #1a2535",
          background: "#0e1520",
        }}
      >
        <div
          style={{
            padding: isMobile ? "5px 12px" : "7px 16px",
            borderBottom: "1px solid #1a2535",
            display: "flex",
            justifyContent: "space-between",
            alignItems: "center",
          }}
        >
          <span
            style={{
              fontSize: isMobile ? "9px" : "11px",
              fontWeight: 600,
              letterSpacing: "0.8px",
              color: "#647e9c",
              textTransform: "uppercase",
            }}
          >
            Standard Input
          </span>
          <span
            style={{
              fontSize: isMobile ? "9px" : "11px",
              color: "#506888",
            }}
          >
            {isMobile ? "Max: 20" : "Numbers must not exceed 20"}
          </span>
        </div>
        <textarea
          value={stdin}
          onChange={(e) => setStdin(e.target.value)}
          readOnly={isProcessing}
          placeholder="Enter input values (e.g. 5 3 8 1 ...)"
          spellCheck={false}
          style={{
            width: "100%",
            height: isMobile ? "40px" : "56px",
            resize: "none",
            border: "none",
            outline: "none",
            background: "#080d15",
            color: "#cdd9f0",
            padding: isMobile ? "6px 12px" : "10px 16px",
            fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
            fontSize: isMobile ? "11px" : "13px",
            lineHeight: isMobile ? "16px" : "20px",
            boxSizing: "border-box",
            caretColor: "#4b8cf7",
            opacity: isProcessing ? 0.6 : 1,
            transition: "opacity 0.2s ease",
          }}
        />
      </div>
    </div>
  );
}

export default Editor;
