/* Source: https://www.geeksforgeeks.org/dsa/inplace-rotate-square-matrix-by-90-degrees/ */
#include <stdio.h>

// Function to reverse a row
void reverseRow(int n, int row[]) {
    int start = 0, end = n - 1;
    while (start < end) {
        int temp = row[start];
        row[start] = row[end];
        row[end] = temp;
        start++;
        end--;
    }
}

// Function to rotate the matrix
void rotateMatrix(int n, int mat[n][n]) {
    // Step 1: Reverse each row
    for (int i = 0; i < n; i++) {
        reverseRow(n, mat[i]);
    }

    // Step 2: Transpose the matrix
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }
    }
}

int main() {
    int n = 4;
    int mat[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    rotateMatrix(n, mat);

    // Print rotated matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    return 0;
}
