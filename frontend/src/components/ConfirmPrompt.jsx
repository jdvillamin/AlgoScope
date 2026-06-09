function ConfirmPrompt({ open, title, message, confirmLabel = "Confirm", onConfirm, onCancel }) {
  if (!open) return null;

  const btnBase = {
    padding: "9px 16px",
    borderRadius: "8px",
    fontSize: "12.5px",
    fontWeight: 600,
    cursor: "pointer",
    fontFamily: "inherit",
    border: "1px solid var(--c-border)",
    background: "var(--c-bg-btn)",
    color: "var(--c-text-muted)",
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
          background: "var(--c-bg-panel)",
          border: "1px solid var(--c-border)",
          borderRadius: "12px",
          padding: "22px 24px 18px",
          boxShadow: "0 20px 60px rgba(0, 0, 0, 0.6)",
          color: "var(--c-text-bright)",
          fontFamily: "inherit",
        }}
      >
        <div
          style={{
            fontSize: "14px",
            fontWeight: 700,
            marginBottom: "8px",
            color: "var(--c-text)",
          }}
        >
          {title}
        </div>
        <div
          style={{
            fontSize: "12.5px",
            lineHeight: 1.5,
            color: "var(--c-text-muted)",
            marginBottom: "18px",
          }}
        >
          {message}
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
            onClick={onConfirm}
            style={{
              ...btnBase,
              borderColor: "var(--c-border-accent)",
              background: "var(--c-bg-accent)",
              color: "var(--c-accent)",
            }}
            type="button"
          >
            {confirmLabel}
          </button>
        </div>
      </div>
    </div>
  );
}

export default ConfirmPrompt;
