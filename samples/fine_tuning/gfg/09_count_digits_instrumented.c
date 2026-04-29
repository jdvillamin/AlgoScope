/* Source: https://www.geeksforgeeks.org/dsa/program-count-digits-integer-3-different-methods/ */
#include <stdio.h>

#include "tracer.h"

int countDigit(int n)
{
    trace_var_init("n", n);

    // Base case
    trace_line(8);
    if (n == 0)
        return 1;

    trace_line(11);
    int count = 0;
    trace_var_init("count", count);

    // Iterate till n has digits remaining
    trace_line(14);
    while (n != 0)
    {
        trace_line(14);

        // Remove rightmost digit
        trace_line(18);
        n = n / 10;
        trace_var("n", n);

        // Increment digit count by 1
        trace_line(21);
        ++count;
        trace_var("count", count);
    }
    trace_line(23);
    return count;
}

int main()
{
    trace_line(28);
    int n = 58964;
    trace_var_init("n", n);
    trace_line(29);
    printf("%d\n", countDigit(n));
    trace_line(30);
    return 0;
}
