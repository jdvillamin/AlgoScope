#include <stdio.h>
#include <string.h>

int main(void)
{
    int i, n, turn;
    char taro[101], hanako[101];
    int tcount = 0, hcount = 0;
    scanf("%d", &n);

    for(i = 0; i < n; i++){
        scanf("%s %s", taro, hanako);
        if(!strcmp(taro, hanako)){
            tcount++;
            hcount++;
        }else if(strcmp(taro, hanako) > 0){
            tcount += 3;
        }else if(strcmp(taro, hanako) < 0){
            hcount += 3;
        }
    }
    printf("%d %d\n", tcount, hcount);

    return 0;
}
