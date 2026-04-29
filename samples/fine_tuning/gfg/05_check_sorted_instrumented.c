/* Source: https://www.geeksforgeeks.org/dsa/program-check-array-sorted-not-iterative-recursive/ */
#include <stdio.h>
#include <stdbool.h>

#include "tracer.h"

bool isSorted(int arr[], int n) {
    trace_var_init("n", n);

     // Iterate over the array and check if
    // every element is greater than or
    // equal to previous element.
    trace_line(10);
    for (int i = 1; i < n; i++) {
        trace_line(10);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        trace_line(11);
        if (arr[i - 1] > arr[i])
            return false;
    }

    trace_line(15);
    return true;
}

int main() {
    int arr[] = { 10, 20, 30, 40, 50 };
    trace_array_init("arr", 5);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_line(20);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);

    trace_line(22);
    if (isSorted(arr, n))
        printf("true\n");
    else
        printf("false\n");

    trace_line(27);
    return 0;
}
