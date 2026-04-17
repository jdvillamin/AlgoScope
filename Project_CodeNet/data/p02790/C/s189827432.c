#include<stdio.h>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    if(a<b){
        for(int i=0;i<b;i++)
            printf("%d",a);
    }
    else{
        for(int i=0;i<a;i++)
            printf("%d",b);
    }
    printf("\n");
    return 0;
}