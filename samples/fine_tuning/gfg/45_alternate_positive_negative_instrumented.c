/* Source: https://www.geeksforgeeks.org/dsa/rearrange-array-alternating-positive-negative-items-o1-extra-space/ */
// C program to rearrange positive and negative numbers 
// alternately using Two pointers 

#include <stdio.h>

#include "tracer.h"

// Function to rearrange positive and negative numbers
// in alternate fashion
void rearrange(int arr[], int n) {
    trace_var_init("n", n);
    trace_line(10);
    int pos[n];
    trace_array_init("pos", n);
    trace_line(11);
    int neg[n];
    trace_array_init("neg", n);
    trace_line(12);
    int posCount = 0, negCount = 0;
    trace_var_init("posCount", posCount);
    trace_var_init("negCount", negCount);

    // Separate positive and negative numbers
    trace_line(15);
    for (int i = 0; i < n; i++) {
        trace_line(15);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        trace_line(16);
        if (arr[i] >= 0)
        {
            trace_line(17);
            pos[posCount++] = arr[i];
            trace_array("pos", posCount - 1, pos[posCount - 1]);
            trace_var("posCount", posCount);
        }
        else
        {
            trace_line(19);
            neg[negCount++] = arr[i];
            trace_array("neg", negCount - 1, neg[negCount - 1]);
            trace_var("negCount", negCount);
        }
    }

    trace_line(22);
    int posIdx = 0, negIdx = 0;
    trace_var_init("posIdx", posIdx);
    trace_var_init("negIdx", negIdx);
    trace_line(23);
    int i = 0;
    trace_var_init("i", i);

    // Place positive and negative numbers alternately
    // in the original array
    trace_line(27);
    while (posIdx < posCount && negIdx < negCount) {
        trace_line(27);
        trace_line(28);
        if (i % 2 == 0)
        {
            trace_line(29);
            arr[i++] = pos[posIdx++];
            trace_array("arr", i - 1, arr[i - 1]);
            trace_var("i", i);
            trace_var("posIdx", posIdx);
        }
        else 
        {
            trace_line(31);
            arr[i++] = neg[negIdx++];
            trace_array("arr", i - 1, arr[i - 1]);
            trace_var("i", i);
            trace_var("negIdx", negIdx);
        }
    }

    // Append remaining positive numbers (if any)
    trace_line(35);
    while (posIdx < posCount)
    {
        trace_line(35);
        trace_line(36);
        arr[i++] = pos[posIdx++];
        trace_array("arr", i - 1, arr[i - 1]);
        trace_var("i", i);
        trace_var("posIdx", posIdx);
    }

    // Append remaining negative numbers (if any)
    trace_line(39);
    while (negIdx < negCount)
    {
        trace_line(39);
        trace_line(40);
        arr[i++] = neg[negIdx++];
        trace_array("arr", i - 1, arr[i - 1]);
        trace_var("i", i);
        trace_var("negIdx", negIdx);
    }
}

int main() {
    int arr[] = {1, 2, 3, -4, -1, 4};
    trace_array_init("arr", 6);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_line(45);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    
    trace_line(47);
    rearrange(arr, n);
    trace_line(48);
    for (int i = 0; i < n; i++) 
    {
        trace_line(48);
        trace_var_init("i", i);
        trace_line(49);
        printf("%d ", arr[i]);
    }
    
    trace_line(51);
    return 0;
}
