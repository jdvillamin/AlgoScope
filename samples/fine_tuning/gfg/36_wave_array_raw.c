/* Source: https://www.geeksforgeeks.org/dsa/sort-array-wave-form-2/ */
#include<stdio.h>
#include<stdlib.h>

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sortInWave(int arr[], int n){
    // swap adjacent elements
    for (int i=0; i<n-1; i += 2)
        swap(&arr[i], &arr[i+1]);
}

int main(){
    
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    sortInWave(arr, n);
    for (int i=0; i<n; i++)
       printf("%d ",arr[i]);
    return 0;
}
