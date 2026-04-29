/* Source: https://www.geeksforgeeks.org/dsa/a-product-array-puzzle/ */
#include <stdio.h>

void productExceptSelf(int arr[], int n, int res[]) {
  
    // Initialize result array as 1
    for (int i = 0; i < n; i++) {
        res[i] = 1;
    }

    for (int i = 0; i < n; i++) {
      
      	// Compute product of all elements except arr[i]
        for (int j = 0; j < n; j++) {
            if (i != j) {
                res[i] *= arr[j];
            }
        }
    }
}

int main() {
    int arr[] = {10, 3, 5, 6, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int res[n];
    
    productExceptSelf(arr, n, res);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", res[i]);
    }
    
    return 0;
}
