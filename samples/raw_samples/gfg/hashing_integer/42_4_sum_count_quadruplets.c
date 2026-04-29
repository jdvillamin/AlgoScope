/* Source: https://www.geeksforgeeks.org/dsa/count-quadruplets-with-sum-k-from-given-array/ */
#include <stdio.h>

// Function to return the number of quadruplets with the given target sum
int countSum(int arr[], int n, int target) {
    int count = 0;

    // Loop over all possible quadruplets
    for (int i = 0; i < n - 3; i++) {
        for (int j = i + 1; j < n - 2; j++) {
            for (int k = j + 1; k < n - 1; k++) {
                for (int l = k + 1; l < n; l++) {
                    if (arr[i] + arr[j] + arr[k] + arr[l] == target) {
                        count++;
                    }
                }
            }
        }
    }

    return count;
}

// Driver Code
int main() {
    int arr[] = {1, 1, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 4;
    printf("%d\n", countSum(arr, n, target));
    return 0;
}
