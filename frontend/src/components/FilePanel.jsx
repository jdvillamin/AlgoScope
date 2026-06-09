import { useState, useRef } from "react";
import SAMPLE_CATEGORIES from "../samples";
import UserMenu from "./UserMenu";
import RunHistory from "./RunHistory";
import { TUTORIAL_EVENT } from "./Tutorial";

const requestTutorial = () =>
  window.dispatchEvent(new CustomEvent(TUTORIAL_EVENT));

function FilePanel({ files, activeFileId, unsavedIds, activeFileUnsaved, onNewFile, onSwitchFile, onDeleteFile, onLoadSample, onRenameFile, onImportFile, onExportFile, onSaveFile, onLoadHistoryRun, onLogout, isSaving, isMobile, theme = "dark", onToggleTheme }) {
  const themeToggleTitle = `Switch to ${theme === "dark" ? "light" : "dark"} mode`;
  const themeToggleIcon = theme === "dark" ? "☀" : "🌙";
  const [expandedCategories, setExpandedCategories] = useState({});
  const [editingId, setEditingId] = useState(null);
  const [editingName, setEditingName] = useState("");
  const [collapsed, setCollapsed] = useState(false);
  const fileInputRef = useRef(null);
  const effectiveCollapsed = isMobile ? false : collapsed;

  const smallBtn = {
    flex: 1,
    padding: "6px 8px",
    borderRadius: "6px",
    border: "1px solid var(--c-border)",
    background: "var(--c-bg-btn)",
    color: "var(--c-text-muted)",
    fontSize: "11.5px",
    fontWeight: 600,
    cursor: "pointer",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    gap: "5px",
    fontFamily: "inherit",
  };

  const collapsedBtn = {
    width: "32px",
    height: "32px",
    borderRadius: "8px",
    border: "1px solid var(--c-border)",
    background: "var(--c-bg-btn)",
    color: "var(--c-text-muted)",
    fontSize: "14px",
    cursor: "pointer",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    padding: 0,
    fontFamily: "inherit",
  };

  const toggleCategory = (name) => {
    setExpandedCategories((prev) => ({ ...prev, [name]: !prev[name] }));
  };

  return (
    <div
      data-tutorial="file-panel"
      style={{
        width: isMobile ? "100%" : (effectiveCollapsed ? "44px" : "220px"),
        minWidth: isMobile ? "100%" : (effectiveCollapsed ? "44px" : "220px"),
        height: "100%",
        background: "var(--c-bg-side)",
        borderRight: isMobile ? "none" : "1px solid var(--c-border-subtle)",
        display: "flex",
        flexDirection: "column",
        transition: isMobile ? "none" : "width 0.2s ease, min-width 0.2s ease",
      }}
    >
      {/* Header row */}
      <div
        style={{
          height: "44px",
          padding: isMobile ? "0 16px" : (effectiveCollapsed ? "0 6px" : "0 12px"),
          borderBottom: "1px solid var(--c-border-subtle)",
          display: "flex",
          alignItems: "center",
          justifyContent: effectiveCollapsed && !isMobile ? "center" : "space-between",
          gap: "8px",
          boxSizing: "border-box",
          flexShrink: 0,
        }}
      >
        {isMobile ? (
          <span style={{ fontSize: "11px", fontWeight: 700, letterSpacing: "1px", color: "var(--c-text-head)", textTransform: "uppercase" }}>
            Files
          </span>
        ) : (
          <button
            onClick={() => setCollapsed((v) => !v)}
            style={{
              width: "32px",
              height: "32px",
              borderRadius: "8px",
              border: "1px solid var(--c-border)",
              background: "var(--c-bg-btn)",
              color: "var(--c-text-muted)",
              fontSize: "14px",
              cursor: "pointer",
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              padding: 0,
              fontFamily: "inherit",
            }}
            title={effectiveCollapsed ? "Expand panel" : "Collapse panel"}
          >
            {effectiveCollapsed ? "☰" : "◀"}
          </button>
        )}
        {(!effectiveCollapsed || isMobile) && (
          <div style={{ display: "flex", gap: "6px" }}>
            <button
              onClick={onToggleTheme}
              style={{ ...collapsedBtn, fontSize: "14px" }}
              title={themeToggleTitle}
            >
              {themeToggleIcon}
            </button>
            <button
              onClick={requestTutorial}
              style={{ ...collapsedBtn, fontSize: "15px", fontWeight: 700 }}
              title="Help & tutorial"
            >
              ?
            </button>
          </div>
        )}
      </div>

      <input
        ref={fileInputRef}
        type="file"
        accept=".c,text/x-c,text/plain"
        multiple
        style={{ display: "none" }}
        onChange={(e) => {
          const picked = Array.from(e.target.files || []);
          picked.forEach((f) => onImportFile?.(f));
          e.target.value = "";
        }}
      />

      {/* New File + Import / Export */}
      {effectiveCollapsed ? (
        <div style={{ padding: "8px 6px", display: "flex", flexDirection: "column", alignItems: "center", gap: "6px" }}>
          <button onClick={onNewFile} style={collapsedBtn} title="New File">
            <span style={{ fontSize: "16px", lineHeight: 1 }}>+</span>
          </button>
          <button onClick={() => fileInputRef.current?.click()} style={collapsedBtn} title="Import file">
            <span style={{ fontSize: "13px", lineHeight: 1 }}>↑</span>
          </button>
          <button onClick={onExportFile} style={collapsedBtn} title="Export file">
            <span style={{ fontSize: "13px", lineHeight: 1 }}>↓</span>
          </button>
          <button
            onClick={() => activeFileUnsaved && !isSaving && onSaveFile?.()}
            disabled={!activeFileUnsaved || isSaving}
            style={{
              ...collapsedBtn,
              border: `1px solid ${activeFileUnsaved ? "var(--c-border-accent)" : "var(--c-border-subtle)"}`,
              background: activeFileUnsaved ? "var(--c-bg-accent)" : "var(--c-bg-btn-off)",
              color: activeFileUnsaved ? "var(--c-accent)" : "var(--c-text-off)",
              cursor: activeFileUnsaved && !isSaving ? "pointer" : "default",
              fontSize: "13px",
            }}
            title={isSaving ? "Saving..." : activeFileUnsaved ? "Save file" : "No unsaved changes"}
          >
            {isSaving ? "⋯" : "✓"}
          </button>

          <div style={{ width: "100%", height: "1px", background: "var(--c-border-subtle)", margin: "2px 0" }} />

          <button onClick={() => setCollapsed(false)} style={collapsedBtn} title="Show files">
            <span style={{ fontSize: "12px", lineHeight: 1 }}>📄</span>
          </button>
          <button onClick={() => setCollapsed(false)} style={collapsedBtn} title="Sample files">
            <span style={{ fontSize: "12px", lineHeight: 1 }}>📂</span>
          </button>

          <div style={{ width: "100%", height: "1px", background: "var(--c-border-subtle)", margin: "2px 0" }} />

          <button onClick={onToggleTheme} style={{ ...collapsedBtn, fontSize: "14px" }} title={themeToggleTitle}>
            {themeToggleIcon}
          </button>
          <button onClick={requestTutorial} style={{ ...collapsedBtn, fontSize: "15px", fontWeight: 700 }} title="Help & tutorial">
            ?
          </button>
        </div>
      ) : (
        <div style={{ padding: "10px 12px 4px" }}>
          <button
            onClick={onNewFile}
            style={{
              width: "100%",
              padding: "8px 12px",
              borderRadius: "8px",
              border: "1px solid var(--c-border)",
              background: "var(--c-bg-btn)",
              color: "var(--c-text-muted)",
              fontSize: "12.5px",
              fontWeight: 600,
              cursor: "pointer",
              display: "flex",
              alignItems: "center",
              gap: "8px",
              fontFamily: "inherit",
            }}
          >
            <span style={{ fontSize: "16px", lineHeight: 1 }}>+</span>
            New File
          </button>
          <div style={{ display: "flex", gap: "6px", marginTop: "6px" }}>
            <button
              onClick={() => fileInputRef.current?.click()}
              style={smallBtn}
              title="Import a .c file from disk"
            >
              <span style={{ fontSize: "13px", lineHeight: 1 }}>↑</span>
              Import
            </button>
            <button
              onClick={onExportFile}
              style={smallBtn}
              title="Download the active file as .c"
            >
              <span style={{ fontSize: "13px", lineHeight: 1 }}>↓</span>
              Export
            </button>
          </div>
          <button
            onClick={() => activeFileUnsaved && onSaveFile?.()}
            disabled={!activeFileUnsaved}
            style={{
              width: "100%",
              marginTop: "6px",
              padding: "7px 10px",
              borderRadius: "6px",
              border: `1px solid ${activeFileUnsaved ? "var(--c-border-accent)" : "var(--c-border-subtle)"}`,
              background: activeFileUnsaved ? "var(--c-bg-accent)" : "var(--c-bg-btn-off)",
              color: activeFileUnsaved ? "var(--c-accent)" : "var(--c-text-off)",
              fontSize: "12px",
              fontWeight: 600,
              cursor: activeFileUnsaved ? "pointer" : "default",
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              gap: "6px",
              fontFamily: "inherit",
            }}
            title={
              isSaving
                ? "Saving..."
                : activeFileUnsaved
                  ? "Save file"
                  : "No unsaved changes"
            }
          >
            {isSaving ? "Saving..." : activeFileUnsaved ? "Save file" : "Saved"}
          </button>
        </div>
      )}

      {/* File list */}
      {!effectiveCollapsed && <div
        style={{
          flex: 1,
          overflowY: "auto",
          display: "flex",
          flexDirection: "column",
        }}
      >
        {/* My Files */}
        <div style={{ padding: "8px 0" }}>
          <div
            style={{
              padding: "0 14px 6px",
              fontSize: "10px",
              fontWeight: 700,
              letterSpacing: "1px",
              color: "var(--c-text-faint)",
              textTransform: "uppercase",
            }}
          >
            Files
          </div>
          {files.map((file) => {
            const isActive = file.id === activeFileId;
            return (
              <div
                key={file.id}
                onClick={() => onSwitchFile(file.id)}
                style={{
                  padding: "7px 14px",
                  margin: "1px 6px",
                  borderRadius: "6px",
                  cursor: "pointer",
                  display: "flex",
                  alignItems: "center",
                  justifyContent: "space-between",
                  gap: "6px",
                  background: isActive ? "var(--c-bg-raised)" : "transparent",
                  borderLeft: isActive ? "2px solid var(--c-accent)" : "2px solid transparent",
                  transition: "background 0.1s",
                }}
              >
                  {editingId === file.id ? (
                  <input
                    autoFocus
                    value={editingName}
                    onChange={(e) => setEditingName(e.target.value)}
                    onBlur={() => {
                      if (editingName.trim()) onRenameFile(file.id, editingName.trim());
                      setEditingId(null);
                    }}
                    onKeyDown={(e) => {
                      if (e.key === "Enter") {
                        if (editingName.trim()) onRenameFile(file.id, editingName.trim());
                        setEditingId(null);
                      } else if (e.key === "Escape") {
                        setEditingId(null);
                      }
                    }}
                    onClick={(e) => e.stopPropagation()}
                    style={{
                      fontSize: "12.5px",
                      color: "var(--c-text-bright)",
                      fontWeight: 600,
                      background: "var(--c-bg-btn)",
                      border: "1px solid var(--c-border-accent)",
                      borderRadius: "4px",
                      outline: "none",
                      padding: "1px 4px",
                      width: "100%",
                      fontFamily: "inherit",
                    }}
                  />
                ) : (
                  <span
                    onDoubleClick={(e) => {
                      e.stopPropagation();
                      setEditingId(file.id);
                      setEditingName(file.name);
                    }}
                    style={{
                      fontSize: "12.5px",
                      color: isActive ? "var(--c-text-bright)" : "var(--c-text-dim)",
                      fontWeight: isActive ? 600 : 400,
                      overflow: "hidden",
                      textOverflow: "ellipsis",
                      whiteSpace: "nowrap",
                      display: "flex",
                      alignItems: "center",
                      gap: "6px",
                      minWidth: 0,
                    }}
                  >
                    {unsavedIds?.has(file.id) && (
                      <span
                        style={{
                          width: "6px",
                          height: "6px",
                          borderRadius: "50%",
                          background: "var(--c-gold)",
                          flexShrink: 0,
                        }}
                        title="Unsaved changes"
                      />
                    )}
                    <span
                      style={{
                        overflow: "hidden",
                        textOverflow: "ellipsis",
                        whiteSpace: "nowrap",
                      }}
                    >
                      {file.name}
                    </span>
                  </span>
                )}
                {files.length > 1 && (
                  <span
                    onClick={(e) => {
                      e.stopPropagation();
                      onDeleteFile(file.id);
                    }}
                    style={{
                      fontSize: "14px",
                      color: "var(--c-text-faint)",
                      cursor: "pointer",
                      lineHeight: 1,
                      padding: "0 2px",
                      flexShrink: 0,
                      opacity: isActive ? 0.8 : 0,
                      transition: "opacity 0.15s",
                    }}
                    title="Delete file"
                  >
                    ×
                  </span>
                )}
              </div>
            );
          })}
        </div>

        {/* Run History */}
        <RunHistory onLoadRun={onLoadHistoryRun} />

        {/* Divider */}
        <div style={{ height: "1px", background: "var(--c-border-subtle)", margin: "4px 14px" }} />

        {/* Samples */}
        <div data-tutorial="samples" style={{ padding: "8px 0" }}>
          <div
            style={{
              padding: "0 14px 6px",
              fontSize: "10px",
              fontWeight: 700,
              letterSpacing: "1px",
              color: "var(--c-text-faint)",
              textTransform: "uppercase",
            }}
          >
            Samples
          </div>
          {SAMPLE_CATEGORIES.map((cat) => {
            const isExpanded = expandedCategories[cat.name];
            return (
              <div key={cat.name}>
                <div
                  onClick={() => toggleCategory(cat.name)}
                  style={{
                    padding: "5px 14px",
                    margin: "1px 6px",
                    borderRadius: "6px",
                    cursor: "pointer",
                    display: "flex",
                    alignItems: "center",
                    gap: "6px",
                    fontSize: "12px",
                    fontWeight: 600,
                    color: "var(--c-text-dimmer)",
                  }}
                >
                  <span
                    style={{
                      fontSize: "9px",
                      transition: "transform 0.15s",
                      transform: isExpanded ? "rotate(90deg)" : "rotate(0deg)",
                      display: "inline-block",
                    }}
                  >
                    ▶
                  </span>
                  {cat.name}
                </div>
                {isExpanded &&
                  cat.samples.map((sample) => (
                    <div
                      key={sample.name}
                      onClick={() => onLoadSample(sample)}
                      style={{
                        padding: "5px 14px 5px 32px",
                        margin: "1px 6px",
                        borderRadius: "6px",
                        cursor: "pointer",
                        fontSize: "12px",
                        color: "var(--c-text-dim)",
                        transition: "background 0.1s",
                      }}
                      onMouseEnter={(e) => {
                        e.currentTarget.style.background = "var(--c-bg-btn)";
                      }}
                      onMouseLeave={(e) => {
                        e.currentTarget.style.background = "transparent";
                      }}
                    >
                      {sample.name}
                    </div>
                  ))}
              </div>
            );
          })}
        </div>
      </div>}

      <UserMenu collapsed={effectiveCollapsed} onLogout={onLogout} />
    </div>
  );
}

export default FilePanel;
