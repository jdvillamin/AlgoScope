/* Source: https://www.geeksforgeeks.org/find-the-smallest-positive-number-missing-from-an-unsorted-array-set-3/ */
// C program to find the smallest positive missing number 
// by marking indices

#include <stdio.h>

// Function for finding the first missing positive number
int missingNumber(int arr[], int n) {
    int flag = 0;

    // Check if 1 is present in array or not
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            flag = 1;
            break;
        }
    }

    // If 1 is not present
    if (flag == 0)
        return 1;

    // Change out of range values to 1
    for (int i = 0; i < n; i++) {
        if (arr[i] <= 0 || arr[i] > n)
            arr[i] = 1;
    }

    // Mark the occurrence of numbers 
    // directly within the same array
    for (int i = 0; i < n; i++) {
        arr[(arr[i] - 1) % n] += n;
    }

    // Finding which index has value less than n
    for (int i = 0; i < n; i++) {
        if (arr[i] <= n)
            return i + 1;
    }

    // If array has values from 1 to n
    return n + 1;
}

int main() {
    int arr[] = {2, -3, 4, 1, 1, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
  
    printf("%d", missingNumber(arr, n));
    return 0;
}
