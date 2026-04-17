#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, count=0, divisor=0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        if (i%2 != 0) {
            for (int j = 1; j <= i; j++) {
                if (i%j == 0) {
                    divisor++;
                }
            }
            if (divisor >=8) {
                count++;
            }
            divisor = 0;

        }

    }
    printf("%d\n", count);



    return 0;
}
