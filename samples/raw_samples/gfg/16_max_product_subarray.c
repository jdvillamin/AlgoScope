/* Source: https://www.geeksforgeeks.org/dsa/maximum-product-subarray/ */
#include <stdio.h>

int maxProduct(int arr[], int n) {
    
    // Initializing result
    int maxProd = arr[0];

    for (int i = 0; i < n; i++) {
        int mul = 1;
      
        // traversing in current subarray
        for (int j = i; j < n; j++) {
          	mul *= arr[j];
          
            // updating result every time
            // to keep track of the maximum product
            maxProd = (maxProd > mul) ? maxProd : mul;
        }
    }
    return maxProd;
}

int main() {
    
    int arr[] = { -2, 6, -3, -10, 0, 2 };
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("%lld\n", maxProduct(arr, n));
    
    return 0;
}
