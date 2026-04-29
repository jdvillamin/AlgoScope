/* Source: https://www.geeksforgeeks.org/dsa/maximum-contiguous-circular-sum/ */
#include <stdio.h>

int maxCircularSum(int arr[], int n) {
    int suffixSum = arr[n - 1];

    // maxSuffix array to store the value of 
    // maximum suffix occurred so far.
    int* maxSuffix = (int*)malloc((n + 1) * sizeof(int));
    maxSuffix[n - 1] = arr[n - 1];

    for(int i = n - 2; i >= 0; i--) {
        suffixSum = suffixSum + arr[i];
        if(maxSuffix[i + 1] > suffixSum)
        	maxSuffix[i] = maxSuffix[i + 1];
        else 
            maxSuffix[i] = suffixSum;
    }

    // circularSum is Maximum sum of circular subarray
    int circularSum = arr[0];

    // normalSum is Maximum sum subarray considering 
    // the array is non-circular
    int normalSum = arr[0];

    int currSum = 0;
    int prefix = 0;

    for(int i = 0; i < n; i++) {
        
        // Kadane's Algorithm
        currSum = (currSum + arr[i] > arr[i]) ? currSum + arr[i] : arr[i];
        normalSum = (normalSum > currSum) ? normalSum : currSum;
      
		// Calculating Maximum Circular Sum
        prefix = prefix + arr[i];
        if(circularSum < prefix + maxSuffix[i + 1])
          	circularSum = prefix + maxSuffix[i + 1];
    }

    return (circularSum > normalSum) ? circularSum : normalSum;
}

int main() {
    int arr[] = {8, -8, 9, -9, 10, -11, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", maxCircularSum(arr, n));
    return 0;
}
