/* Source: https://www.geeksforgeeks.org/dsa/majority-element/ */
#include <stdio.h>

#include "tracer.h"

int majorityElement(int arr[], int n) {
    trace_var_init("n", n);

    trace_line(6);
    int candidate = -1;
    trace_var_init("candidate", candidate);
    trace_line(7);
    int count = 0;
    trace_var_init("count", count);

    // Find a candidate
    trace_line(10);
    for (int i = 0; i < n; i++) {
        trace_line(10);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);

        trace_line(12);
        if (count == 0) {
            trace_line(13);
            candidate = arr[i];
            trace_var("candidate", candidate);
            trace_line(14);
            count = 1;
            trace_var("count", count);
        }
        else if (arr[i] == candidate) {
            trace_line(17);
            count++;
            trace_var("count", count);
        }
        else {
            trace_line(20);
            count--;
            trace_var("count", count);
        }
    }

    // Validate the candidate
    trace_line(25);
    count = 0;
    trace_var("count", count);
    trace_line(26);
    for (int i = 0; i < n; i++) {
        trace_line(26);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        trace_line(27);
        if (arr[i] == candidate) {
            trace_line(28);
            count++;
            trace_var("count", count);
        }
    }

  	// If count is greater than n / 2, return
  	// the candidate; otherwise, return -1
    trace_line(34);
    if (count > n / 2) {
        trace_line(35);
        return candidate;
    } else {
        trace_line(37);
        return -1;
    }
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
    trace_line(43);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(44);
    printf("%d\n", majorityElement(arr, n));
    trace_line(45);
    return 0;
}
