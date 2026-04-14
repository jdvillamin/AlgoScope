// frontend/src/engine/layout.js
//
// Two layout strategies for placing visual objects on the canvas.
//
//   greedyLayout  — fast shelf packing in insertion order. Used in real time
//                   as objects appear or grow. Stable (objects don't jump
//                   around if a later object grows).
//
//   optimalLayout — bitmask DP that minimizes total layout height for a given
//                   canvas width. Triggered by the "Optimal fit" button.
//                   O(3^N) time; falls back to greedy for N > MAX_DP_ITEMS.
//
// Items are { id, w, h }. Pinned positions (from user drag) override the
// computed position.

const PADDING = 24;
const FALLBACK_W = 240;
const FALLBACK_H = 160;
const MAX_DP_ITEMS = 14;

function dims(item) {
  return {
    w: item.w && item.w > 0 ? item.w : FALLBACK_W,
    h: item.h && item.h > 0 ? item.h : FALLBACK_H,
  };
}

/**
 * Greedy shelf-packing layout.
 *
 * Walks items in insertion order, placing each on the current shelf until the
 * shelf width exceeds canvasWidth, then wraps to a new shelf. Pinned items
 * keep their pinned position and are skipped by the packer (their boxes are
 * not avoided, since the user explicitly placed them there).
 *
 * @param {Array<{id:string, w:number, h:number}>} items
 * @param {Object<string,{x:number,y:number}>} pinned
 * @param {number} canvasWidth
 * @returns {Object<string,{x:number,y:number}>}
 */
export function greedyLayout(items, pinned = {}, canvasWidth = 1200) {
  const positions = {};
  let shelfX = PADDING;
  let shelfY = PADDING;
  let shelfH = 0;

  for (const item of items) {
    if (pinned[item.id]) {
      positions[item.id] = pinned[item.id];
      continue;
    }

    const { w, h } = dims(item);

    // Wrap to a new shelf if this item won't fit on the current one.
    if (shelfX > PADDING && shelfX + w + PADDING > canvasWidth) {
      shelfY += shelfH + PADDING;
      shelfX = PADDING;
      shelfH = 0;
    }

    positions[item.id] = { x: shelfX, y: shelfY };
    shelfX += w + PADDING;
    if (h > shelfH) shelfH = h;
  }

  return positions;
}

/**
 * Optimal shelf packing via bitmask DP.
 *
 * Partition the N items into shelves. Each shelf has width = sum of item
 * widths + padding gaps and must fit within canvasWidth. The shelf's height
 * is the max item height in it. dp[S] = minimum total height to pack subset
 * S into shelves. Transition: dp[S] = min over feasible shelf T ⊆ S of
 * dp[S\T] + height(T) + padding.
 *
 * Complexity: O(3^N) — sum over S of 2^|S|. For N ≤ 14 this is ≤ ~5M ops.
 * Items within a shelf are placed in insertion order (low bit first).
 *
 * @param {Array<{id:string, w:number, h:number}>} items
 * @param {number} canvasWidth
 * @returns {Object<string,{x:number,y:number}>}
 */
export function optimalLayout(items, canvasWidth = 1200) {
  const N = items.length;
  if (N === 0) return {};
  if (N > MAX_DP_ITEMS) return greedyLayout(items, {}, canvasWidth);

  const w = items.map((it) => dims(it).w);
  const h = items.map((it) => dims(it).h);

  const FULL = (1 << N) - 1;

  // For every non-empty subset, precompute total width (with internal padding)
  // and max height.
  const shelfWidth = new Array(1 << N).fill(0);
  const shelfHeight = new Array(1 << N).fill(0);
  for (let s = 1; s <= FULL; s++) {
    let sumW = 0;
    let maxH = 0;
    let cnt = 0;
    for (let i = 0; i < N; i++) {
      if (s & (1 << i)) {
        sumW += w[i];
        if (h[i] > maxH) maxH = h[i];
        cnt++;
      }
    }
    shelfWidth[s] = sumW + Math.max(0, cnt - 1) * PADDING;
    shelfHeight[s] = maxH;
  }

  const dp = new Array(1 << N).fill(Infinity);
  const parent = new Array(1 << N).fill(0);
  dp[0] = 0;

  for (let s = 1; s <= FULL; s++) {
    // Enumerate non-empty subsets of s as the "last shelf".
    let sub = s;
    while (sub > 0) {
      // Need PADDING on both sides of the shelf (left + right margin).
      if (shelfWidth[sub] + 2 * PADDING <= canvasWidth) {
        const prev = s ^ sub;
        const candidate =
          dp[prev] + shelfHeight[sub] + (prev > 0 ? PADDING : 0);
        if (candidate < dp[s]) {
          dp[s] = candidate;
          parent[s] = sub;
        }
      }
      sub = (sub - 1) & s;
    }

    // Fallback: an item is wider than the canvas. Place the lowest-bit item
    // alone on its own shelf so we never get Infinity.
    if (dp[s] === Infinity) {
      const lowest = s & -s;
      const prev = s ^ lowest;
      dp[s] = dp[prev] + shelfHeight[lowest] + (prev > 0 ? PADDING : 0);
      parent[s] = lowest;
    }
  }

  // Reconstruct the shelf groupings by walking parent[].
  const shelves = [];
  let cur = FULL;
  while (cur > 0) {
    shelves.push(parent[cur]);
    cur ^= parent[cur];
  }
  // The walk gives shelves in reverse-placement order; reverse so insertion
  // order is roughly preserved top-to-bottom.
  shelves.reverse();

  const positions = {};
  let y = PADDING;
  for (const shelf of shelves) {
    let maxH = 0;
    for (let i = 0; i < N; i++) {
      if (shelf & (1 << i) && h[i] > maxH) maxH = h[i];
    }
    let x = PADDING;
    for (let i = 0; i < N; i++) {
      if (shelf & (1 << i)) {
        positions[items[i].id] = { x, y };
        x += w[i] + PADDING;
      }
    }
    y += maxH + PADDING;
  }

  return positions;
}
