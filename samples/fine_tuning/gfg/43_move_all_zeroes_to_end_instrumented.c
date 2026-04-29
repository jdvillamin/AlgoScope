/* Source: https://www.geeksforgeeks.org/dsa/move-zeroes-end-array/ */
#include <stdio.h>

#include "tracer.h"

void pushZerosToEnd(int arr[], int n) {
    trace_var_init("n", n);
  
    // Pointer to track the position 
    // for next non-zero element
    trace_line(8);
    int count = 0;
    trace_var_init("count", count);
    trace_array_cell("arr", "count", count);
     
    trace_line(10);
    for (int i = 0; i < n; i++) {
        trace_line(10);
        trace_var_init("i", i);
        trace_array_cell("arr", "i", i);

        // If the current element is non-zero
        trace_line(13);
        trace_array_highlight("arr", i);
        if (arr[i] != 0) {
          
            // Swap the current element with 
            // the 0 at index 'count'
            trace_line(17);
            int temp = arr[i];
            trace_line(18);
            arr[i] = arr[count];
            trace_array("arr", i, arr[i]);
            trace_line(19);
            arr[count] = temp;
            trace_array("arr", count, arr[count]);
          
            // Move 'count' pointer to 
            // the next position
            trace_line(23);
            count++;
            trace_var("count", count);
            trace_array_cell("arr", "count", count);
        }
    }
}

int main() {
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
    int size = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("size", size);
    
    trace_line(32);
    pushZerosToEnd(arr, size);
    
    trace_line(34);
    for (int i = 0; i < size; i++) {
        trace_line(34);
        trace_var_init("i", i);
        trace_line(35);
        printf("%d ", arr[i]);
    }
    
    trace_line(38);
    return 0;
}
