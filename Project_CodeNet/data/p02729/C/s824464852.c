#include <stdio.h>

int main(void) {
    int a,b;

    scanf("%d %d", &a, &b);

    printf("%d\n", (a*(a-1)/2) + (b*(b-1)/2) );
    return 0;
}