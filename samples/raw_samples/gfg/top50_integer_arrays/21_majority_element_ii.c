/* Source: https://www.geeksforgeeks.org/dsa/find-all-array-elements-occurring-more-than-floor-of-n-divided-by-3-times/ */
#include <stdio.h>
#include <limits.h>

void findMajority(int arr[], int n, int *res, int *resSize) {
    
    // Initialize two candidates and their counts
    int ele1 = -1, ele2 = -1, cnt1 = 0, cnt2 = 0;

    for (int i = 0; i < n; i++) {
        int ele = arr[i];

        // Increment count for candidate 1
        if (ele1 == ele) {
            cnt1++;
        }
        
        // Increment count for candidate 2
        else if (ele2 == ele) {
            cnt2++;
        }
        
        // New candidate 1 if count is zero
        else if (cnt1 == 0) {
            ele1 = ele;
            cnt1++;
        }
        
        // New candidate 2 if count is zero
        else if (cnt2 == 0) {
            ele2 = ele;
            cnt2++;
        }
        
        // Decrease counts if neither candidate
        else {
            cnt1--;
            cnt2--;
        }
    }

    cnt1 = 0;
    cnt2 = 0;

    // Count the occurrences of candidates
    for (int i = 0; i < n; i++) {
        int ele = arr[i];
        if (ele1 == ele) cnt1++;
        if (ele2 == ele) cnt2++;
    }

    // Add to result if they are majority elements
    *resSize = 0;
    if (cnt1 > n / 3) res[(*resSize)++] = ele1;
    if (cnt2 > n / 3 && ele1 != ele2) res[(*resSize)++] = ele2;

    // Sort the result if there are two elements
    if (*resSize == 2 && res[0] > res[1]) {
        int temp = res[0];
        res[0] = res[1];
        res[1] = temp;
    }
}

int main() {
    int arr[] = {2, 2, 3, 1, 3, 2, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int res[2]; 
    int resSize;

    findMajority(arr, n, res, &resSize);
    for (int i = 0; i < resSize; i++) {
        printf("%d ", res[i]);
    }
    return 0;
}
