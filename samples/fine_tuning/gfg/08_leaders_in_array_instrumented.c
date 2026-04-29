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

    trace_line(10);
    for (int i = 0; i < n; i++) {
        trace_line(10);
        trace_var_init("i", i);
        trace_array_cell("arr", "i", i);
        trace_line(11);
        int j;

        // Check elements to the right
        trace_line(14);
        for (j = i + 1; j < n; j++) {
            trace_line(14);
            trace_var("j", j);
            trace_array_highlight("arr", j);

            // If a larger element is found
            trace_line(17);
            if (arr[i] < arr[j])
                break;
        }

        // If no larger element was found
        trace_line(22);
        if (j == n) {
            trace_line(23);
            result[count++] = arr[i];
            trace_array("result", count - 1, result[count - 1]);
            trace_var("count", count);
        }
    }

    *resSize = count;
    trace_line(27);
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
    trace_line(32);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(33);
    int resSize;

    trace_line(35);
    int* result = leaders(arr, n, &resSize);
    trace_line(36);
    for (int i = 0; i < resSize; i++) {
        trace_line(36);
        trace_var_init("i", i);
        trace_line(37);
        printf("%d ", result[i]);
    }
    trace_line(39);
    printf("\n");

    trace_line(41);
    free(result);
    trace_line(42);
    return 0;
}
