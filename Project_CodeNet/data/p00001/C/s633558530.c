#include<stdio.h>
int main(void){
    int a,b[11]={0};
    int i,j,k,l,m,n,o,p,q;
    scanf("%d",&b[0]);
    for(i=1;i<10;i++){
        scanf("%d",&a);
        n=0;
        for(k=0;k<i+1;k++){
            if(n==i){
                b[k]=a;
                break;
            }
            if(a>b[k]){
                for(l=i;l>k;l--){
                    b[l]=b[l-1];
                }
                b[l]=a;
                break;
            }
            n++;
        }
    }
    for(m=0;m<3;m++){
        printf("%d\n",b[m]);
    }
    return 0;
}