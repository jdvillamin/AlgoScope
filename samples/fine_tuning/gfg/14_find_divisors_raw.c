/* Source: https://www.geeksforgeeks.org/dsa/find-all-factors-of-a-natural-number/ */
#include <stdio.h>
#include <stdlib.h>

int* printDivisors(int n, int* size) {
    int* divisors = (int*)malloc(n * sizeof(int));
    *size = 0;

    for (int i = 1; i <= n; i++) {
       
        // i is a divisor of n
        if (n % i == 0) {
            divisors[(*size)++] = i;
        }
    }

    return divisors;
}

int main() {
    int size;
    int* divisors = printDivisors(10, &size);
    for (int i = 0; i < size; i++) {
        printf("%d ", divisors[i]);
    }

    free(divisors);
    return 0;
}
