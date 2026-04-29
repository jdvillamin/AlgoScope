/* Source: https://www.geeksforgeeks.org/dsa/minimize-the-maximum-difference-between-the-heights/ */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdlib.h> // For qsort

int compare(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int getMinDiff(int arr[], int n, int k)
{
    int res = arr[n - 1] - arr[0];

    // Sort the array using qsort
    qsort(arr, n, sizeof(int), compare);

    // For all indices i, increment
    // arr[0...i-1] by k and decrement and arr[i...n-1] by k
    for (int i = 1; i < n; i++)
    {
        // Impossible to decrement height of ith tower by k, continue
        if (arr[i] - k < 0)
            continue;

        int minH = (arr[0] + k < arr[i] - k) ? arr[0] + k : arr[i] - k;
        int maxH = (arr[i - 1] + k > arr[n - 1] - k) ? arr[i - 1] + k : arr[n - 1] - k;
        res = (res > maxH - minH) ? maxH - minH : res;
    }

    return res;
}

int main()
{
    int k = 2;
    int arr[] = {1, 5, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    int ans = getMinDiff(arr, n, k);
    printf("%d", ans);

    return 0;
}
