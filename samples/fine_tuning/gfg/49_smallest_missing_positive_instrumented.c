/* Source: https://www.geeksforgeeks.org/dsa/find-the-smallest-positive-number-missing-from-an-unsorted-array/ */
#include <stdio.h>

#include "tracer.h"

int partition(int *arr, int n) {
    trace_var_init("n", n);
    trace_line(5);
    int pivotIdx = 0;
    trace_var_init("pivotIdx", pivotIdx);

    trace_line(7);
    for (int i = 0; i < n; i++) {
        trace_line(7);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        
        // Move positive elements to the left
        trace_line(10);
        if (arr[i] > 0) {
            trace_line(11);
            int temp = arr[i];
            trace_line(12);
            arr[i] = arr[pivotIdx];
            trace_array("arr", i, arr[i]);
            trace_line(13);
            arr[pivotIdx] = temp;
            trace_array("arr", pivotIdx, arr[pivotIdx]);
            trace_line(14);
            pivotIdx++;
            trace_var("pivotIdx", pivotIdx);
        }
    }

    // return index of the first non-positive number
    trace_line(19);
    return pivotIdx;
}

int missingNumber(int *arr, int n) {
    trace_var_init("n", n);
    trace_line(23);
    int k = partition(arr, n);
    trace_var_init("k", k);

    // Traverse the positive part of the array
    trace_line(26);
    for (int i = 0; i < k; i++) {
        trace_line(26);
        trace_var_init("i", i);
        
        // Find the absolute value to get the original number
        trace_line(29);
        int val = abs(arr[i]);
        trace_var_init("val", val);

        // If val is within range, then mark the element at
        // index val-1 to negative
        trace_line(33);
        trace_array_highlight("arr", i);
        if (val - 1 < k && arr[val - 1] > 0) {
            trace_line(34);
            arr[val - 1] = -arr[val - 1];
            trace_array("arr", val - 1, arr[val - 1]);
        }
    }

    // Find first unmarked index
    trace_line(39);
    for (int i = 0; i < k; i++) {
        trace_line(39);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        trace_line(40);
        if (arr[i] > 0) {
            trace_line(41);
            return i + 1;
        }
    }

    // If all numbers from 1 to k are marked then
    // missing number is k + 1
    trace_line(47);
    return k + 1;
}

int main() {
 
    int arr[] = {2, -3, 4, 1, 1, 7};
    trace_array_init("arr", 6);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_line(53);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(54);
    printf("%d\n", missingNumber(arr, n));
    trace_line(55);
    return 0;
}
