/* Source: https://www.geeksforgeeks.org/dsa/find-number-closest-n-divisible-m/ */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "tracer.h"

int closestNumber(int n, int m) {
    trace_var_init("n", n);
    trace_var_init("m", m);
    // find the quotient
    trace_line(8);
    int closest = 0;
    trace_var_init("closest", closest);
    trace_line(9);
    int minDifference = INT_MAX;
    trace_var_init("minDifference", minDifference);

    // Check numbers around n
    trace_line(12);
    for (int i = n - abs(m); i <= n + abs(m); ++i) {
        trace_line(12);
        trace_var_init("i", i);
        trace_line(13);
        if (i % m == 0) {
            trace_line(14);
            int difference = abs(n - i);
            trace_var_init("difference", difference);

            trace_line(16);
            if (difference < minDifference ||
               (difference == minDifference && abs(i) > abs(closest))) {
                trace_line(18);
                closest = i;
                trace_var("closest", closest);
                trace_line(19);
                minDifference = difference;
                trace_var("minDifference", minDifference);
            }
        }
    }
    trace_line(23);
    return closest;
}

int main() {
    trace_line(27);
    int n = 13, m = 4;
    trace_var_init("n", n);
    trace_var_init("m", m);
    trace_line(28);
    printf("%d\n", closestNumber(n, m));

    trace_line(30);
    return 0;
}
