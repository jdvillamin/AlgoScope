/* Source: https://www.geeksforgeeks.org/dsa/count-pairs-difference-equal-k/ */
// C Program to count all pairs with difference equal to k
// using Two Pointer Technique

#include <stdio.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int countPairs(int arr[], int n, int k) {
    int cnt = 0;
  
    qsort(arr, n, sizeof(int), compare);
    int i = 0, j = 0;
  
    while (j < n) {
        if (arr[j] - arr[i] < k) 
            j++;
      
        // If difference is greater than k, decrease the 
        // difference by moving i pointer towards right
        else if (arr[j] - arr[i] > k)
            i++;
      
        // If difference is equal to k, increase the difference
        // by moving j pointer towards right
        else {
            int ele1 = arr[i], ele2 = arr[j];
            int cnt1 = 0, cnt2 = 0;
          
            // Count frequency of first element of the pair
            while (j < n && arr[j] == ele2) {
                j++;
                cnt2++;
            }
          
            // Count frequency of second element of the pair
            while (i < n && arr[i] == ele1) {
                i++;
                cnt1++;
            }
          
            // If both the elements are same, then count of
            // pairs = the number of ways to choose 2 
            // elements among cnt1 elements
            if (ele1 == ele2) 
                cnt += (cnt1 * (cnt1 - 1)) / 2;
          
            // If the elements are different, then count of
            // pairs = product of the count of both elements
            else 
                cnt += (cnt1 * cnt2);
        }
    }
    return cnt;
}

int main() {
    int arr[] = {1, 4, 1, 4, 5};
    int k = 3;
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", countPairs(arr, n, k));
    return 0;
}
