export const VISUAL_THEME = {
  var:     { border: "#24456b", label: "#6b8db0", flash: "#7ab8ff" },
  array:   { border: "#3b3057", label: "#7a6ea0", flash: "#9d8bff" },
  array2d: { border: "#432e5a", label: "#8464a3", flash: "#b983ff" },
  stack:   { border: "#5a4218", label: "#b38847", flash: "#e0a84a" },
  queue:   { border: "#5c3a1c", label: "#b87a45", flash: "#f5944a" },
  hashmap: { border: "#1a4b55", label: "#5ba7b3", flash: "#4fc9d9" },
  list:    { border: "#1f4e2c", label: "#5ca976", flash: "#63d188" },
  dlist:   { border: "#1e4a40", label: "#50a294", flash: "#50c7b0" },
  tree:    { border: "#52203b", label: "#b36b93", flash: "#e586b8" },
  graph:   { border: "#5a2429", label: "#c16672", flash: "#eb7785" },
};

export function themeFor(type) {
  return VISUAL_THEME[type] || VISUAL_THEME.var;
}
