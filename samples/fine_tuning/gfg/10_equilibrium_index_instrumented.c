/* Source: https://www.geeksforgeeks.org/dsa/equilibrium-index-of-an-array/ */
#include <stdio.h>

#include "tracer.h"

int findEquilibrium(int arr[], int n) {
    trace_var_init("n", n);

    // Check for indexes one by one until
    // an equilibrium index is found
    trace_line(8);
    for (int i = 0; i < n; ++i) {
        trace_line(8);
        trace_var_init("i", i);
        trace_array_cell("arr", "i", i);

        // Get left sum
        trace_line(11);
        int leftSum = 0;
        trace_var_init("leftSum", leftSum);
        trace_line(12);
        for (int j = 0; j < i; j++)
        {
            trace_line(12);
            trace_var_init("j", j);
            trace_array_highlight("arr", j);
            trace_line(13);
            leftSum += arr[j];
            trace_var("leftSum", leftSum);
        }

        // Get right sum
        trace_line(16);
        int rightSum = 0;
        trace_var_init("rightSum", rightSum);
        trace_line(17);
        for (int j = i + 1; j < n; j++)
        {
            trace_line(17);
            trace_var_init("j", j);
            trace_array_highlight("arr", j);
            trace_line(18);
            rightSum += arr[j];
            trace_var("rightSum", rightSum);
        }

       // Check the condition
        trace_line(21);
        if (leftSum == rightSum)
            return i;
    }

    trace_line(25);
    return -1;
}

int main() {
    int arr[] = {-7, 1, 5, 2, -4, 3, 0};
    trace_array_init("arr", 7);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_array("arr", 6, arr[6]);
    trace_line(30);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);

    trace_line(32);
    printf("%d", findEquilibrium(arr, n));
    trace_line(33);
    return 0;
}
