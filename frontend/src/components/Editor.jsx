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
  onInstrument,
  onRunInstrumented,
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
  theme = "dark",
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

    // Monaco renders to canvas and can't read CSS variables, so both themes
    // are defined with literal hex (kept in sync with the --c-* tokens).
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
    monaco.editor.defineTheme("algoscope-light", {
      base: "vs",
      inherit: true,
      rules: [],
      colors: {
        "editor.background": "#ffffff",
        "editor.foreground": "#1b2c46",
        "editor.lineHighlightBackground": "#eef2f8",
        "editor.lineHighlightBorder": "#eef2f8",
        "editorLineNumber.foreground": "#a3b0c4",
        "editorLineNumber.activeForeground": "#4e5e78",
        "editorCursor.foreground": "#2f6fde",
        "editorGutter.background": "#ffffff",
        "editorIndentGuide.background1": "#e3e8ef",
        "editorIndentGuide.activeBackground1": "#cdd6e3",
        "scrollbarSlider.background": "#c0cbd980",
        "scrollbarSlider.hoverBackground": "#a9b6c8a0",
        "scrollbarSlider.activeBackground": "#a9b6c8",
      },
    });
    monaco.editor.setTheme(
      theme === "light" ? "algoscope-light" : "algoscope-dark",
    );

    decorationsRef.current = editor.createDecorationsCollection([]);
  };

  // Swap the Monaco theme when the app theme toggles after mount.
  useEffect(() => {
    const monaco = monacoRef.current;
    if (!monaco) return;
    monaco.editor.setTheme(
      theme === "light" ? "algoscope-light" : "algoscope-dark",
    );
  }, [theme]);

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

  // Raw code is what gets instrumented, so the instrument action is gated on
  // violations regardless of which tab is showing.
  const rawHasViolations = securityViolations.length > 0;
  const hasInstrumented = (instrumentedCode || "").trim().length > 0;
  const showActionLabels = !isMobile && editorWidth >= 540;

  const iconBtn = (active = true) => ({
    width: isMobile ? "28px" : "32px",
    height: isMobile ? "28px" : "32px",
    borderRadius: isMobile ? "6px" : "8px",
    background: active ? "var(--c-bg-accent)" : "transparent",
    border: `1px solid ${active ? "var(--c-border-strong)" : "transparent"}`,
    color: isProcessing ? "var(--c-text-dimmer)" : "var(--c-text-muted)",
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
    borderBottom: selected ? "2px solid var(--c-accent)" : "2px solid transparent",
    color: selected ? "var(--c-text-bright)" : "var(--c-text-dim)",
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
      data-tutorial="editor"
      style={{
        width: "100%",
        height: "100%",
        display: "flex",
        flexDirection: "column",
        background: "var(--c-bg-panel)",
        color: "var(--c-text)",
      }}
    >
      {/* Header */}
      <div
        style={{
          padding: isMobile ? "0 8px" : "0 16px",
          borderBottom: "1px solid var(--c-border-subtle)",
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
              color: lockToLine ? "var(--c-gold)" : "var(--c-text-dim)",
              border: `1px solid ${lockToLine ? "var(--c-border-warn)" : "var(--c-border-subtle)"}`,
              background: lockToLine ? "var(--c-bg-warn)" : "transparent",
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

          {/* Instrument the raw code (adds tracing). Violet accent. */}
          <button
            data-tutorial="instrument-btn"
            onClick={!isProcessing && !rawHasViolations ? onInstrument : undefined}
            style={{
              ...iconBtn(),
              width: "auto",
              padding: "0 10px",
              gap: "5px",
              fontSize: "12.5px",
              fontWeight: 600,
              color: rawHasViolations ? "#f87171" : isProcessing ? "var(--c-text-dimmer)" : "#b29bff",
              border: `1px solid ${rawHasViolations ? "#5c1e1e" : isProcessing ? "var(--c-border-subtle)" : "#3a2a5c"}`,
              background: rawHasViolations ? "#1a0f0f" : isProcessing ? "var(--c-bg-btn)" : "#161226",
              cursor: isProcessing || rawHasViolations ? "not-allowed" : "pointer",
            }}
            title={rawHasViolations ? "Fix security violations before instrumenting" : isProcessing ? "Processing..." : "Instrument raw code (adds tracing)"}
          >
            {rawHasViolations ? "!" : "✦"}{showActionLabels && <>&nbsp;Instrument</>}
          </button>

          {/* Compile & run the instrumented code. Blue accent. Disabled when
              there is no instrumented code to run. */}
          <button
            data-tutorial="run-btn"
            onClick={!isProcessing && hasInstrumented ? onRunInstrumented : undefined}
            style={{
              ...iconBtn(),
              width: "auto",
              padding: "0 10px",
              gap: "5px",
              fontSize: "12.5px",
              fontWeight: 600,
              color: isProcessing ? "var(--c-text-dimmer)" : hasInstrumented ? "var(--c-accent)" : "var(--c-text-faint)",
              border: `1px solid ${isProcessing ? "var(--c-border-subtle)" : hasInstrumented ? "var(--c-border-accent)" : "var(--c-border-subtle)"}`,
              background: isProcessing ? "var(--c-bg-btn)" : hasInstrumented ? "var(--c-bg-accent)" : "var(--c-bg-btn-off)",
              cursor: isProcessing || !hasInstrumented ? "not-allowed" : "pointer",
              opacity: hasInstrumented || isProcessing ? 1 : 0.55,
            }}
            title={
              !hasInstrumented
                ? "No instrumented code yet — click Instrument first"
                : isProcessing
                ? "Processing..."
                : "Compile & run instrumented code"
            }
          >
            {isProcessing ? "⋯" : "▶"}{showActionLabels && <>&nbsp;Run</>}
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
      <div style={{ flex: 1, minHeight: 0, position: "relative", background: "var(--c-bg0)" }}>
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
          borderTop: "1px solid var(--c-border-subtle)",
          background: "var(--c-bg-panel)",
        }}
      >
        <div
          style={{
            padding: isMobile ? "5px 12px" : "7px 16px",
            borderBottom: "1px solid var(--c-border-subtle)",
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
              color: "var(--c-text-dim)",
              textTransform: "uppercase",
            }}
          >
            Standard Input
          </span>
          <span
            style={{
              fontSize: isMobile ? "9px" : "11px",
              color: "var(--c-text-dimmer)",
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
            background: "var(--c-bg0)",
            color: "var(--c-text)",
            padding: isMobile ? "6px 12px" : "10px 16px",
            fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
            fontSize: isMobile ? "11px" : "13px",
            lineHeight: isMobile ? "16px" : "20px",
            boxSizing: "border-box",
            caretColor: "var(--c-accent)",
            opacity: isProcessing ? 0.6 : 1,
            transition: "opacity 0.2s ease",
          }}
        />
      </div>
    </div>
  );
}

export default Editor;
