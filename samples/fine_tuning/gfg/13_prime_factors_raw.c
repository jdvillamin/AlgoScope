/* Source: https://www.geeksforgeeks.org/dsa/print-all-prime-factors-of-a-given-number/ */
#include <stdio.h>
#include <stdlib.h>

// A function to return all prime factors of a given number n
int primeFactors(int n, int **factors) {
    *factors = (int *)malloc(sizeof(int) * 10000); // allocate memory
    int index = 0;

    // Store the number of 2s that divide n
    while (n % 2 == 0) {
        (*factors)[index++] = 2;
        n = n / 2;
    }

    // n must be odd at this point. So we can 
    // skip one element (i = i + 2)
    for (int i = 3; i * i <= n; i = i + 2) {
        while (n % i == 0) {
            (*factors)[index++] = i;
            n = n / i;
        }
    }

    // If n is a prime number greater than 2
    if (n > 2)
        (*factors)[index++] = n;
        
    // return number of factors stored
    return index; 
}

int main() {
    int n = 18;
    int *ans;
    int size = primeFactors(n, &ans);

    // Print the factors stored in array
    for (int i = 0; i < size; i++) {
        printf("%d ", ans[i]);
    }

    free(ans); // free allocated memory
    return 0;
}
