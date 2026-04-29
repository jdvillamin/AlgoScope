/* Source: https://www.geeksforgeeks.org/dsa/program-to-reverse-an-array/ */
#include <stdio.h>

// Function to swap two numbers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// function to reverse an array
void reverseArray(int arr[], int n) {
    
    // Initialize left to the beginning 
    // and right to the end
    int left = 0, right = n - 1;

    // Iterate till left is less than right
    while (left < right) {
        
        // Swap the elements at left 
        // and right position
        swap(&arr[left], &arr[right]);

        // Increment the left pointer
        left++;

        // Decrement the right pointer
        right--;
    }
}

int main() {
    int arr[] = { 1, 4, 3, 2, 6, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);

    reverseArray(arr, n);
  
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]);
    
    return 0;
}
