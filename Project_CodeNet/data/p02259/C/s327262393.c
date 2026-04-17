
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int bubbleSort(int A[],int N) {
    int i,j;
    int sw = 0;
    unsigned short flag = 1;
    for(i=0;flag;i++) {
        flag = 0;
        for(j=N-1;j>=i+1;j--) {
            if(A[j]<A[j-1]) {
                swap(&A[j],&A[j-1]);
                flag = 1;
                sw++;
            }
        }
    }
    return sw;
}

int main(void) {
    int i, A[100], N, sw;
    scanf("%d",&N);
    for(i=0;i<N;i++) scanf("%d",&A[i]);

    sw = bubbleSort(A,N);

    for(i=0;i<N;i++) {
        if (i) printf(" ");
        printf("%d",A[i]);
    }
    printf("\n%d\n",sw);

    return 0;
}



