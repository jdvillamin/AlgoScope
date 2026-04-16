import { useEffect, useRef, useState } from "react";

const FLASH_MS = 420;

export function useValueFlash(value, ms = FLASH_MS) {
  const [flashing, setFlashing] = useState(false);
  const prevRef = useRef(value);
  useEffect(() => {
    if (prevRef.current === value) return;
    prevRef.current = value;
    setFlashing(true); // eslint-disable-line react-hooks/set-state-in-effect
    const t = setTimeout(() => setFlashing(false), ms);
    return () => clearTimeout(t);
  }, [value, ms]);
  return flashing;
}

export function useChangedKeys(entries, ms = FLASH_MS) {
  const [changed, setChanged] = useState(() => new Set());
  const prevRef = useRef(null);
  useEffect(() => {
    const prev = prevRef.current || {};
    const next = entries || {};
    prevRef.current = next;
    const diff = new Set();
    for (const k of Object.keys(next)) {
      if (prev[k] !== next[k]) diff.add(k);
    }
    if (diff.size === 0) {
      setChanged((s) => (s.size > 0 ? new Set() : s)); // eslint-disable-line react-hooks/set-state-in-effect
      return;
    }
    setChanged(diff);
    const t = setTimeout(() => setChanged(new Set()), ms);
    return () => clearTimeout(t);
  }, [entries, ms]);
  return changed;
}
