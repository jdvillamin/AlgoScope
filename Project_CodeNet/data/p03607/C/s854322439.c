#include <stdio.h>
#include <stdlib.h>

int comp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}

main(){
    int N;
    scanf("%d",&N);
    int p[N];
    int i=0;
    while(i<N)scanf("%d",&p[i++]);

    qsort(p,N,sizeof(int),comp);
    int n=-1;
    int sum=0;
    for(i=0;i<N;i++){
        if(n!=p[i]){
            n=p[i];
            sum++;
        }else{
            n=-1;
            sum--;
        }
    }
    printf("%d\n",sum);
    return 0;
}