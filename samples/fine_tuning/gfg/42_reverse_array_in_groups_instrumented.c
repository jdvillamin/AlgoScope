/* Source: https://www.geeksforgeeks.org/dsa/reverse-an-array-in-groups-of-given-size/ */
#include <stdio.h>

#include "tracer.h"

void reverseInGroups(int arr[], int n, int k){
    trace_var_init("n", n);
    trace_var_init("k", k);
    
    trace_line(6);
    for (int i = 0; i < n; i += k) {
        trace_line(6);
        trace_var_init("i", i);
    
        trace_line(8);
        int left = i;
        trace_var_init("left", left);
        trace_array_cell("arr", "left", left);
        trace_line(9);
        int right;
    
        // to handle case when k is not multiple of n
        trace_line(12);
        if(i+k-1<n-1)
        {
            trace_line(13);
            right = i+k-1;
            trace_var_init("right", right);
            trace_array_cell("arr", "right", right);
        }
        else
        {
            trace_line(15);
            right = n-1;
            trace_var_init("right", right);
            trace_array_cell("arr", "right", right);
        }

        // reverse the sub-array [left, right]
        trace_line(18);
        while (left < right) {
            trace_line(18);
            
            // swap
            trace_line(21);
            trace_array_highlight("arr", left);
            trace_array_highlight("arr", right);
            int temp = arr[left];
            trace_line(22);
            arr[left] = arr[right];
            trace_array("arr", left, arr[left]);
            trace_line(23);
            arr[right] = temp;
            trace_array("arr", right, arr[right]);
            trace_line(24);
            left++;
            trace_var("left", left);
            trace_array_cell("arr", "left", left);
            trace_line(25);
            right--;
            trace_var("right", right);
            trace_array_cell("arr", "right", right);
        }

    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    trace_array_init("arr", 8);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_array("arr", 6, arr[6]);
    trace_array("arr", 7, arr[7]);
    trace_line(33);
    int k = 3;
    trace_var_init("k", k);

    trace_line(35);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);

    trace_line(37);
    reverseInGroups(arr, n, k);

    trace_line(39);
    for (int i = 0; i < n; i++)
    {
        trace_line(39);
        trace_var_init("i", i);
        trace_line(40);
        printf("%d ",arr[i]);
    }

    trace_line(42);
    return 0;
}
