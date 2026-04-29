/* Source: https://www.geeksforgeeks.org/dsa/count-number-of-ways-to-cover-a-distance/ */
// C program to count number of
// ways to reach nth stair.
#include <stdio.h>

#include "tracer.h"

int countWays(int n) {
    trace_var_init("n", n);

    // Base case for 0th and 1st stair
    trace_line(9);
    if (n == 0 || n == 1)
        return 1;

    // base case for 2nd stair
    trace_line(13);
    if (n == 2)
        return 2;

    // Variables to store values
    // of previous 3 stairs.
    int prev1, prev2, prev3;

    // insert ans values for 0,1,2 stair
    trace_line(21);
    prev3 = 1;
    trace_var_init("prev3", prev3);
    trace_line(22);
    prev2 = 1;
    trace_var_init("prev2", prev2);
    trace_line(23);
    prev1 = 2;
    trace_var_init("prev1", prev1);

    // building dp in bottom up manner
    trace_line(26);
    for (int i = 3; i <= n; i++) {
        trace_line(26);
        trace_var_init("i", i);
        trace_line(27);
        int val = prev1 + prev2 + prev3;
        trace_var_init("val", val);

        // Replace previous stair values
        // with next stairs.
        trace_line(31);
        prev3 = prev2;
        trace_var("prev3", prev3);
        trace_line(32);
        prev2 = prev1;
        trace_var("prev2", prev2);
        trace_line(33);
        prev1 = val;
        trace_var("prev1", prev1);
    }

    trace_line(36);
    return prev1;
}

int main() {

    trace_line(41);
    int n = 4;
    trace_var_init("n", n);
    trace_line(42);
    printf("%d\n", countWays(n));
    trace_line(43);
    return 0;
}
