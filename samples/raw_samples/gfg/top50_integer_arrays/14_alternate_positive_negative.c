/* Source: https://www.geeksforgeeks.org/dsa/rearrange-array-alternating-positive-negative-items-o1-extra-space/ */
// C program to rearrange positive and negative numbers 
// alternately using Two pointers 

#include <stdio.h>

// Function to rearrange positive and negative numbers
// in alternate fashion
void rearrange(int arr[], int n) {
    int pos[n];
    int neg[n];
    int posCount = 0, negCount = 0;

    // Separate positive and negative numbers
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0)
            pos[posCount++] = arr[i];
        else
            neg[negCount++] = arr[i];
    }

    int posIdx = 0, negIdx = 0;
    int i = 0;

    // Place positive and negative numbers alternately
    // in the original array
    while (posIdx < posCount && negIdx < negCount) {
        if (i % 2 == 0)
            arr[i++] = pos[posIdx++];
        else 
            arr[i++] = neg[negIdx++];
    }

    // Append remaining positive numbers (if any)
    while (posIdx < posCount)
        arr[i++] = pos[posIdx++];

    // Append remaining negative numbers (if any)
    while (negIdx < negCount)
        arr[i++] = neg[negIdx++];
}

int main() {
    int arr[] = {1, 2, 3, -4, -1, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    rearrange(arr, n);
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]);
    
    return 0;
}
