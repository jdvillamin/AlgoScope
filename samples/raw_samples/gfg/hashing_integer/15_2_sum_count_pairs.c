/* Source: https://www.geeksforgeeks.org/dsa/count-pairs-with-given-sum/ */
#include <stdio.h>

int countPairs(int arr[], int n, int target) {
    int cnt = 0;

    // Iterate through each element in the array
    for (int i = 0; i < n; i++) {
      
        // For each element arr[i], check every
        // other element arr[j] that comes after it
        for (int j = i + 1; j < n; j++) {
          
            // Check if the sum of the current pair
            // equals the target
            if (arr[i] + arr[j] == target) {
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    int arr[] = {1, 5, 7, -1, 5};
    int target = 6;
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", countPairs(arr, n, target));
    return 0;
}
