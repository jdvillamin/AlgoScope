#include<stdio.h>
int n,k,i,m=1e9+7,a[200001]={},r=0;
int main(){
    scanf("%d%d",&n,&k);
    for(i=1;i<=n+1;i++)a[i]=(a[i-1]+i)%m;
    for(i=k;i<=n+1;i++)r=(r+(a[n]+1+m-a[n-i<0?0:n-i]-a[i-1]))%m;
    printf("%ld",r);
    return 0;
}