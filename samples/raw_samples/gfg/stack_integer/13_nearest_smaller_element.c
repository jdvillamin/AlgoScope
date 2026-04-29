/* Source: https://www.geeksforgeeks.org/dsa/find-the-nearest-smaller-numbers-on-left-side-in-an-array/ */
#include <stdio.h>
#include <stdlib.h>

int* prevSmaller(int arr[], int n) {
   
    int* result = (int*)malloc(n * sizeof(int));

    // stack to keep track of elements
    int* st = (int*)malloc(n * sizeof(int));
    int top = -1;

    // initialize all PSEs as -1
    for (int i = 0; i < n; i++) {
        result[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        
        // pop elements from stack which are >= current element
        while (top >= 0 && st[top] >= arr[i]) {
            top--;
        }

        // if stack is not empty, top element is PSE
        if (top >= 0) {
            result[i] = st[top];
        }

        // push current element onto stack
        st[++top] = arr[i];
    }

    return result;
}

int main() {
    int arr[] = {1, 5, 0, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int* result = prevSmaller(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
