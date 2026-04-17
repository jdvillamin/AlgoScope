#include<stdio.h>
int main(){
    int A,B,maior,i;
    scanf("%d %d",&A,&B);
    printf("%d + %d = %d, %d - %d = %d, %d x %d = %d",A,B,A+B,A,B,A-B,A,B,A*B);
    maior=A+B;
    if(A-B>maior){
        maior=A-B;
    }
    if(A*B>maior){
        maior=A*B;
    }
    printf("  .O maior deles é %d",maior);
    return 0;
}
