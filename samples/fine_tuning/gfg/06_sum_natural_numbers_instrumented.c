/* Source: https://www.geeksforgeeks.org/dsa/program-find-sum-first-n-natural-numbers/ */
#include <stdio.h>

#include "tracer.h"

int findSum(int n){
    trace_var_init("n", n);
    trace_line(4);
    int sum = 0;
    trace_var_init("sum", sum);

    // iterating over all the numbers
    // between 1 to n
    trace_line(8);
    for (int i = 1; i <= n; i++)
    {
        trace_line(8);
        trace_var_init("i", i);
        trace_line(10);
        sum = sum + i;
        trace_var("sum", sum);
    }
    trace_line(12);
    return sum;
}
int main()
{
    trace_line(16);
    int n = 5;
    trace_var_init("n", n);
    trace_line(17);
    printf("%d", findSum(n));
    trace_line(18);
    return 0;
}
