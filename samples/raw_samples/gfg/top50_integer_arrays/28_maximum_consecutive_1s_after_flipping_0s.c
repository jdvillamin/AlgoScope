/* Source: https://www.geeksforgeeks.org/dsa/find-zeroes-to-be-flipped-so-that-number-of-consecutive-1s-is-maximized/ */
#include <stdio.h>

int maxOnes(int arr[], int n, int k) {
    int res = 0;

    // Start and end pointer of the window
    int start = 0, end = 0;

    // Counter to keep track of zeros in current window
    int cnt = 0;

    while (end < n) {
        if (arr[end] == 0)
            cnt++;

        // Shrink the window from left if no. 
      	// of zeroes are greater than k
        while (cnt > k) {
            if (arr[start] == 0)
                cnt--;

            start++;
        }

        res = (res > (end - start + 1)) ? res : (end - start + 1);

        // Increment the end pointer to expand the window
        end++;
    }

    return res;
}

int main() {
    int arr[] = {1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1};
    int k = 2;
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", maxOnes(arr, n, k));
    return 0;
}
