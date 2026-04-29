/* Source: https://www.geeksforgeeks.org/dsa/leaders-in-an-array/ */
#include <stdio.h>
#include <stdlib.h>

#include "tracer.h"

// Function to find the leaders in an array
int* leaders(int arr[], int n, int* resSize) {
    trace_var_init("n", n);
    trace_line(7);
    int* result = (int*)malloc(n * sizeof(int));
    trace_array_init("result", n);
    trace_line(8);
    int count = 0;
    trace_var_init("count", count);

    // Start with the rightmost element
    trace_line(11);
    int maxRight = arr[n - 1];
    trace_var_init("maxRight", maxRight);
    trace_array_highlight("arr", n - 1);

    // Rightmost element is always a leader
    trace_line(14);
    result[count++] = maxRight;
    trace_array("result", count - 1, result[count - 1]);
    trace_var("count", count);

    // Traverse the array from right to left
    trace_line(17);
    for (int i = n - 2; i >= 0; i--) {
        trace_line(17);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        trace_line(18);
        if (arr[i] >= maxRight) {
            trace_line(19);
            maxRight = arr[i];
            trace_var("maxRight", maxRight);
            trace_line(20);
            result[count++] = maxRight;
            trace_array("result", count - 1, result[count - 1]);
            trace_var("count", count);
        }
    }

    // Reverse the result array
    trace_line(25);
    for (int i = 0; i < count / 2; i++) {
        trace_line(25);
        trace_var_init("i", i);
        trace_line(26);
        int temp = result[i];
        trace_line(27);
        result[i] = result[count - i - 1];
        trace_array("result", i, result[i]);
        trace_line(28);
        result[count - i - 1] = temp;
        trace_array("result", count - i - 1, result[count - i - 1]);
    }

    trace_line(31);
    *resSize = count;
    trace_line(32);
    return result;
}

int main() {
    int arr[] = { 16, 17, 4, 3, 5, 2 };
    trace_array_init("arr", 6);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_line(37);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(38);
    int resSize;

    trace_line(40);
    int* result = leaders(arr, n, &resSize);
    trace_var_init("resSize", resSize);
    trace_line(41);
    for (int i = 0; i < resSize; i++) {
        trace_line(41);
        trace_var_init("i", i);
        trace_line(42);
        printf("%d ", result[i]);
    }
    trace_line(44);
    printf("\n");
    trace_line(45);
    return 0;
}
