#include <stdio.h>
#include <stdlib.h>
int compar(const int *val1,const int *val2){
    return *val1-*val2;
}

int main(void){
    int len[3],sign,num,hole;
    for(;scanf("%d %d %d",&len[0],&len[1],&len[2]),len[2];){
        qsort(len,3,sizeof(int),(int (*)(const void *,const void *))compar);
        sign=len[0]*len[0]+len[1]*len[1];
        scanf("%d",&num);
        while(num--){
            scanf("%d",&hole);
            hole*=2;
            printf("%s",sign>=hole*hole?"NA\n":"OK\n");
        }
    }
    return 0;
}