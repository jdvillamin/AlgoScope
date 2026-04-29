/* Source: https://www.geeksforgeeks.org/dsa/find-second-largest-element-array/ */
// C program to find second largest element in an array using Sorting

#include <stdio.h>

#include "tracer.h"

// function to compare two integers for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// function to find the second largest element
int getSecondLargest(int arr[], int n) {
    trace_var_init("n", n);

    // Sort the array in non-decreasing order
    trace_line(15);
    qsort(arr, n, sizeof(int), compare);
    for (int _i = 0; _i < n; _i++) { trace_array("arr", _i, arr[_i]); }

    // start from second last element as last element is the largest
    trace_line(18);
    for (int i = n - 2; i >= 0; i--) {
        trace_line(18);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);

        // return the first element which is not equal to the
        // largest element
        trace_line(22);
        if (arr[i] != arr[n - 1]) {
            trace_line(23);
            return arr[i];
        }
    }

    // If no second largest element was found, return -1
    trace_line(28);
    return -1;
}

int main() {
    int arr[] = { 12, 35, 1, 10, 34, 1 };
    trace_array_init("arr", 6);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_line(33);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(34);
    printf("%d\n", getSecondLargest(arr, n));
    trace_line(35);
    return 0;
}
