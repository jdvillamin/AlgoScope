/* Source: https://www.geeksforgeeks.org/dsa/check-given-array-contains-duplicate-elements-within-k-distance/ */
#include <stdio.h>

int checkDuplicatesWithinK(int arr[], int n, int k)
{
    // Traverse for every element
    for (int i = 0; i < n; i++) {
      
        // Traverse next k elements
        for (int c = 1; c <= k && (i + c) < n; c++) {
            int j = i + c;
          
            // If we find one more occurrence within k
            if (arr[i] == arr[j])
                return 1; 
        }
    }
    return 0; 
}

// Driver method to test above method
int main()
{
    int arr[] = {10, 5, 3, 4, 3, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%s\n", checkDuplicatesWithinK(arr, n, 3) ? "Yes" : "No");
    return 0;
}
