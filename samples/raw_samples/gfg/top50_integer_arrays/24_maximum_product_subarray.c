/* Source: https://www.geeksforgeeks.org/dsa/maximum-product-subarray/ */
#include <stdio.h>
#include <limits.h>

int max(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

int min(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

int maxProduct(int arr[], int n) {
    
    // max product ending at the current index
    int currMax = arr[0];

    // min product ending at the current index
    int currMin = arr[0];

    // Initialize overall max product
    int maxProd = arr[0];

    // Iterate through the array
    for (int i = 1; i < n; i++) {
        
        // Temporary variable to store the maximum product ending at the
        // current index
        int temp = max(arr[i], arr[i] * currMax, arr[i] * currMin);
        
        // Update the minimum product ending at the current index
        currMin = min(arr[i], arr[i] * currMax, arr[i] * currMin);
      
        // Update the maximum product ending at the current index
        currMax = temp;
      
        // Update the overall maximum product
        maxProd = max(maxProd, currMax, maxProd);
    }
    return maxProd;
}

int main() {
    int arr[] = { -2, 6, -3, -10, 0, 2 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%lld\n", maxProduct(arr, n));
    return 0;
}
