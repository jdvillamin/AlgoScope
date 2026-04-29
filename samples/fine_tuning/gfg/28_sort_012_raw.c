/* Source: https://www.geeksforgeeks.org/dsa/sort-an-array-of-0s-1s-and-2s/ */
#include <stdio.h>

// Function to sort array containing 0s, 1s, and 2s
void sort012(int arr[], int n) {
    
    // initialize three pointers:
    // lo: boundary for 0s
    // mid: current element being checked
    // hi: boundary for 2s
    int lo = 0;
    int hi = n - 1;
    int mid = 0;

    // process elements until mid crosses hi
    while (mid <= hi) {
        if (arr[mid] == 0) {
            
            // current is 0: swap with lo and move both 
            // pointers forward
            int temp = arr[lo];
            arr[lo++] = arr[mid];
            arr[mid++] = temp;
        }
        else if (arr[mid] == 1) {
            // current is 1: it's already in correct position
            mid++;
        }
        else {
            // current is 2: swap with hi and move hi backward
            // do not increment mid, as swapped value needs
            // to be re-checked
            int temp = arr[mid];
            arr[mid] = arr[hi];
            arr[hi--] = temp;
        }
    }
}

int main() {
    int arr[] = {0, 1, 2, 0, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    // sort the array in-place
    sort012(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
