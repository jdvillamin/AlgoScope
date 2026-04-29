/* Source: https://www.geeksforgeeks.org/dsa/leaders-in-an-array/ */
#include <stdio.h>
#include <stdlib.h>

// Function to find the leaders in an array
int* leaders(int arr[], int n, int* resSize) {
    int* result = (int*)malloc(n * sizeof(int));
    int count = 0;

    // Start with the rightmost element
    int maxRight = arr[n - 1];

    // Rightmost element is always a leader
    result[count++] = maxRight;

    // Traverse the array from right to left
    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] >= maxRight) {
            maxRight = arr[i];
            result[count++] = maxRight;
        }
    }

    // Reverse the result array
    for (int i = 0; i < count / 2; i++) {
        int temp = result[i];
        result[i] = result[count - i - 1];
        result[count - i - 1] = temp;
    }

    *resSize = count;
    return result;
}

int main() {
    int arr[] = { 16, 17, 4, 3, 5, 2 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int resSize;

    int* result = leaders(arr, n, &resSize);
    for (int i = 0; i < resSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}
