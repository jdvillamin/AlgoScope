/* Source: https://www.geeksforgeeks.org/dsa/longest-subarray-sum-divisible-k/ */
#include <stdio.h>
int longestSubarrayDivK(int arr[], int n, int k) {
    int res = 0;
    for (int i = 0; i < n; i++) {
      
        // Initialize sum for the current subarray
        int sum = 0;
        for (int j = i; j < n; j++) {
          
            // Add the current element to the subarray sum
            sum = (sum + arr[j]) % k;

            // Update max length if sum is divisible by k
            if (sum == 0)
                res = (res > (j - i + 1)) ? res : (j - i + 1);
        }
    }
    return res;
}

int main() {
    int arr[] = {2, 7, 6, 1, 4, 5};
    int k = 3;
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", longestSubarrayDivK(arr, n, k));
    return 0;
}
