#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
void swap(int *a,int *b){int tmp;tmp=*a;*a=*b;*b=tmp;}

int main(void){
    int x,ans=100000;
    scanf("%d",&x);
    while(x>=100){
        ans=min(ans,abs(753-x%1000));
        x/=10;
    }
    printf("%d\n",ans);
    return 0;
}