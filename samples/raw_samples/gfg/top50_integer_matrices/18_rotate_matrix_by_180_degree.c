/* Source: https://www.geeksforgeeks.org/dsa/rotate-matrix-180-degree/ */
#include <stdio.h>

void rotateMatrix(int n, int mat[n][n]) {

    // Swap elements from the start and end to
    // rotate by 180 degrees
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n; j++) {
            int temp = mat[i][j];
            mat[i][j] = mat[n - i - 1][n - j - 1];
            mat[n - i - 1][n - j - 1] = temp;
        }
    }

    // Handle the middle row if the matrix 
    // has odd dimensions
    if (n % 2 != 0) {
        int mid = n / 2;
        for (int j = 0; j < n / 2; j++) {
            int temp = mat[mid][j];
            mat[mid][j] = mat[mid][n - j - 1];
            mat[mid][n - j - 1] = temp;
        }
    }
}

int main() {
    int n = 3;
    int mat[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    rotateMatrix(n, mat);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    return 0;
}
