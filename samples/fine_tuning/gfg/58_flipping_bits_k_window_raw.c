/* Source: https://www.geeksforgeeks.org/dsa/flipping-bits-with-k-window/ */
#include <stdio.h>

int kBitFlips(int arr[], int n, int k) {
    int res = 0, flag = 0;
    int flipped[n + 1];
    for (int i = 0; i < n + 1; i++) 
        flipped[i] = 0;

    for (int i = 0; i < n; i++) {
        
        // Check if flag should be flipped at index i
        flag = (flag ^ flipped[i]);
        
        // If flag = 1, then flip the current index
        if (flag == 1)
            arr[i] ^= 1;
        
        // Finally, if arr[i] = 0, then we need to flip
        if (arr[i] == 0) {
            
            // Check if k elements are left
            if (i + k > n) 
                return -1;
            
            res += 1;
            
            // Flip flag so that upcoming elements are also flipped
            flag ^= 1;
            
            // Mark index (i + k) where flag will be flipped again
            flipped[i + k] = 1;
        }
    }

    return res; 
}

int main() {
    int arr[] = {1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    printf("%d", kBitFlips(arr, n, k));
    return 0;
}
