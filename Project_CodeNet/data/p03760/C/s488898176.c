#include <stdio.h>
#include <string.h>

int main(void){
    char O[50],E[50];
    int i,size;
    char ans[100];
    scanf("%s",O);
    scanf("%s",E);
    size = strlen(O) + strlen(E);
    if(strlen(O) - strlen(E) == 0){
        for(i=0;i<size;i++){
            if(i % 2 == 0) ans[i] = O[i / 2];
            else ans[i] = E[i / 2];
        }
    }else{
        for(i=0;i<size - 1;i++){
            if(i % 2 == 0) ans[i] = O[i / 2];
            else ans[i] = E[i / 2];
        }
    }
    printf("%s\n",ans);
    return 0;
}