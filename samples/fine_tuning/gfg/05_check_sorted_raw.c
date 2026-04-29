/* Source: https://www.geeksforgeeks.org/dsa/program-check-array-sorted-not-iterative-recursive/ */
#include <stdio.h>
#include <stdbool.h>

bool isSorted(int arr[], int n) {
    
     // Iterate over the array and check if 
    // every element is greater than or
    // equal to previous element.
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i])
            return false;
    }

    return true;
}

int main() {
    int arr[] = { 10, 20, 30, 40, 50 };
    int n = sizeof(arr) / sizeof(arr[0]);

    if (isSorted(arr, n))
        printf("true\n");
    else
        printf("false\n");

    return 0;
}
