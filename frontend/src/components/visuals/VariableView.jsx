import React from "react";
import { useValueFlash } from "../../visuals/useFlash";
import { themeFor } from "../../visuals/visualTheme";

function VariableView({ obj, onMouseDown }) {
  const flashing = useValueFlash(obj.value);
  const theme = themeFor("var");
  return (
    <div
      data-viz-id={obj.id}
      onMouseDown={(e) => onMouseDown(e, obj.id)}
      style={{
        position: "absolute",
        left: obj.x,
        top: obj.y,
        cursor: "move",
        userSelect: "none",
      }}
    >
      <div
        style={{
          background: "#131d2e",
          border: `1px solid ${flashing ? theme.flash : theme.border}`,
          borderRadius: "10px",
          padding: "8px 14px",
          boxShadow: flashing
            ? `0 0 16px ${theme.flash}33, 0 4px 20px rgba(0,0,0,0.5)`
            : "0 4px 20px rgba(0,0,0,0.5)",
          minWidth: "64px",
          textAlign: "center",
          transition: "border-color 0.2s, box-shadow 0.2s",
        }}
      >
        <div
          style={{
            fontSize: "11px",
            fontWeight: 600,
            color: theme.label,
            marginBottom: "4px",
            letterSpacing: "0.8px",
          }}
        >
          {obj.id}
        </div>
        <div
          style={{
            fontSize: "16px",
            fontWeight: 700,
            color: flashing ? theme.flash : "#dce7f8",
            fontFamily: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
            transition: "color 0.2s",
          }}
        >
          {obj.value ?? "∅"}
        </div>
      </div>
    </div>
  );
}

export default VariableView;
