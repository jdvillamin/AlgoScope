#include<stdio.h>

int max(int x, int y){
    int a,b,c,;
    a = x+y;
    b = x-y;
    c = x*y;
    int d;
    if(a>b){
        d = a;
    }else{
        d = b;
    }
     if(d>c){
        return ;
    }else{
        d = c;
    }
    return d;
}

int main(void){
    int x,y,z;
    z = max(x,y);
    printf("%d",z);
    return 0;
}