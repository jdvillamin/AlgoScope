#include <stdio.h>
int main(){
    int n,i,j,q,p,tmp;
    int g[101][101]={};
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d %d",&q,&p);
        for(j=0;j<p;j++){
            scanf("%d",&tmp);
            g[q][tmp]=1;
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(j-1) printf(" ");
            printf("%d",g[i][j]);
        }
        printf("\n");
    }
    return 0;
}
