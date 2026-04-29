/* Source: https://www.geeksforgeeks.org/dsa/find-whether-an-array-is-subset-of-another-array-set-1/ */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

bool isSubset(int a[], int b[], int m, int n) {
    sort(a, m);
    sort(b, n);

    int i = 0, j = 0;

    while (i < m && j < n) {
        if (a[i] < b[j]) {
            // move in a to catch up
            i++;   
        }
        else if (a[i] == b[j]) {
            i++;
            // matched one element from b
            j++;   
        }
        else {
            // a[i] > b[j] → means b[j] is missing
            return false;
        }
    }
    
    // all b[] matched
    return (j == n); 
}

int main() {
    int a[] = {11, 1, 13, 21, 3, 7};
    int b[] = {11, 3, 7, 1};
    int m = sizeof(a)/sizeof(a[0]);
    int n = sizeof(b)/sizeof(b[0]);

    if (isSubset(a, b, m, n)) printf("true\n");
    else printf("false\n");

    return 0;
}
