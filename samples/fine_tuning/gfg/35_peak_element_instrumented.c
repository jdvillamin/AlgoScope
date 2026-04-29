/* Source: https://www.geeksforgeeks.org/dsa/find-a-peak-in-a-given-array/ */
#include <stdio.h>

#include "tracer.h"

int peakElement(int arr[], int n) {
    trace_var_init("n", n);
    trace_line(5);
    for (int i = 0; i < n; i++) {
        trace_line(5);
        trace_var_init("i", i);
        trace_array_cell("arr", "i", i);
        trace_line(6);
        int left = 1;
        trace_var_init("left", left);
        trace_line(7);
        int right = 1;
        trace_var_init("right", right);

        // Check for element to the left
        trace_line(10);
        if (i > 0 && arr[i] <= arr[i - 1])
        {
            trace_line(11);
            left = 0;
            trace_var("left", left);
        }

        // Check for element to the right
        trace_line(14);
        if (i < n - 1 && arr[i] <= arr[i + 1])
        {
            trace_line(15);
            right = 0;
            trace_var("right", right);
        }

        // If arr[i] is greater than its left as well as
        // its right element, return its index
        trace_line(19);
        if (left && right) {
            return i;
        }
    }
    trace_line(23);
    return 0;
}

int main() {
    int arr[] = {1, 2, 4, 5, 7, 8, 3};
    trace_array_init("arr", 7);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_array("arr", 6, arr[6]);
    trace_line(28);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(29);
    printf("%d\n", peakElement(arr, n));
    trace_line(30);
    return 0;
}
