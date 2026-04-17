#include<stdio.h>

int main(){
    int a,s[3],i=0,count=0;
    scanf("%d",&a);

    for(i=0;i<3;i++){
        s[i]=a%10;
        a/=10;
    }


    if(s[0]==1) count++;
    if(s[1]==1) count++;
    if(s[2]==1) count++;

    printf("%d",count);


return 0;
}
