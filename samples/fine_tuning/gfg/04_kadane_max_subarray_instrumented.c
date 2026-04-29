/* Source: https://www.geeksforgeeks.org/dsa/largest-sum-contiguous-subarray/ */
#include <stdio.h>
#include <limits.h>

#include "tracer.h"

int maxSubarraySum(int arr[], int size) {
    trace_var_init("size", size);

    // Stores the result (maximum sum found so far)
    trace_line(8);
    int res = arr[0];
    trace_var_init("res", res);

    // Maximum sum of subarray ending at current position
    trace_line(11);
    int maxEnding = arr[0];
    trace_var_init("maxEnding", maxEnding);

    trace_line(13);
    for (int i = 1; i < size; i++) {
        trace_line(13);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);

        // Either extend the previous subarray or start
        // new from current element
        trace_line(17);
        maxEnding = (maxEnding + arr[i] > arr[i]) ?
          									maxEnding + arr[i] : arr[i];
        trace_var("maxEnding", maxEnding);

        // Update result if the new subarray sum is larger
        trace_line(21);
        res = (res > maxEnding) ? res : maxEnding;
        trace_var("res", res);
    }
    trace_line(23);
    return res;
}

int main() {
    int arr[] = {2, 3, -8, 7, -1, 2, 3};
    trace_array_init("arr", 7);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_array("arr", 6, arr[6]);
    trace_line(28);
    int size = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("size", size);
    trace_line(29);
    printf("%lld\n", maxSubarraySum(arr, size));
    trace_line(30);
    return 0;
}
