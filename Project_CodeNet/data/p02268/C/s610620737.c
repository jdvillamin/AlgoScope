#include <stdio.h>
#include <stdlib.h>

int binSearch(int,int[],int);

int main(int argc, char** argv) {
    int size1;
    scanf("%d\n", &size1);
    int array1[size1];
    for(int i = 0; i < size1; i++)
        scanf("%d", &array1[i]);
    
    int size2;
    scanf("%d\n", &size2);
    int array2[size2];
    for(int i = 0; i < size2; i++)
        scanf("%d", &array2[i]);
    
    int searched[size1];
    for(int i = 0; i < size1; i++)
        searched[i] = 0;
    int count = 0;
    int temp;
    for(int i = 0; i < size2; i++){
        temp = binSearch(size1,array1,array2[i]);
        if(temp >= 0 && temp < size1)
            searched[temp]++;
    }
    
    for(int i = 0; i < size1; i++)
        if(searched[i])
            count++;
    
    printf("%d\n", count);
    return (EXIT_SUCCESS);
}

int binSearch(int size, int array[size], int searchVal){
    int left = 0;
    int right = size;
    int mid;
    while(left < right){
        mid = (left + right)/2;
        if(array[mid] == searchVal)
            return mid;
        if(searchVal > array[mid])
            left = mid + 1;
        else if(searchVal < array[mid])
            right = mid;
    }
    return -1;
}

