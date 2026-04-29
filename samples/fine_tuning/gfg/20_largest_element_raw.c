/* Source: https://www.geeksforgeeks.org/dsa/program-to-find-largest-element-in-an-array/ */
#include <stdio.h>

int largest(int arr[], int n) {
    int i;
    int max = arr[0];

    // Traverse array elements from second and
    // compare every element with current max
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    return max;
}

int main() {
    int arr[] = {20, 10, 20, 4, 100};
    int n = sizeof(arr) / sizeof(arr[0]);
  
    printf("%d", largest(arr, n));
    return 0;
}
