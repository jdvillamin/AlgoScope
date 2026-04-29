/* Source: https://www.geeksforgeeks.org/dsa/intersection-of-two-arrays/ */
#include <stdio.h>

void intersect(int a[], int n1, int b[], 
            int n2, int res[], int *res_size) {
  
    // Traverse through a[] and 
    // search every element a[i] in b[]
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {

            // If found, check if the element 
            // is already in the result
            int found = 0;
            if (a[i] == b[j]) {
                for (int k = 0; k < *res_size; k++) {
                    if (res[k] == a[i]) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    res[(*res_size)++] = a[i];
                }
            }
        }
    }
}

int main() {
    int a[] = {1, 2, 3, 2, 1};
    int b[] = {3, 2, 2, 3, 3, 2};
    int res[10];
    int res_size = 0;

    intersect(a, 5, b, 6, res, &res_size);

    for (int i = 0; i < res_size; i++) {
        printf("%d ", res[i]);
    }

    return 0;
}
