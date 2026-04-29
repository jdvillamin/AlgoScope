/* Source: https://www.geeksforgeeks.org/dsa/split-array-three-equal-sum-subarrays/ */
// C program to find if the array can be divided into
// three segments by finding all possible partitions

#include <stdio.h>

// function to find the sum of subarray arr[start...end]
int findSum(int *arr, int start, int end) {
    int sum = 0;
    for(int i = start; i <= end; i++) 
        sum += arr[i];
    return sum;
}

// function to return the index pair of equal sum segments
int* findSplit(int *arr, int n) {
    int *res = (int *)malloc(2 * sizeof(int));
    res[0] = -1;
    res[1] = -1;
    
    // First partition
    for(int i = 0; i < n - 2; i++) {
        
        // Second Partition
        for(int j = i + 1; j < n - 1; j++) {
            
            // Find sum of all three segments
            int sum1 = findSum(arr, 0, i);
            int sum2 = findSum(arr, i + 1, j);
            int sum3 = findSum(arr, j + 1, n - 1);
            
            // If all three segments have equal sum,
            // then return true
            if(sum1 == sum2 && sum2 == sum3) {
                res[0] = i;
                res[1] = j;
                return res;
            }
        }
    }

    // No possible index pair found
    return res;
}

int main() {
    int arr[] = {1, 3, 4, 0, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *res = findSplit(arr, n);
    
    printf("%d %d", res[0], res[1]);

    return 0;
}
