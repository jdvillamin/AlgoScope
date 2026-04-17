#include<stdio.h>
int main(void)
{
    static short A[2000000],C[10000],B[2000000];
    static int i,n;

    for(i=0;i<10000;i++) C[i]=0;
    scanf("%d",&n);
    for(i=0;i<n;i++) scanf("%d", &A[i]);
    for(i=0;i<n;i++) C[A[i]]++;
    for(i=1;i<10000;i++) C[i]+=C[i-1];
    for(i=n-1;i>=0;i--){
        B[C[A[i]]-1] = A[i];
        C[A[i]]--;
    }
    printf("%d",B[0]);
    for(i=1;i<n;i++) printf(" %d",B[i]);
    printf("\n");
    return 0;
}