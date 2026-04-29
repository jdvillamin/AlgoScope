/* Source: https://www.geeksforgeeks.org/dsa/program-to-print-multiplication-table-of-a-number/ */
#include <stdio.h>

#include "tracer.h"

void printTable(int n) {
    trace_var_init("n", n);
    trace_line(5);
    for (int i = 1; i <= 10; ++i)
    {
        trace_line(5);
        trace_var_init("i", i);
        trace_line(6);
        printf("%d * %d = %d\n", n, i, n * i);
    }
}

int main() {
    trace_line(10);
    int n = 5;
    trace_var_init("n", n);
    trace_line(11);
    printTable(n);
    trace_line(12);
    return 0;
}
