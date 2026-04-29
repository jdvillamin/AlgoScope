/* Source: https://www.geeksforgeeks.org/dsa/majority-element/ */
#include <stdio.h>

#include "tracer.h"

int majorityElement(int arr[], int n) {
    trace_var_init("n", n);

    // Loop to consider each element as
    // a candidate for majority
    trace_line(8);
    for (int i = 0; i < n; i++) {
        trace_line(8);
        trace_var_init("i", i);
        trace_array_cell("arr", "i", i);
        trace_line(9);
        int count = 0;
        trace_var_init("count", count);

        // Inner loop to count the frequency of arr[i]
        trace_line(12);
        for (int j = 0; j < n; j++) {
            trace_line(12);
            trace_var_init("j", j);
            trace_array_highlight("arr", j);
            trace_line(13);
            if (arr[i] == arr[j]) {
                trace_line(14);
                count++;
                trace_var("count", count);
            }
        }

        // Check if count of arr[i] is more
        // than half the size of the array
        trace_line(20);
        if (count > n / 2) {
            trace_line(21);
            return arr[i];
        }
    }

    // If no majority element found, return -1
    trace_line(26);
    return -1;
}

int main() {
    int arr[] = {1, 1, 2, 1, 3, 5, 1};
    trace_array_init("arr", 7);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_array("arr", 6, arr[6]);
    trace_line(31);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);

    trace_line(33);
    printf("%d\n", majorityElement(arr, n));

    trace_line(35);
    return 0;
}
