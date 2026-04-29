/* Source: https://www.geeksforgeeks.org/dsa/maximum-distance-two-occurrences-element-array/ */
// C Program to find max distance between two occurrences
// in array by exploring all pairs

#include <stdio.h>
#include <stdlib.h>

#include "tracer.h"

// function to find the maximum distance
int maxDistance(int arr[], int n) {
    trace_var_init("n", n);
    trace_line(10);
    int res = 0;
    trace_var_init("res", res);
    trace_line(11);
    for (int i = 0; i < n - 1; i++) {
        trace_line(11);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        trace_line(12);
        for (int j = i + 1; j < n; j++) {
            trace_line(12);
            trace_var_init("j", j);
            trace_array_highlight("arr", j);
          
            // check if two elements are equal
            trace_line(15);
            if (arr[i] == arr[j]) {
          
              // calculate the distance and update res
                trace_line(18);
                res = (res > (j - i)) ? res : (j - i);
                trace_var("res", res);
            }
        }
    }
    trace_line(22);
    return res;
}

int main() {
    int arr[] = {1, 2, 4, 1, 3, 4, 2, 5, 6, 5};
    trace_array_init("arr", 10);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_array("arr", 6, arr[6]);
    trace_array("arr", 7, arr[7]);
    trace_array("arr", 8, arr[8]);
    trace_array("arr", 9, arr[9]);
    trace_line(27);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(28);
    printf("%d\n", maxDistance(arr, n));
    trace_line(29);
    return 0;
}
