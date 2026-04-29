/* Source: https://www.geeksforgeeks.org/dsa/majority-element/ */
#include <stdio.h>

int majorityElement(int arr[], int n) {

    int candidate = -1;
    int count = 0;

    // Find a candidate
    for (int i = 0; i < n; i++) {

        if (count == 0) {
            candidate = arr[i];
            count = 1;
        }
        else if (arr[i] == candidate) {
            count++;
        }
        else {
            count--;
        }
    }

    // Validate the candidate
    count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == candidate) {
            count++;
        }
    }

  	// If count is greater than n / 2, return
  	// the candidate; otherwise, return -1
    if (count > n / 2) {
        return candidate;
    } else {
        return -1;
    }
}

int main() {
    int arr[] = {1, 1, 2, 1, 3, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", majorityElement(arr, n));
    return 0;
}
