/* Source: https://www.geeksforgeeks.org/dsa/equilibrium-index-of-an-array/ */
#include <stdio.h>

int findEquilibrium(int arr[], int n) {
  
    // Check for indexes one by one until
    // an equilibrium index is found 
    for (int i = 0; i < n; ++i) {
        
        // Get left sum
        int leftSum = 0;
        for (int j = 0; j < i; j++)
            leftSum += arr[j];

        // Get right sum
        int rightSum = 0;
        for (int j = i + 1; j < n; j++)
            rightSum += arr[j];

       // Check the condition
        if (leftSum == rightSum)
            return i;
    }
    
    return -1;
}

int main() {
    int arr[] = {-7, 1, 5, 2, -4, 3, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d", findEquilibrium(arr, n));
    return 0;
}
