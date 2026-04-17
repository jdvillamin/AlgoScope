#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {
    int n, m, i, x_len, x_offset, y_len, y_offset;
    long long sum = 0;
    long long *x, *y;
    scanf("%d %d", &n, &m);
    x = malloc(n * sizeof(long long));
    y = malloc(m * sizeof(long long));
    for (i = 0; i < n; i++) {
        scanf("%lld", &x[i]);
    }
    for (i = 0; i < m; i++) {
        scanf("%lld", &y[i]);
    }
    
    for (x_len = 1; x_len < n; x_len++) {
        for (x_offset = 0; x_len + x_offset < n; x_offset++){
            for (y_len = 1; y_len < m; y_len++) {
                for (y_offset = 0; y_len + y_offset < m; y_offset++){
                    sum += (x[x_offset + x_len] - x[x_offset]) * (y[y_offset + y_len] - y[y_offset]) ;
                    sum = sum % 1000000007;
                }
            }
        }
    }
    printf("%lld\n", sum);
    return 0;
}