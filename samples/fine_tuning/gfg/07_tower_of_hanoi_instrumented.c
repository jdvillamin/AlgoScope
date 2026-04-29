/* Source: https://www.geeksforgeeks.org/dsa/c-program-for-tower-of-hanoi/ */
#include <stdio.h>

#include "tracer.h"

void towerOfHanoi(int n, char fromRod, char toRod, char auxRod) {
    trace_var_init("n", n);
    trace_var_init("fromRod", fromRod);
    trace_var_init("toRod", toRod);
    trace_var_init("auxRod", auxRod);
    trace_line(5);
    if (n == 0) {
        return;
    }
    trace_line(8);
    towerOfHanoi(n - 1, fromRod, auxRod, toRod);
    trace_line(9);
    printf("Disk %d moved from %c to %c\n", n, fromRod, toRod);
    trace_line(10);
    towerOfHanoi(n - 1, auxRod, toRod, fromRod);
}

int main() {
    trace_line(14);
    int n = 3;
    trace_var_init("n", n);

    // A, B and C are names of rods
    trace_line(17);
    towerOfHanoi(n, 'A', 'C', 'B');
    trace_line(18);
    return 0;
}
