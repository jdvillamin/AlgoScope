/* Source: https://www.geeksforgeeks.org/dsa/3-sum-count-all-triplets-with-given-sum/ */
// C program to count all triplets having sum equal to
// target by exploring all possible triplets

#include <stdio.h>

int countTriplets(int arr[], int n, int target) {
    int cnt = 0;

    // Generating all triplets
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {

                // If the sum of a triplet is equal to target
                // then increment count by 1
                if (arr[i] + arr[j] + arr[k] == target)
                    cnt += 1;
            }
        }
    }
    return cnt;
}

int main() {
    int arr[] = {0, -1, 2, -3, 1};
    int target = -2;
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", countTriplets(arr, n, target));
    return 0;
}
