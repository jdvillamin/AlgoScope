#include <stdio.h>
int main(void)
{
    int a[1000000];
    int n,m;
    int i,j,k;
    int max=0;
    int sum=0;
        
    scanf("%d %d",&n,&m);


    while(n != 0){
        for(i=0;i<n;i++){
            scanf("%d",&a[i]);
        }
        
        for(i=0;i<=n;i++){
            for(j=i+1;j<=n;j++){
                sum =a[i] + a[j];
                if (sum > max && sum <= m){
                    max = sum;
                }
            }
        }
    if(max == 0){
        printf("NONE\n");
    }else{
        printf("%d\n",max);
    }
    max = 0;
    scanf("%d %d",&n,&m);
    }
}
