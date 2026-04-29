/* Source: https://www.geeksforgeeks.org/dsa/array-rotation/ */
// C Program to left rotate the array by d positions
// using temporary array

#include <stdio.h>
#include <stdlib.h>

// Function to rotate array
void rotateArr(int* arr, int d, int n) {
    
    // Handle case when d > n
    d %= n;
  
    // Storing rotated version of array
    int temp[n];

    // Copy last n - d elements to the front of temp
    for (int i = 0; i < n - d; i++)
        temp[i] = arr[d + i];

    // Copy the first d elements to the back of temp
    for (int i = 0; i < d; i++)
        temp[n - d + i] = arr[i];

    // Copying the elements of temp in arr
    // to get the final rotated array
    for (int i = 0; i < n; i++)
        arr[i] = temp[i];
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int d = 2;

    rotateArr(arr, d, n);

    // Print the rotated array
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
