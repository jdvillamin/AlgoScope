/* Source: https://www.geeksforgeeks.org/dsa/subset-sum-problem-dp-25/ */
//C implementation for subset sum
// problem using recursion
#include <stdio.h>

#include "tracer.h"

// Function to check if there is a subset
// with the given sum using recursion
int isSubsetSumRec(int arr[], int n, int sum) {
    trace_var_init("n", n);
    trace_var_init("sum", sum);
  
    // Base Cases
    trace_line(11);
    if (sum == 0) {
        trace_line(12);
        return 1;
    }
    trace_line(14);
    if (n == 0) {
        trace_line(15);
        return 0;
    }

    // If last element is greater than sum, ignore it
    trace_line(19);
    trace_array_highlight("arr", n - 1);
    if (arr[n - 1] > sum) {
        trace_line(20);
        return isSubsetSumRec(arr, n - 1, sum);
    }

    // Check if sum can be obtained by including
    // or excluding the last element
    trace_line(25);
    return isSubsetSumRec(arr, n - 1, sum) || 
           isSubsetSumRec(arr, n - 1, sum - arr[n - 1]);
}

int isSubsetSum(int arr[], int n, int sum) {
    trace_var_init("n", n);
    trace_var_init("sum", sum);
    trace_line(30);
    return isSubsetSumRec(arr, n, sum);
}

int main() {
    int arr[] = {3, 34, 4, 12, 5, 2};
    trace_array_init("arr", 6);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_line(35);
    int sum = 9;
    trace_var_init("sum", sum);
    trace_line(36);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);

    trace_line(38);
    if (isSubsetSum(arr, n, sum)) {
        trace_line(39);
        printf("True\n");
    } else {
        trace_line(41);
        printf("False\n");
    }

    trace_line(44);
    return 0;
}
