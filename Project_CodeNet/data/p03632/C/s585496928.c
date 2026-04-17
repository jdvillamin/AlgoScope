#include <stdio.h>

int min(x,y){
    if(x<y){
        return x;
    }else{
        return y;
    }
}

int max(x,y){
    if(x<y){
        return y;
    }else{
        return x;
    }
}

int main(void){
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    printf("%d",max(min(b,d)-max(a,c),0));
    return 0;
}
