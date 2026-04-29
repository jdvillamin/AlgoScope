/* Source: https://www.geeksforgeeks.org/dsa/a-product-array-puzzle/ */
#include <stdio.h>

#include "tracer.h"

void productExceptSelf(int arr[], int n, int res[]) {
    trace_var_init("n", n);

    // Initialize result array as 1
    trace_line(7);
    for (int i = 0; i < n; i++) {
        trace_line(7);
        trace_var_init("i", i);
        trace_line(8);
        res[i] = 1;
        trace_array("res", i, res[i]);
    }

    trace_line(11);
    for (int i = 0; i < n; i++) {
        trace_line(11);
        trace_var_init("i", i);
        trace_array_cell("arr", "i", i);

      	// Compute product of all elements except arr[i]
        trace_line(14);
        for (int j = 0; j < n; j++) {
            trace_line(14);
            trace_var_init("j", j);
            trace_array_highlight("arr", j);
            trace_line(15);
            if (i != j) {
                trace_line(16);
                res[i] *= arr[j];
                trace_array("res", i, res[i]);
            }
        }
    }
}

int main() {
    int arr[] = {10, 3, 5, 6, 2};
    trace_array_init("arr", 5);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_line(24);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(25);
    int res[n];
    trace_array_init("res", n);

    trace_line(27);
    productExceptSelf(arr, n, res);

    trace_line(29);
    for (int i = 0; i < n; i++) {
        trace_line(29);
        trace_var_init("i", i);
        trace_line(30);
        printf("%d ", res[i]);
    }

    trace_line(33);
    return 0;
}
