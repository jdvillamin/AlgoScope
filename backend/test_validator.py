import unittest
from validator import validate_code


class TestValidateCode(unittest.TestCase):

    # --- Safe code should pass ---

    def test_safe_code_passes(self):
        code = '''
#include <stdio.h>
#include <stdlib.h>
int main() {
    int arr[5] = {3, 1, 4, 1, 5};
    printf("%d\\n", arr[0]);
    return 0;
}
'''
        self.assertEqual(validate_code(code), [])

    def test_all_allowed_includes(self):
        headers = [
            "stdio.h", "stdlib.h", "string.h", "strings.h", "math.h",
            "stdbool.h", "stdint.h", "limits.h", "ctype.h", "float.h",
            "stddef.h", "inttypes.h", "assert.h", "time.h", "stdarg.h",
            "tracer.h",
        ]
        code = "\n".join(f'#include <{h}>' for h in headers) + "\nint main() { return 0; }\n"
        self.assertEqual(validate_code(code), [])

    # --- Blocked includes ---

    def test_blocked_include_unistd(self):
        code = '#include <unistd.h>\nint main() { return 0; }\n'
        v = validate_code(code)
        self.assertEqual(len(v), 1)
        self.assertIn("unistd.h", v[0]["message"])
        self.assertEqual(v[0]["line"], 1)

    def test_blocked_include_sys_socket(self):
        code = '#include <sys/socket.h>\nint main() { return 0; }\n'
        v = validate_code(code)
        self.assertTrue(len(v) >= 1)
        self.assertIn("sys/socket.h", v[0]["message"])

    # --- Blocked functions ---

    def test_blocked_system(self):
        code = 'int main() { system("ls"); return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("system" in vi["message"] for vi in v))

    def test_blocked_fork(self):
        code = 'int main() { fork(); return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("fork" in vi["message"] for vi in v))

    def test_blocked_fopen(self):
        code = 'int main() { fopen("/etc/passwd", "r"); return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("fopen" in vi["message"] for vi in v))

    def test_blocked_socket(self):
        code = 'int main() { socket(AF_INET, SOCK_STREAM, 0); return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("socket" in vi["message"] for vi in v))

    def test_blocked_exec(self):
        code = 'int main() { execv("/bin/sh", NULL); return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("execv" in vi["message"] for vi in v))

    def test_blocked_popen(self):
        code = 'int main() { popen("ls", "r"); return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("popen" in vi["message"] for vi in v))

    def test_blocked_getenv(self):
        code = 'int main() { getenv("HOME"); return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("getenv" in vi["message"] for vi in v))

    def test_blocked_mmap(self):
        code = 'int main() { mmap(NULL, 4096, 0, 0, -1, 0); return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("mmap" in vi["message"] for vi in v))

    def test_blocked_dlopen(self):
        code = 'int main() { dlopen("lib.so", 0); return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("dlopen" in vi["message"] for vi in v))

    def test_blocked_ptrace(self):
        code = 'int main() { ptrace(0, 0, 0, 0); return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("ptrace" in vi["message"] for vi in v))

    # --- Inline assembly ---

    def test_blocked_asm(self):
        code = 'int main() { asm("nop"); return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("assembly" in vi["message"].lower() for vi in v))

    def test_blocked_asm_volatile(self):
        code = 'int main() { __asm__ volatile("nop"); return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("assembly" in vi["message"].lower() for vi in v))

    # --- Path-based includes ---

    def test_blocked_path_include_absolute(self):
        code = '#include "/etc/passwd"\nint main() { return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("path" in vi["message"].lower() for vi in v))

    def test_blocked_path_include_relative(self):
        code = '#include "../secret.h"\nint main() { return 0; }\n'
        v = validate_code(code)
        self.assertTrue(any("path" in vi["message"].lower() for vi in v))

    # --- Comments and strings should not trigger false positives ---

    def test_function_in_comment_not_flagged(self):
        code = '// system("rm -rf /");\nint main() { return 0; }\n'
        self.assertEqual(validate_code(code), [])

    def test_function_in_block_comment_not_flagged(self):
        code = '/* fopen("/etc/passwd", "r"); */\nint main() { return 0; }\n'
        self.assertEqual(validate_code(code), [])

    def test_function_in_string_not_flagged(self):
        code = 'int main() { char *s = "system is cool"; return 0; }\n'
        self.assertEqual(validate_code(code), [])

    # --- Multiple violations ---

    def test_multiple_violations(self):
        code = '''#include <unistd.h>
int main() {
    system("ls");
    fork();
    return 0;
}
'''
        v = validate_code(code)
        self.assertTrue(len(v) >= 3)

    # --- Line numbers are correct ---

    def test_line_numbers(self):
        code = 'int main() {\n  int x = 1;\n  system("ls");\n  return 0;\n}\n'
        v = validate_code(code)
        self.assertEqual(len(v), 1)
        self.assertEqual(v[0]["line"], 3)


if __name__ == "__main__":
    unittest.main()
