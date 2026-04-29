/* Source: https://www.geeksforgeeks.org/dsa/maximum-product-subarray/ */
#include <stdio.h>

#include "tracer.h"

int maxProduct(int arr[], int n) {
    trace_var_init("n", n);

    // Initializing result
    trace_line(7);
    int maxProd = arr[0];
    trace_var_init("maxProd", maxProd);

    trace_line(9);
    for (int i = 0; i < n; i++) {
        trace_line(9);
        trace_var_init("i", i);
        trace_array_cell("arr", "i", i);
        trace_line(10);
        int mul = 1;
        trace_var_init("mul", mul);

        // traversing in current subarray
        trace_line(13);
        for (int j = i; j < n; j++) {
            trace_line(13);
            trace_var_init("j", j);
            trace_array_highlight("arr", j);
          	trace_line(14);
            mul *= arr[j];
            trace_var("mul", mul);

            // updating result every time
            // to keep track of the maximum product
            trace_line(18);
            maxProd = (maxProd > mul) ? maxProd : mul;
            trace_var("maxProd", maxProd);
        }
    }
    trace_line(21);
    return maxProd;
}

int main() {

    int arr[] = { -2, 6, -3, -10, 0, 2 };
    trace_array_init("arr", 6);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_line(27);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);

    trace_line(29);
    printf("%lld\n", maxProduct(arr, n));

    trace_line(31);
    return 0;
}
