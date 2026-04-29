/* Source: https://www.geeksforgeeks.org/dsa/leaders-in-an-array/ */
#include <stdio.h>
#include <stdlib.h>

// Function to find the leaders in an array
int* leaders(int arr[], int n, int* resSize) {
    int* result = (int*)malloc(n * sizeof(int));
    int count = 0;

    for (int i = 0; i < n; i++) {
        int j;
      
        // Check elements to the right
        for (j = i + 1; j < n; j++) {
          
            // If a larger element is found
            if (arr[i] < arr[j])
                break;
        }

        // If no larger element was found
        if (j == n) 
            result[count++] = arr[i];
    }

    *resSize = count;
    return result;
}

int main() {
    int arr[] = { 16, 17, 4, 3, 5, 2 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int resSize;
    
    int* result = leaders(arr, n, &resSize);
    for (int i = 0; i < resSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    free(result);
    return 0;
}
