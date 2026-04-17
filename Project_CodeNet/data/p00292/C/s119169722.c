#include<stdio.h>

int main(void){
    int w,n,i,k[n],p[n];
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d %d",&k[i],&p[i]);
    for(i=0;i<n;i++){
         w=k[i]%p[i];
         if(w==0)
            printf("%d\n",p[i]);
         else
            printf("%d\n",w);
    }
    return 0;
}
 