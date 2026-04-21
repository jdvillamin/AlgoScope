const ALLOWED_INCLUDES = new Set([
  "stdio.h",
  "stdlib.h",
  "string.h",
  "strings.h",
  "math.h",
  "stdbool.h",
  "stdint.h",
  "limits.h",
  "ctype.h",
  "float.h",
  "stddef.h",
  "inttypes.h",
  "assert.h",
  "time.h",
  "stdarg.h",
  "tracer.h",
]);

const BLOCKED_FUNCTIONS = [
  "system", "popen", "pclose", "execl", "execle", "execlp",
  "execv", "execve", "execvp", "execvpe",
  "fork", "vfork", "clone",
  "fopen", "freopen", "fdopen", "tmpfile", "tmpnam", "remove", "unlink",
  "rename", "rmdir", "mkdir", "chdir", "chmod", "chown", "link", "symlink",
  "readlink", "opendir", "readdir", "closedir", "creat",
  "socket", "connect", "bind", "listen", "accept", "sendto", "recvfrom",
  "sendmsg", "recvmsg", "getaddrinfo", "gethostbyname", "gethostbyaddr",
  "signal", "sigaction", "kill", "alarm",
  "getenv", "setenv", "putenv", "unsetenv",
  "mmap", "mprotect", "munmap", "dlopen", "dlsym", "dlclose", "shm_open",
  "ptrace", "setuid", "setgid", "seteuid", "setegid", "setreuid", "setregid",
  "ioctl", "fcntl",
];

const BLOCKED_RE = new RegExp(
  "\\b(" + BLOCKED_FUNCTIONS.map((f) => f.replace(/[.*+?^${}()|[\]\\]/g, "\\$&")).join("|") + ")\\b",
  "g"
);

const INCLUDE_RE = /^\s*#\s*include\s+[<"]([^>"]+)[>"]/;
const PATH_INCLUDE_RE = /^\s*#\s*include\s+[<"](\.\.|\/)/ ;
const ASM_RE = /\b(__asm__|__asm|asm)\s*[({(volatile)]/;

function stripCommentsAndStrings(code) {
  const result = [];
  let i = 0;
  const n = code.length;

  while (i < n) {
    if (code[i] === "/" && i + 1 < n && code[i + 1] === "/") {
      result.push("  ");
      i += 2;
      while (i < n && code[i] !== "\n") {
        result.push(" ");
        i++;
      }
    } else if (code[i] === "/" && i + 1 < n && code[i + 1] === "*") {
      result.push("  ");
      i += 2;
      while (i < n) {
        if (code[i] === "*" && i + 1 < n && code[i + 1] === "/") {
          result.push("  ");
          i += 2;
          break;
        }
        result.push(code[i] === "\n" ? "\n" : " ");
        i++;
      }
    } else if (code[i] === '"') {
      result.push('"');
      i++;
      while (i < n && code[i] !== '"') {
        if (code[i] === "\\" && i + 1 < n) {
          result.push("  ");
          i += 2;
        } else {
          result.push(code[i] === "\n" ? "\n" : " ");
          i++;
        }
      }
      if (i < n) {
        result.push('"');
        i++;
      }
    } else if (code[i] === "'") {
      result.push("'");
      i++;
      while (i < n && code[i] !== "'") {
        if (code[i] === "\\" && i + 1 < n) {
          result.push("  ");
          i += 2;
        } else {
          result.push(" ");
          i++;
        }
      }
      if (i < n) {
        result.push("'");
        i++;
      }
    } else {
      result.push(code[i]);
      i++;
    }
  }

  return result.join("");
}

const EDUCATIONAL_MESSAGES = {
  system: "system() executes shell commands — this is a security risk in a sandboxed environment.",
  popen: "popen() opens a process pipe — not allowed in this sandbox.",
  fork: "fork() creates child processes — not permitted here.",
  vfork: "vfork() creates child processes — not permitted here.",
  fopen: "fopen() opens files on the filesystem — use arrays/variables instead.",
  socket: "socket() opens network connections — networking is not allowed.",
  connect: "connect() opens network connections — networking is not allowed.",
  execl: "exec*() replaces the current process — not permitted.",
  execv: "exec*() replaces the current process — not permitted.",
  mmap: "mmap() maps memory pages directly — not permitted in this sandbox.",
  dlopen: "dlopen() loads shared libraries dynamically — not permitted.",
  ptrace: "ptrace() attaches to processes — not permitted.",
  signal: "signal() modifies signal handling — not permitted in this sandbox.",
  kill: "kill() sends signals to processes — not permitted.",
  getenv: "getenv() reads environment variables — not permitted in this sandbox.",
};

function getEducationalMessage(fnName) {
  if (EDUCATIONAL_MESSAGES[fnName]) return EDUCATIONAL_MESSAGES[fnName];
  for (const [key, msg] of Object.entries(EDUCATIONAL_MESSAGES)) {
    if (fnName.startsWith(key)) return msg;
  }
  return `${fnName}() is not permitted in this sandbox.`;
}

export function validateCode(code) {
  const violations = [];
  const stripped = stripCommentsAndStrings(code);
  const lines = stripped.split("\n");
  const originalLines = code.split("\n");

  for (let lineno = 0; lineno < lines.length; lineno++) {
    const line = lines[lineno];
    const origLine = originalLines[lineno] || "";
    const lineNum = lineno + 1;

    // Use stripped line to confirm include is not commented out,
    // but extract header name from original (stripping blanks quoted content).
    if (INCLUDE_RE.test(line)) {
      const origMatch = origLine.match(INCLUDE_RE);
      if (origMatch) {
        const header = origMatch[1];
        if (!ALLOWED_INCLUDES.has(header)) {
          violations.push({
            line: lineNum,
            message: `Blocked include: <${header}>. Only standard algorithm headers are allowed.`,
          });
        }
      }
    }

    if (PATH_INCLUDE_RE.test(origLine)) {
      violations.push({
        line: lineNum,
        message: "Path-based includes are not allowed.",
      });
    }

    if (ASM_RE.test(line)) {
      violations.push({
        line: lineNum,
        message: "Inline assembly is not allowed.",
      });
    }

    BLOCKED_RE.lastIndex = 0;
    let m;
    while ((m = BLOCKED_RE.exec(line)) !== null) {
      const fnName = m[1];
      violations.push({
        line: lineNum,
        message: getEducationalMessage(fnName),
      });
    }
  }

  return violations;
}
