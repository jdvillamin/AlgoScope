#include <stdio.h>

int main(){

    int N;
    scanf("%d", &N);

    int i;
    long long int A, ans=1;
    long long int THR = 1000000000000000000;
    for(i=1;i<=N;i++){
        scanf("%lld", &A);
        ans *= A;
    }

    if( ans > THR ){
        printf("-1\n");
        return 0;
    }

    printf("%lld\n", ans);

    return 0;
}

