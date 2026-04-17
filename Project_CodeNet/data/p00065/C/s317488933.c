#include <stdio.h>

int x[1001];
int y[1001];
int main() {
    int c, d;
    char s[10];
    for(;fgets(s, 10, stdin), s[0] != '\n';) {
        sscanf(s, "%d,%d", &c, &d);
        x[c]++;
    }
    while(~scanf("%d,%d", &c, &d))
        if (x[c] != 0) y[c] = ++x[c];
    for (int i=1; i<1001; i++)
        if (y[i] != 0) printf("%d %d\n", i, y[i]);
}

