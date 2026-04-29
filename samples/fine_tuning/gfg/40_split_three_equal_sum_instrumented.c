/* Source: https://www.geeksforgeeks.org/dsa/split-array-three-equal-sum-subarrays/ */
// C program to find if the array can be divided into
// three segments by finding all possible partitions

#include <stdio.h>

#include "tracer.h"

// function to find the sum of subarray arr[start...end]
int findSum(int *arr, int start, int end) {
    trace_var_init("start", start);
    trace_var_init("end", end);
    trace_line(9);
    int sum = 0;
    trace_var_init("sum", sum);
    trace_line(10);
    for(int i = start; i <= end; i++)
    {
        trace_line(10);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        trace_line(11);
        sum += arr[i];
        trace_var("sum", sum);
    }
    trace_line(12);
    return sum;
}

// function to return the index pair of equal sum segments
int* findSplit(int *arr, int n) {
    trace_var_init("n", n);
    trace_line(17);
    int *res = (int *)malloc(2 * sizeof(int));
    trace_line(18);
    res[0] = -1;
    trace_line(19);
    res[1] = -1;

    // First partition
    trace_line(22);
    for(int i = 0; i < n - 2; i++) {
        trace_line(22);
        trace_var_init("i", i);
        trace_array_cell("arr", "i", i);

        // Second Partition
        trace_line(25);
        for(int j = i + 1; j < n - 1; j++) {
            trace_line(25);
            trace_var_init("j", j);
            trace_array_cell("arr", "j", j);

            // Find sum of all three segments
            trace_line(28);
            int sum1 = findSum(arr, 0, i);
            trace_var_init("sum1", sum1);
            trace_line(29);
            int sum2 = findSum(arr, i + 1, j);
            trace_var_init("sum2", sum2);
            trace_line(30);
            int sum3 = findSum(arr, j + 1, n - 1);
            trace_var_init("sum3", sum3);

            // If all three segments have equal sum,
            // then return true
            trace_line(34);
            if(sum1 == sum2 && sum2 == sum3) {
                trace_line(35);
                res[0] = i;
                trace_line(36);
                res[1] = j;
                trace_line(37);
                return res;
            }
        }
    }

    // No possible index pair found
    trace_line(43);
    return res;
}

int main() {
    int arr[] = {1, 3, 4, 0, 4};
    trace_array_init("arr", 5);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_line(48);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(49);
    int *res = findSplit(arr, n);

    trace_line(51);
    printf("%d %d", res[0], res[1]);

    trace_line(53);
    return 0;
}
