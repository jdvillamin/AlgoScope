/* Source: https://www.geeksforgeeks.org/dsa/print-all-prime-factors-of-a-given-number/ */
#include <stdio.h>
#include <stdlib.h>

#include "tracer.h"

// A function to return all prime factors of a given number n
int primeFactors(int n, int **factors) {
    trace_var_init("n", n);
    trace_line(7);
    *factors = (int *)malloc(sizeof(int) * 10000); // allocate memory
    trace_line(8);
    int index = 0;
    trace_var_init("index", index);

    // Store the number of 2s that divide n
    trace_line(11);
    while (n % 2 == 0) {
        trace_line(11);
        trace_line(12);
        (*factors)[index++] = 2;
        trace_var("index", index);
        trace_line(13);
        n = n / 2;
        trace_var("n", n);
    }

    // n must be odd at this point. So we can
    // skip one element (i = i + 2)
    trace_line(18);
    for (int i = 3; i * i <= n; i = i + 2) {
        trace_line(18);
        trace_var_init("i", i);
        trace_line(19);
        while (n % i == 0) {
            trace_line(19);
            trace_line(20);
            (*factors)[index++] = i;
            trace_var("index", index);
            trace_line(21);
            n = n / i;
            trace_var("n", n);
        }
    }

    // If n is a prime number greater than 2
    trace_line(26);
    if (n > 2)
    {
        trace_line(27);
        (*factors)[index++] = n;
        trace_var("index", index);
    }

    // return number of factors stored
    trace_line(30);
    return index;
}

int main() {
    trace_line(34);
    int n = 18;
    trace_var_init("n", n);
    trace_line(35);
    int *ans;
    trace_line(36);
    int size = primeFactors(n, &ans);
    trace_var_init("size", size);

    // Print the factors stored in array
    trace_line(39);
    for (int i = 0; i < size; i++) {
        trace_line(39);
        trace_var_init("i", i);
        trace_line(40);
        printf("%d ", ans[i]);
    }

    trace_line(43);
    free(ans); // free allocated memory
    trace_line(44);
    return 0;
}
