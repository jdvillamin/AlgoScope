#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int V[N];
    int C[N];
    int sum=0;
    
    int i;
    
    for(i=0; i<N; ++i){
        scanf("%d",&V[i]);
    }
    for(i=0; i<N; ++i){
        scanf("%d",&C[i]);
    }
    
    for(i=0; i<N; ++i){
        if(V[i] - C[i] >= 0) sum += V[i] - C[i];
    }
    
    printf("%d\n", sum);
    return 0;
}