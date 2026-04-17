#include <stdio.h>

int main(void)
{
    int n, x[500000], y[500000], i, j, xd, yd;
    long m = 100000000L, d;

    scanf("%d\n", &n);
    for (i = 0; i < n; i++) {
        scanf("%d %d\n", &x[i], &y[i]);
    }

    for (i = 0; i < n - 2; i++) {
        for (j = 1; j < n - 1; j++) {
            xd = x[i] - x[j];
            yd = y[i] - y[j];
            d = xd * xd + yd * yd;
            if (xd < m) m = d;
        }
    }
    printf("%d\n", m);
}

