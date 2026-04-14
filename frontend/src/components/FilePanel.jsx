import { useState, useRef } from "react";
import SAMPLE_CATEGORIES from "../samples";
import UserMenu from "./UserMenu";

function FilePanel({ files, activeFileId, onNewFile, onSwitchFile, onDeleteFile, onLoadSample, onRenameFile, onImportFile, onExportFile }) {
  const [expandedCategories, setExpandedCategories] = useState({});
  const [editingId, setEditingId] = useState(null);
  const [editingName, setEditingName] = useState("");
  const [collapsed, setCollapsed] = useState(false);
  const fileInputRef = useRef(null);

  const smallBtn = {
    flex: 1,
    padding: "6px 8px",
    borderRadius: "6px",
    border: "1px solid #1e2d42",
    background: "#0f1928",
    color: "#8fa3c8",
    fontSize: "11.5px",
    fontWeight: 600,
    cursor: "pointer",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    gap: "5px",
    fontFamily: "inherit",
  };

  const toggleCategory = (name) => {
    setExpandedCategories((prev) => ({ ...prev, [name]: !prev[name] }));
  };

  return (
    <div
      style={{
        width: collapsed ? "44px" : "220px",
        minWidth: collapsed ? "44px" : "220px",
        height: "100%",
        background: "#0a1018",
        borderRight: "1px solid #1a2535",
        display: "flex",
        flexDirection: "column",
        overflow: "hidden",
        transition: "width 0.2s ease, min-width 0.2s ease",
      }}
    >
      {/* Header row — 44px to align with Canvas toolbar & Editor tabs */}
      <div
        style={{
          height: "44px",
          padding: collapsed ? "0 6px" : "0 12px",
          borderBottom: "1px solid #1a2535",
          display: "flex",
          alignItems: "center",
          justifyContent: collapsed ? "center" : "flex-start",
          boxSizing: "border-box",
          flexShrink: 0,
        }}
      >
        <button
          onClick={() => setCollapsed((v) => !v)}
          style={{
            width: "32px",
            height: "32px",
            borderRadius: "8px",
            border: "1px solid #1e2d42",
            background: "#0f1928",
            color: "#8fa3c8",
            fontSize: "14px",
            cursor: "pointer",
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
            padding: 0,
            fontFamily: "inherit",
          }}
          title={collapsed ? "Expand panel" : "Collapse panel"}
        >
          {collapsed ? "☰" : "◀"}
        </button>
      </div>

      {/* New File + Import / Export */}
      <div style={{ padding: "10px 12px 4px" }}>
        {!collapsed && (
          <>
            <button
              onClick={onNewFile}
              style={{
                width: "100%",
                padding: "8px 12px",
                borderRadius: "8px",
                border: "1px solid #1e2d42",
                background: "#0f1928",
                color: "#8fa3c8",
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
          </>
        )}
      </div>

      {/* File list */}
      {!collapsed && <div
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
              color: "#3d5270",
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
                  background: isActive ? "#131d2e" : "transparent",
                  borderLeft: isActive ? "2px solid #4b8cf7" : "2px solid transparent",
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
                      color: "#c8d8f0",
                      fontWeight: 600,
                      background: "#0f1928",
                      border: "1px solid #1e3a6e",
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
                      color: isActive ? "#c8d8f0" : "#647e9c",
                      fontWeight: isActive ? 600 : 400,
                      overflow: "hidden",
                      textOverflow: "ellipsis",
                      whiteSpace: "nowrap",
                    }}
                  >
                    {file.name}
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
                      color: "#3d5270",
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

        {/* Divider */}
        <div
          style={{
            height: "1px",
            background: "#1a2535",
            margin: "4px 14px",
          }}
        />

        {/* Samples */}
        <div style={{ padding: "8px 0" }}>
          <div
            style={{
              padding: "0 14px 6px",
              fontSize: "10px",
              fontWeight: 700,
              letterSpacing: "1px",
              color: "#3d5270",
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
                    color: "#506888",
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
                        color: "#647e9c",
                        transition: "background 0.1s",
                      }}
                      onMouseEnter={(e) => {
                        e.currentTarget.style.background = "#0f1928";
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

      <UserMenu collapsed={collapsed} />
    </div>
  );
}

export default FilePanel;
