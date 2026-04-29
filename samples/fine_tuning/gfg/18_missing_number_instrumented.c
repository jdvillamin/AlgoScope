/* Source: https://www.geeksforgeeks.org/find-the-smallest-positive-number-missing-from-an-unsorted-array-set-3/ */
// C program to find the smallest positive missing number
// by marking indices

#include <stdio.h>

#include "tracer.h"

// Function for finding the first missing positive number
int missingNumber(int arr[], int n) {
    trace_var_init("n", n);
    trace_line(9);
    int flag = 0;
    trace_var_init("flag", flag);

    // Check if 1 is present in array or not
    trace_line(12);
    for (int i = 0; i < n; i++) {
        trace_line(12);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        trace_line(13);
        if (arr[i] == 1) {
            trace_line(14);
            flag = 1;
            trace_var("flag", flag);
            trace_line(15);
            break;
        }
    }

    // If 1 is not present
    trace_line(20);
    if (flag == 0)
        return 1;

    // Change out of range values to 1
    trace_line(24);
    for (int i = 0; i < n; i++) {
        trace_line(24);
        trace_var_init("i", i);
        trace_line(25);
        if (arr[i] <= 0 || arr[i] > n)
        {
            trace_line(26);
            arr[i] = 1;
            trace_array("arr", i, arr[i]);
        }
    }

    // Mark the occurrence of numbers
    // directly within the same array
    trace_line(31);
    for (int i = 0; i < n; i++) {
        trace_line(31);
        trace_var_init("i", i);
        trace_line(32);
        arr[(arr[i] - 1) % n] += n;
        trace_array("arr", (arr[i] - 1) % n, arr[(arr[i] - 1) % n]);
    }

    // Finding which index has value less than n
    trace_line(36);
    for (int i = 0; i < n; i++) {
        trace_line(36);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        trace_line(37);
        if (arr[i] <= n)
            return i + 1;
    }

    // If array has values from 1 to n
    trace_line(42);
    return n + 1;
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
    trace_line(47);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);

    trace_line(49);
    printf("%d", missingNumber(arr, n));
    trace_line(50);
    return 0;
}
