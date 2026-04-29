/* Source: https://www.geeksforgeeks.org/dsa/move-zeroes-end-array/ */
#include <stdio.h>

void pushZerosToEnd(int *arr, int n)
{
    int temp[n];

    // to keep track of the index in temp[]
    int j = 0;

    // Copy non-zero elements to temp[]
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != 0)
            temp[j++] = arr[i];
    }

    // Fill remaining positions in temp[] with zeros
    while (j < n)
        temp[j++] = 0;

    // Copy all the elements from temp[] to arr[]
    for (int i = 0; i < n; i++)
        arr[i] = temp[i];
}

int main()
{
    int arr[] = {1, 2, 0, 4, 3, 0, 5, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    pushZerosToEnd(arr, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
