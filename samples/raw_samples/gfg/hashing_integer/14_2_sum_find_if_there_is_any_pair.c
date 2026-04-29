/* Source: https://www.geeksforgeeks.org/dsa/check-if-pair-with-given-sum-exists-in-array/ */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}

// Function to perform binary search
bool binarySearch(int arr[], int left,
                        int right, int target){
    while (left <= right){
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return true;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

bool twoSum(int arr[], int n, int target){
 
    qsort(arr, n, sizeof(int), compare);

    for (int i = 0; i < n; i++){
        int complement = target - arr[i];

        // Use binary search to
        // find the complement
        if (binarySearch(arr, i + 1,
                        n - 1, complement))
            return true;
    }
    // If no pair is found
    return false;
}

int main(){
    int arr[] = {0, -1, 2, -3, 1};
    int target = -2;
    int n = sizeof(arr) / sizeof(arr[0]);

    if (twoSum(arr, n, target))
        printf("true\n");
    else
        printf("false\n");

    return 0;
}
