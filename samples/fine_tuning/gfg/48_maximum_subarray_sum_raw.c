/* Source: https://www.geeksforgeeks.org/dsa/largest-sum-contiguous-subarray/ */
#include <stdio.h>
#include <limits.h>

int maxSubarraySum(int arr[], int size) {
    
    // Stores the result (maximum sum found so far)
    int res = arr[0];
    
    // Maximum sum of subarray ending at current position
    int maxEnding = arr[0];

    for (int i = 1; i < size; i++) {
        
        // Either extend the previous subarray or start 
        // new from current element
        maxEnding = (maxEnding + arr[i] > arr[i]) ? 
          									maxEnding + arr[i] : arr[i];
      
        // Update result if the new subarray sum is larger
        res = (res > maxEnding) ? res : maxEnding;
    }
    return res;
}

int main() {
    int arr[] = {2, 3, -8, 7, -1, 2, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%lld\n", maxSubarraySum(arr, size));
    return 0;
}
