/* Source: https://www.geeksforgeeks.org/dsa/union-of-two-arrays/ */
#include <stdio.h>
#include <stdlib.h>

int *findUnion(int a[], int n, int b[], int m, int *size) {

    // Allocate enough space for the 
    // result (maximum possible size)
    int *res = (int *)malloc((m + n) * sizeof(int));
    int index = 0;

    // Traverse through a[] and 
    // search every element
    for (int i = 0; i < n; i++) {

        // Check if the element is already
        // in the result to avoid duplicates
        int j;
        for (j = 0; j < index; j++) {
            if (res[j] == a[i])
                break;
        }
        if (j == index) {
            res[index++] = a[i];
        }
    }

    // Traverse through b[] and 
    // search every element
    for (int i = 0; i < m; i++) {
        
        // Check if the element is already
        // in the result to avoid duplicates
        int j;
        for (j = 0; j < index; j++) {
            if (res[j] == b[i])
                break;
        }
        if (j == index) {
            res[index++] = b[i];
        }
    }

    // Update the size of the result array
    *size = index;
    return res; 
}

int main() {
    int a[] = {1, 2, 3, 2, 1};
    int b[] = {3, 2, 2, 3, 3, 2};
    int n = sizeof(a) / sizeof(a[0]);
    int m = sizeof(b) / sizeof(b[0]);
    int size;

    int *result = findUnion(a, n, b, m, &size);

    for (int i = 0; i < size; i++)
        printf("%d ", result[i]);

    free(result);
    return 0;
}
