/* Source: https://www.geeksforgeeks.org/dsa/check-whether-given-number-even-odd/ */
#include <stdio.h>
#include <stdbool.h>

#include "tracer.h"

bool isEven(int n)
{
    trace_var_init("n", n);
    trace_line(7);
    return n % 2 == 0;
}

// Driver Code
int main()
{
    trace_line(13);
    int n = 15;
    trace_var_init("n", n);

    trace_line(15);
    if (isEven(n))
        printf("true\n");
    else
        printf("false\n");

    trace_line(20);
    return 0;
}
