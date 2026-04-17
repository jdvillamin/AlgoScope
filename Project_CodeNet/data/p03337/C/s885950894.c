#include<stdio.h>
int main()
{
    int A,B;
    scanf("%d%d",&A,&B);
   A+B;
   A-B;
   A*B;
    if(A+B>A-B && A+B>A*B){
        printf("%d",A+B);
    }
    else if(A-B>A+B && A-B>A*B){
        printf("%d",A-B);
    }
    else if(A*B>A+B && A*B>A-B){
        printf("%d",A*B);
    }
    else if(A+B==A-B && A+B==A*B){
        printf("%d",A+B);
    }

}
