#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int descending_compare(const void *a, const void *b){
    if (*(int*)a > *(int*)b){
        return -1;
    }else if (*(int*)a == *(int*)b){
        return 0;
    }else{
        return 1;
    }
}

int ascending_compare(const void *a, const void *b){
    if (*(int*)a < *(int*)b){
        return -1;
    }else if (*(int*)a == *(int*)b){
        return 0;
    }else{
        return 1;
    }
}


int lower_bound(int *a, int n, int key){
    int left, mid, right;
    left = 0, right = n;
    mid = (left + right)/2;
    while (left+1 != mid || mid+1 != right){
        if (key > a[mid]){
            left = mid;
        }else{
            right = mid+1;
        }
        mid = (left + right)/2;
    }
    if (a[left] >= key)return left;
    if (a[mid] >= key)return mid;
    if (a[right] >= key)return right;
    return n;
}

int a[100000];
int b[100000];
int c[100000];

int main(void){
    int n;
    int i;
    int answer = 0;
    int ai, ci;
    
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    for (i = 0; i < n; i++){
        scanf("%d", &b[i]);
    }
    for (i = 0; i < n; i++){
        scanf("%d", &c[i]);
    }

    qsort(a, n, sizeof(int), ascending_compare);
    qsort(b, n, sizeof(int), ascending_compare);
    qsort(c, n, sizeof(int), ascending_compare);

    
    for (i = 0; i < n; i++){
        ai = lower_bound(a, n, b[i]);
        ci = lower_bound(c, n, b[i]+1);
            answer += (ai)*(n-ci);
        }

    printf("%d\n", answer);
    return 0;
}
