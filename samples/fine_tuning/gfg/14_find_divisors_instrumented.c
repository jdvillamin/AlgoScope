/* Source: https://www.geeksforgeeks.org/dsa/find-all-factors-of-a-natural-number/ */
#include <stdio.h>
#include <stdlib.h>

#include "tracer.h"

int* printDivisors(int n, int* size) {
    trace_var_init("n", n);
    trace_line(6);
    int* divisors = (int*)malloc(n * sizeof(int));
    trace_array_init("divisors", n);
    trace_line(7);
    *size = 0;

    trace_line(9);
    for (int i = 1; i <= n; i++) {
        trace_line(9);
        trace_var_init("i", i);

        // i is a divisor of n
        trace_line(12);
        if (n % i == 0) {
            trace_line(13);
            divisors[(*size)++] = i;
            trace_array("divisors", *size - 1, divisors[*size - 1]);
        }
    }

    trace_line(17);
    return divisors;
}

int main() {
    trace_line(21);
    int size;
    trace_line(22);
    int* divisors = printDivisors(10, &size);
    trace_var_init("size", size);
    trace_line(23);
    for (int i = 0; i < size; i++) {
        trace_line(23);
        trace_var_init("i", i);
        trace_line(24);
        printf("%d ", divisors[i]);
    }

    trace_line(27);
    free(divisors);
    trace_line(28);
    return 0;
}
