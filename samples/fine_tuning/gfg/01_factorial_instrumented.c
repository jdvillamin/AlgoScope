/* Source: https://www.geeksforgeeks.org/dsa/program-for-factorial-of-a-number/ */
#include <stdio.h>

#include "tracer.h"

int factorial(int n)
{
    trace_var_init("n", n);

    // Calculating factorial of number
    trace_line(8);
    int ans = 1, i;
    trace_var_init("ans", ans);
    trace_line(9);
    for (i = 2; i <= n; i++)
    {
        trace_line(9);
        trace_var("i", i);
        trace_line(10);
        ans *= i;
        trace_var("ans", ans);
    }
    trace_line(11);
    return ans;
}

int main()
{
    trace_line(16);
    int num = 5;
    trace_var_init("num", num);
    trace_line(17);
    printf("%d\n", factorial(num));
    trace_line(18);
    return 0;
}
