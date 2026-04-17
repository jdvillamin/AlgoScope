#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int max(int x, int y) {
    if (x >= y) return x;
    else return y;
}

int min(int x, int y) {
    if (x <= y) return x;
    else return y;
}

int main()
{
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    int ans;
    ans = min(b, d) - max(a, c);
    if (ans >= 0) printf("%d\n", ans);
    else printf("0\n");
    return 0;
}
