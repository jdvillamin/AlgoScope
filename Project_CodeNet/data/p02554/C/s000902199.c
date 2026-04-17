#include <stdio.h>

#define mod (long long)(1e9 + 7)

int main() {
    int n;
    long long pot10 = 1, pot9 = 1, pot8 = 1;

    scanf("%d", &n);

    for (int i=0; i<n; ++i) {
        pot10 = (pot10 * 10)%mod;
        pot9 = (pot9 * 9)%mod;
        pot8 = (pot8 * 8)%mod;
    }

    long long invalidos = ((pot9+pot9)%mod - pot8)%mod;

    printf("%lld\n", (pot10%mod - invalidos%mod)%mod);

    return 0;
} 