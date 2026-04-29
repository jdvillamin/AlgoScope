/* Source: https://www.geeksforgeeks.org/dsa/count-trailing-zeroes-factorial-number/ */
#include <stdio.h>

#include "tracer.h"

int trailingZeroes(int n)
{
    trace_var_init("n", n);
    // Edge Case
    trace_line(7);
    if (n < 0)
        return -1;

    // Initialize result
    trace_line(11);
    int count = 0;
    trace_var_init("count", count);

    // Keep dividing n by powers of
    // 5 and update count
    trace_line(15);
    for (int i = 5; n / i >= 1; i *= 5)
    {
        trace_line(15);
        trace_var_init("i", i);
        trace_line(16);
        count += n / i;
        trace_var("count", count);
    }

    trace_line(18);
    return count;
}

int main()
{
    trace_line(23);
    int n = 10;
    trace_var_init("n", n);
    trace_line(24);
    printf("%d\n", trailingZeroes(n));
    trace_line(25);
    return 0;
}
