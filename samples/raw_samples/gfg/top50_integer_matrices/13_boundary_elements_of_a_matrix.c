/* Source: https://www.geeksforgeeks.org/dsa/boundary-elements-matrix/ */
#include <stdio.h>

void boundaryTraversal(int n, int m, int mat[n][m], int res[], int *size)
{
    int k = 0; // Index for res[]

    // Traverse the top row from left to right
    for (int j = 0; j < m; j++)
    {
        res[k++] = mat[0][j];
    }

    // Traverse the last column from 2nd row
    for (int i = 1; i < n; i++)
    {
        res[k++] = mat[i][m - 1];
    }

    // Traverse the bottom row from second last column to first
    if (n > 1)
    { // Check to avoid duplicate row in single-row matrix
        for (int j = m - 2; j >= 0; j--)
        {
            res[k++] = mat[n - 1][j];
        }
    }

    // Traverse the first column from second last row up to second row
    if (m > 1)
    { // Check to avoid duplicate column in single-column matrix
        for (int i = n - 2; i > 0; i--)
        {
            res[k++] = mat[i][0];
        }
    }

    *size = k; // Set the size of the result
}

int main()
{
    int mat[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    int n = 3, m = 4;
    
    // Maximum possible size
    int res[n * m]; 
    int size;

    boundaryTraversal(n, m, mat, res, &size);

    for (int i = 0; i < size; i++)
    {
        printf("%d ", res[i]);
    }
    printf("\n");

    return 0;
}
