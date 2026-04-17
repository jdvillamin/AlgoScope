#include <stdio.h>
#include <string.h>

char line[100];

int main() {
    char c;

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%c", &c);

    if ('a' <= c && c <= 'z') {
        printf("a\n");
    } else if ('A' <= c && c <= 'Z') {
        printf("A\n");
    }

    return 0;
}
