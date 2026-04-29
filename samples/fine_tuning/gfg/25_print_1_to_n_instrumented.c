/* Source: https://www.geeksforgeeks.org/dsa/print-1-to-n-without-using-loops/ */
#include <stdio.h>

#include "tracer.h"

void printNos(int n){
    trace_var_init("n", n);

    // base condition
    trace_line(7);
    if (n == 0)
        return;

    // recursive call
    trace_line(11);
    printNos(n - 1);
    trace_line(12);
    printf("%d ", n);
}

int main(){
    trace_line(16);
    int n = 3;
    trace_var_init("n", n);
    trace_line(17);
    printNos(n);
    trace_line(18);
    return 0;
}
