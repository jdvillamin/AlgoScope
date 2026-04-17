#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void){
    int A,B,X;
    scanf("%d %d %d",&A,&B,&X);
    if(A<=X&&X<=A+B){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
    return 0;
}