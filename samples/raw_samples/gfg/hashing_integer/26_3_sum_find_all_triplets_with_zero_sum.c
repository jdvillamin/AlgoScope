/* Source: https://www.geeksforgeeks.org/dsa/find-triplets-array-whose-sum-equal-zero/ */
// C program to find triplet having sum zero using 
// three nested loops
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIMIT 100 

void findTriplets(int arr[], int n, int res[][3], int* count) {
    *count = 0; 

    // Generating all triplets
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
              
                // If the sum of triplet equals zero
              	// then add it's indexes to reuslt
                if (arr[i] + arr[j] + arr[k] == 0) {
                	res[*count][0] = i;
                    res[*count][1] = j;
                    res[*count][2] = k;
                    (*count)++; 
                }
            }
        }
    }
}

int main() {
    int arr[] = {0, -1, 2, -3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
  	
  	// res array to store all triplets
    int res[MAX_LIMIT][3]; 
  	
  	// Variable to store number of triplets found
    int count = 0; 
    findTriplets(arr, n, res, &count);
    for (int i = 0; i < count; i++) 
        printf("%d %d %d\n", res[i][0], res[i][1], res[i][2]);
    
    return 0;
}
