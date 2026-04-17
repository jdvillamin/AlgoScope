#include <stdio.h>
int main(){
        int i,j;
        int ans = 1;
        scanf("%d", &i);
        for(j=i;j>0;j--){
                ans = ans * j;
        }
        printf("%d", ans);
return 0;
}