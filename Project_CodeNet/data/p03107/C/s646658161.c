#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    char S[10000];
    int i = 0;
    for(i = 0; i < 10000; i ++){
        S[i] = 0;
    }
    scanf("%s", S);
    int num_0 = 0, num_1 = 0;
    for(i = 0; i < 10000; i ++){
        if(S[i] == 48){
            num_0 ++;
        }else if(S[i] == 49){
            num_1 ++;
        }
        /*printf("%d %d\n", S[i], i);*/
    }
    int ans = 0;
    if(num_0 < num_1){
        ans = 2 * num_0;
    }else{
        ans = 2 * num_1;
    }
    printf("%d", ans);
    return 0;
}