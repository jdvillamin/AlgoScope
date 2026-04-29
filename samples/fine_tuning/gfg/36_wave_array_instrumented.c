/* Source: https://www.geeksforgeeks.org/dsa/sort-array-wave-form-2/ */
#include<stdio.h>
#include<stdlib.h>

#include "tracer.h"

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sortInWave(int arr[], int n){
    trace_var_init("n", n);
    // swap adjacent elements
    trace_line(13);
    for (int i=0; i<n-1; i += 2)
    {
        trace_line(13);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        trace_array_highlight("arr", i + 1);
        trace_line(14);
        swap(&arr[i], &arr[i+1]);
        trace_array("arr", i, arr[i]);
        trace_array("arr", i + 1, arr[i + 1]);
    }
}

int main(){

    int arr[] = {1, 2, 3, 4, 5};
    trace_array_init("arr", 5);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_line(20);
    int n = sizeof(arr)/sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(21);
    sortInWave(arr, n);
    trace_line(22);
    for (int i=0; i<n; i++)
    {
        trace_line(22);
        trace_var_init("i", i);
        trace_line(23);
       printf("%d ",arr[i]);
    }
    trace_line(24);
    return 0;
}
