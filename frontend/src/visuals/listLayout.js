// Shared helpers for the linked-list views (LinkedListView, DoublyLinkedListView).

// Trace events only ever append links (singly lists have no unlink event), so
// a node accumulates an outgoing link per ->next assignment. The latest
// assignment is the live one — earlier ones are stale and must not render.
export function latestLinkTargets(links) {
  const out = {};
  for (const l of links) out[l.from] = l.to;
  return out;
}

// Order nodes by walking the next-chain so the rendered row matches the
// logical list order rather than node creation order. Chain heads (nodes with
// no incoming live link) are walked first in creation order; leftover nodes
// (members of cycles) follow, also in creation order.
export function chainOrder(nodeIds, nextByFrom) {
  const idSet = new Set(nodeIds);
  // Self-links don't make a node a chain member — it can still head a chain.
  const hasIncoming = new Set(
    Object.entries(nextByFrom)
      .filter(([from, to]) => idSet.has(to) && to !== from)
      .map(([, to]) => to),
  );
  const visited = new Set();
  const order = [];
  const walk = (start) => {
    let cur = start;
    while (cur != null && idSet.has(cur) && !visited.has(cur)) {
      visited.add(cur);
      order.push(cur);
      cur = nextByFrom[cur];
    }
  };
  for (const id of nodeIds) {
    if (!hasIncoming.has(id)) walk(id);
  }
  for (const id of nodeIds) walk(id);
  return order;
}
