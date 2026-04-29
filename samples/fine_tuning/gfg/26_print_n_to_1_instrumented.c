/* Source: https://www.geeksforgeeks.org/dsa/print-n-to-1-without-loop/ */
#include <stdio.h>

#include "tracer.h"

void printNos(int n){
    trace_var_init("n", n);

    // base case
    trace_line(7);
    if (n == 0)
        return;

    trace_line(10);
    printf("%d ", n);

    // recursive call
    trace_line(13);
    printNos(n - 1);
}

int main(){
    trace_line(17);
    int n = 3;
    trace_var_init("n", n);

    trace_line(19);
    printNos(n);

    trace_line(21);
    return 0;
}
