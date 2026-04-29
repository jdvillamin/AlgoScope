/* Source: https://www.geeksforgeeks.org/dsa/swap-two-numbers-without-using-temporary-variable/ */
// C Code to swap two numbers using bitwise XOR
#include <stdio.h>

#include "tracer.h"

int main() {
    trace_line(6);
    int a = 10, b = 20;
    trace_var_init("a", a);
    trace_var_init("b", b);

    trace_line(8);
    a = a ^ b;
    trace_var("a", a);
    trace_line(9);
    b = a ^ b;
    trace_var("b", b);
    trace_line(10);
    a = a ^ b;
    trace_var("a", a);

    trace_line(12);
    printf("%d %d\n", a, b);
    trace_line(13);
    return 0;
}
