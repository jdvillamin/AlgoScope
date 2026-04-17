#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define N 200010
#define MAX 1000000000000000000
#define MOD 1000000007

#include <stdio.h>

int main (void) {
    unsigned long long n, a[200010], i, j, sum = 0;

    scanf("%llu", &n);

    for (i = 0; i < n; i++) {
        scanf("%llu", &(a[i]));
    }

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            sum = (sum + (a[i] * a[j]) % MOD) % MOD;
        }
    }
    printf("%llu", sum);

    return 0;
}

