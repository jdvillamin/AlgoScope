/* Source: https://www.geeksforgeeks.org/dsa/count-pairs-with-given-sum/ */
#include <stdio.h>

#include "tracer.h"

int countPairs(int arr[], int n, int target) {
    trace_var_init("n", n);
    trace_var_init("target", target);
    trace_line(5);
    int cnt = 0;
    trace_var_init("cnt", cnt);

    // Iterate through each element in the array
    trace_line(8);
    for (int i = 0; i < n; i++) {
        trace_line(8);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
      
        // For each element arr[i], check every
        // other element arr[j] that comes after it
        trace_line(12);
        for (int j = i + 1; j < n; j++) {
            trace_line(12);
            trace_var_init("j", j);
            trace_array_highlight("arr", j);
          
            // Check if the sum of the current pair
            // equals the target
            trace_line(16);
            if (arr[i] + arr[j] == target) {
                trace_line(17);
                cnt++;
                trace_var("cnt", cnt);
            }
        }
    }
    trace_line(21);
    return cnt;
}

int main() {
    int arr[] = {1, 5, 7, -1, 5};
    trace_array_init("arr", 5);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_line(25);
    int target = 6;
    trace_var_init("target", target);
    trace_line(26);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(27);
    printf("%d\n", countPairs(arr, n, target));
    trace_line(28);
    return 0;
}
