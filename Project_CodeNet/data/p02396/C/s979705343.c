#include <stdio.h>

int main(){
    int x;
    int i=0;
    while(1){
        scanf("%d", &x);
        if(x==0)break;
        printf("Case %d: %d\n", ++i, x);
    }
    return 0;
}