import API from "./backend";

export function listHistory(page = 1) {
  return API.get("/api/history", { params: { page } }).then((r) => r.data);
}

export function getHistoryRun(id) {
  return API.get(`/api/history/${id}`).then((r) => r.data.run);
}
