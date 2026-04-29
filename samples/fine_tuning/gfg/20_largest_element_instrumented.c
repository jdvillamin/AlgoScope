/* Source: https://www.geeksforgeeks.org/dsa/program-to-find-largest-element-in-an-array/ */
#include <stdio.h>

#include "tracer.h"

int largest(int arr[], int n) {
    trace_var_init("n", n);
    trace_line(5);
    int i;
    trace_line(6);
    int max = arr[0];
    trace_var_init("max", max);

    // Traverse array elements from second and
    // compare every element with current max
    trace_line(10);
    for (i = 1; i < n; i++)
    {
        trace_line(10);
        trace_var("i", i);
        trace_array_highlight("arr", i);
        trace_line(11);
        if (arr[i] > max)
        {
            trace_line(12);
            max = arr[i];
            trace_var("max", max);
        }
    }

    trace_line(14);
    return max;
}

int main() {
    int arr[] = {20, 10, 20, 4, 100};
    trace_array_init("arr", 5);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_line(19);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);

    trace_line(21);
    printf("%d", largest(arr, n));
    trace_line(22);
    return 0;
}
