import API from "./backend";

export function listCodes() {
  return API.get("/api/codes").then((r) => r.data.codes);
}

export function createCode(title, code, stdin = "") {
  return API.post("/api/codes", { title, code, stdin }).then((r) => r.data.code);
}

export function updateCode(id, updates) {
  return API.put(`/api/codes/${id}`, updates).then((r) => r.data.code);
}

export function deleteCode(id) {
  return API.delete(`/api/codes/${id}`);
}
