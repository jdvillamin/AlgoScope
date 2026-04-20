import re

ALLOWED_INCLUDES = {
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
}

BLOCKED_FUNCTIONS = [
    # Process execution
    "system",
    "popen",
    "pclose",
    "execl",
    "execle",
    "execlp",
    "execv",
    "execve",
    "execvp",
    "execvpe",
    # Process creation
    "fork",
    "vfork",
    "clone",
    # File I/O
    "fopen",
    "freopen",
    "fdopen",
    "tmpfile",
    "tmpnam",
    "remove",
    "unlink",
    "rename",
    "rmdir",
    "mkdir",
    "chdir",
    "chmod",
    "chown",
    "link",
    "symlink",
    "readlink",
    "opendir",
    "readdir",
    "closedir",
    "creat",
    # Network
    "socket",
    "connect",
    "bind",
    "listen",
    "accept",
    "sendto",
    "recvfrom",
    "sendmsg",
    "recvmsg",
    "getaddrinfo",
    "gethostbyname",
    "gethostbyaddr",
    # Signals
    "signal",
    "sigaction",
    "kill",
    "alarm",
    # Environment
    "getenv",
    "setenv",
    "putenv",
    "unsetenv",
    # Memory mapping / dynamic loading
    "mmap",
    "mprotect",
    "munmap",
    "dlopen",
    "dlsym",
    "dlclose",
    "shm_open",
    # Process control
    "ptrace",
    "setuid",
    "setgid",
    "seteuid",
    "setegid",
    "setreuid",
    "setregid",
    # I/O control
    "ioctl",
    "fcntl",
]

_BLOCKED_RE = re.compile(
    r"\b(" + "|".join(re.escape(fn) for fn in BLOCKED_FUNCTIONS) + r")\b"
)

_INCLUDE_RE = re.compile(
    r'^\s*#\s*include\s+[<"]([^>"]+)[>"]', re.MULTILINE
)

_PATH_INCLUDE_RE = re.compile(
    r'^\s*#\s*include\s+[<"](\.\.|/)', re.MULTILINE
)

_ASM_RE = re.compile(r"\b(__asm__|__asm|asm)\s*[\(\{(volatile)]")


def _strip_comments_and_strings(code):
    """Replace comment bodies and string literal contents with spaces,
    preserving line structure so line numbers stay correct."""
    result = []
    i = 0
    n = len(code)
    while i < n:
        # Single-line comment
        if code[i] == "/" and i + 1 < n and code[i + 1] == "/":
            result.append("  ")
            i += 2
            while i < n and code[i] != "\n":
                result.append(" ")
                i += 1
        # Multi-line comment
        elif code[i] == "/" and i + 1 < n and code[i + 1] == "*":
            result.append("  ")
            i += 2
            while i < n:
                if code[i] == "*" and i + 1 < n and code[i + 1] == "/":
                    result.append("  ")
                    i += 2
                    break
                result.append("\n" if code[i] == "\n" else " ")
                i += 1
        # String literal
        elif code[i] == '"':
            result.append('"')
            i += 1
            while i < n and code[i] != '"':
                if code[i] == "\\" and i + 1 < n:
                    result.append("  ")
                    i += 2
                else:
                    result.append("\n" if code[i] == "\n" else " ")
                    i += 1
            if i < n:
                result.append('"')
                i += 1
        # Char literal
        elif code[i] == "'":
            result.append("'")
            i += 1
            while i < n and code[i] != "'":
                if code[i] == "\\" and i + 1 < n:
                    result.append("  ")
                    i += 2
                else:
                    result.append(" ")
                    i += 1
            if i < n:
                result.append("'")
                i += 1
        else:
            result.append(code[i])
            i += 1
    return "".join(result)


def validate_code(code):
    """Validate C code for dangerous constructs.

    Returns a list of ``{"line": int, "message": str}`` dicts.
    An empty list means the code is safe.
    """
    violations = []
    stripped = _strip_comments_and_strings(code)
    lines = stripped.split("\n")

    for lineno, line in enumerate(lines, start=1):
        # Check includes against whitelist
        inc_match = _INCLUDE_RE.match(line)
        if inc_match:
            header = inc_match.group(1)
            if header not in ALLOWED_INCLUDES:
                violations.append({
                    "line": lineno,
                    "message": (
                        f'Blocked include: <{header}>. '
                        f"Only standard algorithm headers are allowed."
                    ),
                })

        # Check for path-based includes
        if _PATH_INCLUDE_RE.match(line):
            violations.append({
                "line": lineno,
                "message": "Path-based includes are not allowed.",
            })

        # Check for inline assembly
        if _ASM_RE.search(line):
            violations.append({
                "line": lineno,
                "message": "Inline assembly is not allowed.",
            })

        # Check for blocked function names
        for m in _BLOCKED_RE.finditer(line):
            fn_name = m.group(1)
            violations.append({
                "line": lineno,
                "message": f"Blocked function: {fn_name}(). This operation is not permitted.",
            })

    return violations
