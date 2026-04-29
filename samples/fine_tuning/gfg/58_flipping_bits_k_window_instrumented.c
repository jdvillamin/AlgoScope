/* Source: https://www.geeksforgeeks.org/dsa/flipping-bits-with-k-window/ */
#include <stdio.h>

#include "tracer.h"

int kBitFlips(int arr[], int n, int k) {
    trace_var_init("n", n);
    trace_var_init("k", k);
    trace_line(5);
    int res = 0, flag = 0;
    trace_var_init("res", res);
    trace_var_init("flag", flag);
    trace_line(6);
    int flipped[n + 1];
    trace_array_init("flipped", n + 1);
    trace_line(7);
    for (int i = 0; i < n + 1; i++) 
    {
        trace_line(7);
        trace_var_init("i", i);
        trace_line(8);
        flipped[i] = 0;
        trace_array("flipped", i, flipped[i]);
    }

    trace_line(10);
    for (int i = 0; i < n; i++) {
        trace_line(10);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        
        // Check if flag should be flipped at index i
        trace_line(13);
        trace_array_highlight("flipped", i);
        flag = (flag ^ flipped[i]);
        trace_var("flag", flag);
        
        // If flag = 1, then flip the current index
        trace_line(16);
        if (flag == 1)
        {
            trace_line(17);
            arr[i] ^= 1;
            trace_array("arr", i, arr[i]);
        }
        
        // Finally, if arr[i] = 0, then we need to flip
        trace_line(20);
        if (arr[i] == 0) {
            
            // Check if k elements are left
            trace_line(23);
            if (i + k > n) 
            {
                trace_line(24);
                return -1;
            }
            
            trace_line(26);
            res += 1;
            trace_var("res", res);
            
            // Flip flag so that upcoming elements are also flipped
            trace_line(29);
            flag ^= 1;
            trace_var("flag", flag);
            
            // Mark index (i + k) where flag will be flipped again
            trace_line(32);
            flipped[i + k] = 1;
            trace_array("flipped", i + k, flipped[i + k]);
        }
    }

    trace_line(36);
    return res; 
}

int main() {
    int arr[] = {1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1};
    trace_array_init("arr", 11);
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
    trace_array("arr", 10, arr[10]);
    trace_line(41);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(42);
    int k = 2;
    trace_var_init("k", k);
    trace_line(43);
    printf("%d", kBitFlips(arr, n, k));
    trace_line(44);
    return 0;
}
