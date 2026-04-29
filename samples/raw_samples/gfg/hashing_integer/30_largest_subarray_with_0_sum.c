/* Source: https://www.geeksforgeeks.org/dsa/find-the-largest-subarray-with-0-sum/ */
#include <stdio.h>

int maxLength(int arr[], int n) {
    int maxLen = 0;

    // Loop through each starting point
    for (int i = 0; i < n; i++) {
        int currSum = 0;

        // Try all subarrays starting from 'i'
        for (int j = i; j < n; j++) {
            currSum += arr[j];

            // If currSum becomes 0, update maxLen if required
            if (currSum == 0) {
                int length = j - i + 1;
                if (length > maxLen)
                    maxLen = length;
            }
        }
    }

    return maxLen;
}

int main() {
    int arr[] = {15, -2, 2, -8, 1, 7, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", maxLength(arr, size));
    return 0;
}
