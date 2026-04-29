/* Source: https://www.geeksforgeeks.org/dsa/program-to-reverse-an-array/ */
#include <stdio.h>

#include "tracer.h"

// Function to swap two numbers
void swap(int *a, int *b) {
    trace_line(6);
    int temp = *a;
    trace_line(7);
    *a = *b;
    trace_line(8);
    *b = temp;
}

// function to reverse an array
void reverseArray(int arr[], int n) {
    trace_var_init("n", n);
    
    // Initialize left to the beginning 
    // and right to the end
    trace_line(16);
    int left = 0, right = n - 1;
    trace_var_init("left", left);
    trace_array_cell("arr", "left", left);
    trace_var_init("right", right);
    trace_array_cell("arr", "right", right);

    // Iterate till left is less than right
    trace_line(19);
    while (left < right) {
        trace_line(19);
        
        // Swap the elements at left 
        // and right position
        trace_line(23);
        trace_array_highlight("arr", left);
        trace_array_highlight("arr", right);
        swap(&arr[left], &arr[right]);
        trace_array("arr", left, arr[left]);
        trace_array("arr", right, arr[right]);

        // Increment the left pointer
        trace_line(26);
        left++;
        trace_var("left", left);
        trace_array_cell("arr", "left", left);

        // Decrement the right pointer
        trace_line(29);
        right--;
        trace_var("right", right);
        trace_array_cell("arr", "right", right);
    }
}

int main() {
    int arr[] = { 1, 4, 3, 2, 6, 5 };
    trace_array_init("arr", 6);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_line(35);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);

    trace_line(37);
    reverseArray(arr, n);
  
    trace_line(39);
    for (int i = 0; i < n; i++) 
    {
        trace_line(39);
        trace_var_init("i", i);
        trace_line(40);
        printf("%d ", arr[i]);
    }
    
    trace_line(42);
    return 0;
}
