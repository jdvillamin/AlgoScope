/* Source: https://www.geeksforgeeks.org/dsa/write-a-c-program-to-calculate-powxn/ */
#include <stdio.h>
#include <math.h>

#include "tracer.h"

double power(double b, int e) {
    trace_var_init("e", e);

    // Initialize result to 1
    trace_line(8);
    double pow = 1;

    // Multiply b for e times
    trace_line(11);
    for (int i = 0; i < abs(e); i++)
    {
        trace_line(11);
        trace_var_init("i", i);
        trace_line(12);
        pow = pow * b;
    }

    trace_line(14);
    if (e < 0)
        return 1 / pow;

    trace_line(17);
    return pow;
}

int main() {
    trace_line(21);
    double b = 3.0;
    trace_line(22);
    int e = 5;
    trace_var_init("e", e);
    trace_line(23);
    double res = power(b, e);
    trace_line(24);
    printf("%f", res);
    trace_line(25);
    return 0;
}
