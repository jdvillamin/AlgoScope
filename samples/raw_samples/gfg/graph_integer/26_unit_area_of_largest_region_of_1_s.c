/* Source: https://www.geeksforgeeks.org/dsa/find-length-largest-region-boolean-matrix/ */
// C Program to find area of the largest region of 1s

#include <stdio.h>

// Define the maximum size of the matrix and queue
#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_QUEUE_SIZE MAX_ROWS * MAX_COLS

// Define a structure for the queue to store pairs of integers
struct Pair {
    int row, col;
};

int isSafe(int M[MAX_ROWS][MAX_COLS], int r, int c, int rows, int cols) {
  	
    // Row number is in range, column number is in range, and value is 1
    return (r >= 0 && r < rows) && (c >= 0 && c < cols) && (M[r][c] == 1);
}

// Breadth-First-Search to visit all cells in the current island
int BFS(int M[MAX_ROWS][MAX_COLS], int r, int c, int rows, int cols) {
  	
    // These arrays are used to get row and column numbers of 
  	// 8 neighbours of a given cell
    int dirR[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dirC[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int area = 0;

    // Create a queue for BFS traversal
    struct Pair queue[MAX_QUEUE_SIZE];
    int front = 0, rear = 0;

    // Push the cell(r, c) into queue and mark it as visited
    queue[rear++] = (struct Pair){r, c};
    M[r][c] = 0;

    while (front < rear) {
        struct Pair curr = queue[front++];

        // Increment the area of region
        area += 1;

        // Recur for all 8 connected neighbours
        for (int i = 0; i < 8; i++) {
            int newR = curr.row + dirR[i];
            int newC = curr.col + dirC[i];

            if (isSafe(M, newR, newC, rows, cols)) {
                M[newR][newC] = 0;
                queue[rear++] = (struct Pair){newR, newC};
            }
        }
    }
    return area;
}

// Function to find the area of the largest region of 1s
int largestRegion(int M[MAX_ROWS][MAX_COLS], int rows, int cols) {
  	
    // Initialize result as 0 and traverse through all cells 
  	// of the given matrix
    int maxArea = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          	
            // If a cell with value 1 is found
            if (M[i][j] == 1) {
                int area = BFS(M, i, j, rows, cols);

                // Maximize the area
                if (area > maxArea) {
                    maxArea = area;
                }
            }
        }
    }
    return maxArea;
}

int main() {
    // Define the matrix directly
    int M[MAX_ROWS][MAX_COLS] = {
        {1, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0},
        {1, 0, 0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0, 1, 1}
    };

    int rows = 5, cols = 7; // Matrix dimensions

    printf("%d\n", largestRegion(M, rows, cols));

    return 0;
}
