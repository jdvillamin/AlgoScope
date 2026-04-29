/* Source: https://www.geeksforgeeks.org/dsa/find-the-smallest-positive-number-missing-from-an-unsorted-array/ */
#include <stdio.h>

int partition(int *arr, int n) {
    int pivotIdx = 0;

    for (int i = 0; i < n; i++) {
        
        // Move positive elements to the left
        if (arr[i] > 0) {
            int temp = arr[i];
            arr[i] = arr[pivotIdx];
            arr[pivotIdx] = temp;
            pivotIdx++;
        }
    }

    // return index of the first non-positive number
    return pivotIdx;
}

int missingNumber(int *arr, int n) {
    int k = partition(arr, n);

    // Traverse the positive part of the array
    for (int i = 0; i < k; i++) {
        
        // Find the absolute value to get the original number
        int val = abs(arr[i]);

        // If val is within range, then mark the element at
        // index val-1 to negative
        if (val - 1 < k && arr[val - 1] > 0) {
            arr[val - 1] = -arr[val - 1];
        }
    }

    // Find first unmarked index
    for (int i = 0; i < k; i++) {
        if (arr[i] > 0) {
            return i + 1;
        }
    }

    // If all numbers from 1 to k are marked then
    // missing number is k + 1
    return k + 1;
}

int main() {
 
    int arr[] = {2, -3, 4, 1, 1, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", missingNumber(arr, n));
    return 0;
}
