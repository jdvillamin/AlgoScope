/* Source: https://www.geeksforgeeks.org/dsa/check-two-given-sets-disjoint/ */
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int areDisjoint(int a[], int n, int b[], int m) {
    
    // Sorting both the arrays
    qsort(a, n, sizeof(int), compare);
    qsort(b, m, sizeof(int), compare);
    
    // Initializing pointers at the  
    // beginning of both the arrays
    int i = 0, j = 0;
    
    while(i < n && j < m) {
        
        // If any common element is found, then
        // given arrays are not disjoint
        if(a[i] == b[j])
            return 0; 
            
        // Incrementing the pointer  
        // having smaller value
        if(a[i] < b[j])
            i++;
        else
            j++;
    }
    
    return 1; 
}

int main() {
    int a[] = {12, 34, 11, 9, 3};
    int b[] = {7, 2, 1, 5};
    int n = sizeof(a) / sizeof(a[0]);
    int m = sizeof(b) / sizeof(b[0]);
    
    if(areDisjoint(a, n, b, m))
        printf("True");
    else
        printf("False");
        
    return 0;
}
