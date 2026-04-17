#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    char str[27];
    bool flags[26];
    for (int i = 0; i < 26; i++)
        flags[i] = false;

    fgets(str, 27, stdin);
    for (int i = 0; str[i] != '\n'; i++) {
        if (flags[str[i] - 'a']) {
            puts("no");
            return 0;
        }
        flags[str[i] - 'a'] = true;
    }
    puts("yes");
    return 0;
}
