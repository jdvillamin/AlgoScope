/* Source: https://www.geeksforgeeks.org/dsa/find-second-largest-element-array/ */
// C program to find second largest element in an array using Sorting

#include <stdio.h>

// function to compare two integers for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// function to find the second largest element
int getSecondLargest(int arr[], int n) {
    
    // Sort the array in non-decreasing order
    qsort(arr, n, sizeof(int), compare);
  
    // start from second last element as last element is the largest
    for (int i = n - 2; i >= 0; i--) {
        
        // return the first element which is not equal to the 
        // largest element
        if (arr[i] != arr[n - 1]) {
            return arr[i];
        }
    }
  
    // If no second largest element was found, return -1
    return -1;
}

int main() {
    int arr[] = { 12, 35, 1, 10, 34, 1 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", getSecondLargest(arr, n));
    return 0;
}
