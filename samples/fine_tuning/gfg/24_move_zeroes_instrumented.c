/* Source: https://www.geeksforgeeks.org/dsa/move-zeroes-end-array/ */
#include <stdio.h>

#include "tracer.h"

void pushZerosToEnd(int *arr, int n)
{
    trace_var_init("n", n);
    trace_line(6);
    int temp[n];
    trace_array_init("temp", n);

    // to keep track of the index in temp[]
    trace_line(9);
    int j = 0;
    trace_var_init("j", j);

    // Copy non-zero elements to temp[]
    trace_line(12);
    for (int i = 0; i < n; i++)
    {
        trace_line(12);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        trace_line(14);
        if (arr[i] != 0)
        {
            trace_line(15);
            temp[j++] = arr[i];
            trace_array("temp", j - 1, temp[j - 1]);
            trace_var("j", j);
        }
    }

    // Fill remaining positions in temp[] with zeros
    trace_line(19);
    while (j < n)
    {
        trace_line(19);
        trace_line(20);
        temp[j++] = 0;
        trace_array("temp", j - 1, temp[j - 1]);
        trace_var("j", j);
    }

    // Copy all the elements from temp[] to arr[]
    trace_line(23);
    for (int i = 0; i < n; i++)
    {
        trace_line(23);
        trace_var_init("i", i);
        trace_line(24);
        arr[i] = temp[i];
        trace_array("arr", i, arr[i]);
    }
}

int main()
{
    int arr[] = {1, 2, 0, 4, 3, 0, 5, 0};
    trace_array_init("arr", 8);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_array("arr", 6, arr[6]);
    trace_array("arr", 7, arr[7]);
    trace_line(30);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);

    trace_line(32);
    pushZerosToEnd(arr, n);

    trace_line(34);
    for (int i = 0; i < n; i++)
    {
        trace_line(34);
        trace_var_init("i", i);
        trace_line(36);
        printf("%d ", arr[i]);
    }
    trace_line(38);
    return 0;
}
