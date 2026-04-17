#include <stdio.h>

int n,count=2;

int fibonacch(int f1, int f2){
    int f=f1+f2;
    if(count++==n) return f;
    else return fibonacch(f2, f);
}

int main(){
    scanf("%d",&n);
    if(!n || n==1) printf("1\n");
    else printf("%d\n",fibonacch(1, 1));
    return 0;
}


