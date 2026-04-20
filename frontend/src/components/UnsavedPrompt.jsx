function UnsavedPrompt({ open, fileName, onSave, onDiscard, onCancel }) {
  if (!open) return null;

  const btnBase = {
    padding: "9px 16px",
    borderRadius: "8px",
    fontSize: "12.5px",
    fontWeight: 600,
    cursor: "pointer",
    fontFamily: "inherit",
    border: "1px solid #1e2d42",
    background: "#0f1928",
    color: "#8fa3c8",
    transition: "all 0.12s",
  };

  return (
    <div
      onClick={onCancel}
      style={{
        position: "fixed",
        inset: 0,
        background: "rgba(2, 4, 10, 0.72)",
        display: "flex",
        alignItems: "center",
        justifyContent: "center",
        zIndex: 1000,
        backdropFilter: "blur(2px)",
      }}
    >
      <div
        onClick={(e) => e.stopPropagation()}
        style={{
          width: "calc(100vw - 32px)",
          maxWidth: "440px",
          background: "#0e1520",
          border: "1px solid #1e2d42",
          borderRadius: "12px",
          padding: "22px 24px 18px",
          boxShadow: "0 20px 60px rgba(0, 0, 0, 0.6)",
          color: "#c8d8f0",
          fontFamily: "inherit",
        }}
      >
        <div
          style={{
            fontSize: "14px",
            fontWeight: 700,
            marginBottom: "8px",
            color: "#dce7f8",
          }}
        >
          Unsaved changes
        </div>
        <div
          style={{
            fontSize: "12.5px",
            lineHeight: 1.5,
            color: "#8fa3c8",
            marginBottom: "18px",
          }}
        >
          <span style={{ color: "#c8d8f0", fontWeight: 600 }}>
            {fileName || "This file"}
          </span>{" "}
          has unsaved changes. Save them before continuing, or discard to lose
          the changes.
        </div>
        <div
          style={{
            display: "flex",
            justifyContent: "flex-end",
            gap: "8px",
          }}
        >
          <button onClick={onCancel} style={btnBase} type="button">
            Cancel
          </button>
          <button
            onClick={onDiscard}
            style={{
              ...btnBase,
              borderColor: "#3d2e10",
              background: "#1a1810",
              color: "#f0a429",
            }}
            type="button"
          >
            Discard
          </button>
          <button
            onClick={onSave}
            style={{
              ...btnBase,
              borderColor: "#1e3a6e",
              background: "#0f1e3a",
              color: "#4b8cf7",
            }}
            type="button"
          >
            Save
          </button>
        </div>
      </div>
    </div>
  );
}

export default UnsavedPrompt;
