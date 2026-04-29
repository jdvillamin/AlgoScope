/* Source: https://www.geeksforgeeks.org/dsa/sort-an-array-of-0s-1s-and-2s/ */
#include <stdio.h>

#include "tracer.h"

// Function to sort array containing 0s, 1s, and 2s
void sort012(int arr[], int n) {

    // initialize three pointers:
    // lo: boundary for 0s
    // mid: current element being checked
    // hi: boundary for 2s
    trace_line(11);
    int lo = 0;
    trace_var_init("lo", lo);
    trace_line(12);
    int hi = n - 1;
    trace_var_init("hi", hi);
    trace_line(13);
    int mid = 0;
    trace_var_init("mid", mid);

    // process elements until mid crosses hi
    trace_line(16);
    while (mid <= hi) {
        trace_line(16);
        trace_array_cell("arr", "lo", lo);
        trace_array_cell("arr", "mid", mid);
        trace_array_cell("arr", "hi", hi);
        trace_line(17);
        if (arr[mid] == 0) {

            // current is 0: swap with lo and move both
            // pointers forward
            trace_line(21);
            int temp = arr[lo];
            trace_line(22);
            arr[lo++] = arr[mid];
            trace_array("arr", lo - 1, arr[lo - 1]);
            trace_var("lo", lo);
            trace_line(23);
            arr[mid++] = temp;
            trace_array("arr", mid - 1, arr[mid - 1]);
            trace_var("mid", mid);
        }
        else if (arr[mid] == 1) {
            // current is 1: it's already in correct position
            trace_line(27);
            mid++;
            trace_var("mid", mid);
        }
        else {
            // current is 2: swap with hi and move hi backward
            // do not increment mid, as swapped value needs
            // to be re-checked
            trace_line(33);
            int temp = arr[mid];
            trace_line(34);
            arr[mid] = arr[hi];
            trace_array("arr", mid, arr[mid]);
            trace_line(35);
            arr[hi--] = temp;
            trace_array("arr", hi + 1, arr[hi + 1]);
            trace_var("hi", hi);
        }
    }
}

int main() {
    int arr[] = {0, 1, 2, 0, 1, 2};
    trace_array_init("arr", 6);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_line(42);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);

    // sort the array in-place
    trace_line(45);
    sort012(arr, n);

    trace_line(47);
    for (int i = 0; i < n; i++)
    {
        trace_line(47);
        trace_var_init("i", i);
        trace_line(48);
        printf("%d ", arr[i]);
    }

    trace_line(50);
    return 0;
}
