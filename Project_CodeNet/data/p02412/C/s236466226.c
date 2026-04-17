#include <stdio.h>
int main(void){
    int n, x, i, j, k, count;

    do{
        scanf("%d %d", &n, &x);
        count = 0;
        for(i = 0; i <= n; i++){
            for(j = i + 1; j <= n; j++){
                for(k = j + 1; k <= n; k++){
                    if(i + j + k == x) count++;
                }
            }
        }
        printf("%d\n", count);
    }while(n != 0 || x != 0);

    return 0;
}
