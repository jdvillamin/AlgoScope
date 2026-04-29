/* Source: https://www.geeksforgeeks.org/dsa/last-moment-before-all-ants-fall-out-of-a-plank/ */
#include <stdio.h>

int getLastMoment(int n, int left[], int l1, int right[], int l2) {
    
    int res = 0;
  
    // Find the time to fall off the plank for all 
    // ants moving towards left
    for(int i = 0; i < l1; i++) {
        if (left[i] > res) {
            res = left[i];
        }
    }
  
    // Find the time to fall off the plank for all 
    // ants moving towards right
    for(int i = 0; i < l2; i++) {
        int time = n - right[i];
        if (time > res) {
            res = time;
        }
    }
    
    // Return the maximum time among all ants
    return res;
}

int main() {
    int n = 4;
    int left[] = {2};
    int right[] = {0, 1, 3};
    int l1 = sizeof(left) / sizeof(left[0]);
    int l2 = sizeof(right) / sizeof(right[0]);
    printf("%d\n", getLastMoment(n, left, l1, right, l2));
    return 0;
}
