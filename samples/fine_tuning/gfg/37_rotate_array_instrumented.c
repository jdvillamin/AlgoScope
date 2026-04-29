/* Source: https://www.geeksforgeeks.org/dsa/array-rotation/ */
// C Program to left rotate the array by d positions
// using temporary array

#include <stdio.h>
#include <stdlib.h>

#include "tracer.h"

// Function to rotate array
void rotateArr(int* arr, int d, int n) {
    trace_var_init("d", d);
    trace_var_init("n", n);

    // Handle case when d > n
    trace_line(12);
    d %= n;
    trace_var("d", d);

    // Storing rotated version of array
    trace_line(15);
    int temp[n];
    trace_array_init("temp", n);

    // Copy last n - d elements to the front of temp
    trace_line(18);
    for (int i = 0; i < n - d; i++)
    {
        trace_line(18);
        trace_var_init("i", i);
        trace_line(19);
        temp[i] = arr[d + i];
        trace_array("temp", i, temp[i]);
    }

    // Copy the first d elements to the back of temp
    trace_line(22);
    for (int i = 0; i < d; i++)
    {
        trace_line(22);
        trace_var_init("i", i);
        trace_line(23);
        temp[n - d + i] = arr[i];
        trace_array("temp", n - d + i, temp[n - d + i]);
    }

    // Copying the elements of temp in arr
    // to get the final rotated array
    trace_line(27);
    for (int i = 0; i < n; i++)
    {
        trace_line(27);
        trace_var_init("i", i);
        trace_line(28);
        arr[i] = temp[i];
        trace_array("arr", i, arr[i]);
    }
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
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
    int d = 2;
    trace_var_init("d", d);

    trace_line(36);
    rotateArr(arr, d, n);

    // Print the rotated array
    trace_line(39);
    for (int i = 0; i < n; i++)
    {
        trace_line(39);
        trace_var_init("i", i);
        trace_line(40);
        printf("%d ", arr[i]);
    }

    trace_line(42);
    return 0;
}
