/* Source: https://www.geeksforgeeks.org/dsa/maximum-distance-two-occurrences-element-array/ */
// C Program to find max distance between two occurrences
// in array by exploring all pairs

#include <stdio.h>
#include <stdlib.h>

// function to find the maximum distance
int maxDistance(int arr[], int n) {
    int res = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
          
            // check if two elements are equal
            if (arr[i] == arr[j]) {
          
              // calculate the distance and update res
                res = (res > (j - i)) ? res : (j - i);
            }
        }
    }
    return res;
}

int main() {
    int arr[] = {1, 2, 4, 1, 3, 4, 2, 5, 6, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", maxDistance(arr, n));
    return 0;
}
