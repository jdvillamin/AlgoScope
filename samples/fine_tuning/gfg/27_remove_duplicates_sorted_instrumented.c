/* Source: https://www.geeksforgeeks.org/dsa/remove-duplicates-sorted-array/ */
#include <stdio.h>

#include "tracer.h"

int removeDuplicates(int arr[], int n) {
    trace_var_init("n", n);
    trace_line(5);
    if (n <= 1)
        return n;

  	// Start from the second element
    trace_line(9);
    int idx = 1;
    trace_var_init("idx", idx);

    trace_line(11);
    for (int i = 1; i < n; i++) {
        trace_line(11);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        trace_line(12);
        if (arr[i] != arr[i - 1]) {
            trace_line(13);
            arr[idx++] = arr[i];
            trace_array("arr", idx - 1, arr[idx - 1]);
            trace_var("idx", idx);
        }
    }
    trace_line(16);
    return idx;
}

int main() {
    int arr[] = {1, 2, 2, 3, 4, 4, 4, 5, 5};
    trace_array_init("arr", 9);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_array("arr", 6, arr[6]);
    trace_array("arr", 7, arr[7]);
    trace_array("arr", 8, arr[8]);
    trace_line(21);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(22);
    int newSize = removeDuplicates(arr, n);
    trace_var_init("newSize", newSize);

    trace_line(24);
    for (int i = 0; i < newSize; i++)
    {
        trace_line(24);
        trace_var_init("i", i);
        trace_line(25);
        printf("%d ", arr[i]);
    }

    trace_line(27);
    return 0;
}
