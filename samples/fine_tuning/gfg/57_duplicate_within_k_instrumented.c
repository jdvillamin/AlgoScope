/* Source: https://www.geeksforgeeks.org/dsa/check-given-array-contains-duplicate-elements-within-k-distance/ */
#include <stdio.h>

#include "tracer.h"

int checkDuplicatesWithinK(int arr[], int n, int k)
{
    trace_var_init("n", n);
    trace_var_init("k", k);
    // Traverse for every element
    trace_line(7);
    for (int i = 0; i < n; i++) {
        trace_line(7);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
      
        // Traverse next k elements
        trace_line(10);
        for (int c = 1; c <= k && (i + c) < n; c++) {
            trace_line(10);
            trace_var_init("c", c);
            trace_line(11);
            int j = i + c;
            trace_var_init("j", j);
            trace_array_highlight("arr", j);
          
            // If we find one more occurrence within k
            trace_line(14);
            if (arr[i] == arr[j])
            {
                trace_line(15);
                return 1; 
            }
        }
    }
    trace_line(18);
    return 0; 
}

// Driver method to test above method
int main()
{
    int arr[] = {10, 5, 3, 4, 3, 5, 6};
    trace_array_init("arr", 7);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_array("arr", 6, arr[6]);
    trace_line(25);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(26);
    printf("%s\n", checkDuplicatesWithinK(arr, n, 3) ? "Yes" : "No");
    trace_line(27);
    return 0;
}
