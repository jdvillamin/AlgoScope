/* Source: https://www.geeksforgeeks.org/dsa/longest-zig-zag-subsequence/ */
// C program to find longest Zig-Zag subsequence in
// an array
#include <stdio.h>
#include <stdlib.h>

#include "tracer.h"

// function to return max of two numbers
int max(int a, int b) {  return (a > b) ? a : b; }

// Function to return longest Zig-Zag subsequence length
int zzis(int arr[], int n)
{
    trace_var_init("n", n);
    /*Z[i][0] = Length of the longest Zig-Zag subsequence
          ending at index i and last element is greater
          than its previous element
     Z[i][1] = Length of the longest Zig-Zag subsequence
          ending at index i and last element is smaller
          than its previous element   */
    trace_line(19);
    int Z[n][2];
    trace_array2d_init("Z", n, 2);

    /* Initialize all values from 1  */
    trace_line(22);
    for (int i = 0; i < n; i++)
    {
        trace_line(22);
        trace_var_init("i", i);
        trace_line(23);
        Z[i][0] = Z[i][1] = 1;
        trace_array2d("Z", i, 0, Z[i][0]);
        trace_array2d("Z", i, 1, Z[i][1]);
    }

    trace_line(25);
    int res = 1; // Initialize result
    trace_var_init("res", res);

    /* Compute values in bottom up manner */
    trace_line(28);
    for (int i = 1; i < n; i++)
    {
        trace_line(28);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        // Consider all elements as previous of arr[i]
        trace_line(31);
        for (int j = 0; j < i; j++)
        {
            trace_line(31);
            trace_var_init("j", j);
            trace_array_highlight("arr", j);
            // If arr[i] is greater, then check with Z[j][1]
            trace_line(34);
            trace_array2d_highlight("Z", j, 1);
            trace_array2d_highlight("Z", i, 0);
            if (arr[j] < arr[i] && Z[i][0] < Z[j][1] + 1)
            {
                trace_line(35);
                Z[i][0] = Z[j][1] + 1;
                trace_array2d("Z", i, 0, Z[i][0]);
            }

            // If arr[i] is smaller, then check with Z[j][0]
            trace_line(38);
            trace_array2d_highlight("Z", j, 0);
            trace_array2d_highlight("Z", i, 1);
            if( arr[j] > arr[i] && Z[i][1] < Z[j][0] + 1)
            {
                trace_line(39);
                Z[i][1] = Z[j][0] + 1;
                trace_array2d("Z", i, 1, Z[i][1]);
            }
        }

        /* Pick maximum of both values at index i  */
        trace_line(43);
        if (res < max(Z[i][0], Z[i][1]))
        {
            trace_line(44);
            res = max(Z[i][0], Z[i][1]);
            trace_var("res", res);
        }
    }

    trace_line(47);
    return res;
}

/* Driver program */
int main()
{
    int arr[] = { 10, 22, 9, 33, 49, 50, 31, 60 };
    trace_array_init("arr", 8);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_array("arr", 6, arr[6]);
    trace_array("arr", 7, arr[7]);
    trace_line(54);
    int n = sizeof(arr)/sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(55);
    printf("Length of Longest Zig-Zag subsequence is %d\n",
            zzis(arr, n) );
    trace_line(57);
    return 0;
}
