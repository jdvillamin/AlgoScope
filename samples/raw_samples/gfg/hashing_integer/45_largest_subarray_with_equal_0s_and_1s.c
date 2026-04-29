/* Source: https://www.geeksforgeeks.org/dsa/largest-subarray-with-equal-number-of-0s-and-1s/ */
// C program to find the longest subarray with 
// equal number of 0s and 1s using nested loop

#include <stdio.h>

int maxLen(int arr[], int n) {
    int res = 0;

    // Pick a starting point as 's'
    for (int s = 0; s < n; s++) {
        int sum = 0;

        // Consider all subarrays arr[s...e]
        for (int e = s; e < n; e++) {
            sum += (arr[e] == 0) ? -1 : 1;

            // Check if it's a 0-sum subarray
            if (sum == 0)
                // Update max size
                res = (res > e - s + 1) ? res : (e - s + 1);
        }
    }

    return res;
}

int main() {
    int arr[] = {1, 0, 0, 1, 0, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d", maxLen(arr, n));
    return 0;
}
