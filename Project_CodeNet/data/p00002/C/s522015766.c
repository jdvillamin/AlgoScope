#include <stdio.h>

int hill[10];

int main(void) {
    int a, b;

    while(scanf("%d%d", &a, &b)) {
        int size = 0;
        int sum = a + b;

        while(sum > 0) {
            size += 1;
            sum /= 10;
        }
        printf("%d\n", size);
    }

    return 0;
}