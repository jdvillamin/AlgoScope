/* Source: https://www.geeksforgeeks.org/dsa/subset-sum-problem-dp-25/ */
//C implementation for subset sum
// problem using recursion
#include <stdio.h>

// Function to check if there is a subset
// with the given sum using recursion
int isSubsetSumRec(int arr[], int n, int sum) {
  
    // Base Cases
    if (sum == 0) {
        return 1;
    }
    if (n == 0) {
        return 0;
    }

    // If last element is greater than sum, ignore it
    if (arr[n - 1] > sum) {
        return isSubsetSumRec(arr, n - 1, sum);
    }

    // Check if sum can be obtained by including
    // or excluding the last element
    return isSubsetSumRec(arr, n - 1, sum) || 
           isSubsetSumRec(arr, n - 1, sum - arr[n - 1]);
}

int isSubsetSum(int arr[], int n, int sum) {
    return isSubsetSumRec(arr, n, sum);
}

int main() {
    int arr[] = {3, 34, 4, 12, 5, 2};
    int sum = 9;
    int n = sizeof(arr) / sizeof(arr[0]);

    if (isSubsetSum(arr, n, sum)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}
