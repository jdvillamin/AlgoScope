#include <stdio.h>
int main(void){
    int i,N;
    int k[100]={},p[100]={};
    
    scanf("%d",&N);
    
    for(i=0;i<N;i++){
        scanf("%d %d",&k[i],&p[i]);
        printf("%d\n",(k[i]%p[i]) ? k[i]%p[i] : p[i]);
    }
    
    return 0;
}