#include <stdio.h>

int main(){

    int n,a,i;
    scanf("%d",&n);

    for (i=1; i<n+1; i++) {
        if (i%3==0) {
            printf(" %d\n",i);
        }
        else if(i%10==3){
            a=i%10;
            printf(" %d\n",i);
        }
        else
            ;
    }
    return 0;
}