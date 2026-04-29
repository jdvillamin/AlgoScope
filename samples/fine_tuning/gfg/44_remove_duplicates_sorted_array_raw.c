/* Source: https://www.geeksforgeeks.org/dsa/remove-duplicates-sorted-array/ */
#include <stdio.h>

int removeDuplicates(int arr[], int n) {
    if (n <= 1)
        return n;
	
  	// Start from the second element
    int idx = 1;
  
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[i - 1]) {
            arr[idx++] = arr[i];
        }
    }
    return idx;
}

int main() {
    int arr[] = {1, 2, 2, 3, 4, 4, 4, 5, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int newSize = removeDuplicates(arr, n);
    
    for (int i = 0; i < newSize; i++) 
        printf("%d ", arr[i]);

    return 0;
}
