/* Source: https://www.geeksforgeeks.org/dsa/majority-element/ */
#include <stdio.h>

int majorityElement(int arr[], int n) {
    
    // Loop to consider each element as 
    // a candidate for majority
    for (int i = 0; i < n; i++) {
        int count = 0; 

        // Inner loop to count the frequency of arr[i]
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }

        // Check if count of arr[i] is more
        // than half the size of the array
        if (count > n / 2) {
            return arr[i]; 
        }
    }

    // If no majority element found, return -1
    return -1;
}

int main() {
    int arr[] = {1, 1, 2, 1, 3, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("%d\n", majorityElement(arr, n));

    return 0;
}
