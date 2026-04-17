#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <limits.h>

int main(void){
    int i;
    char s[21];
    scanf("%s",s);
    for(i=1;i<=strlen(s);i++){
        printf("%c",s[strlen(s)-i]);
    }
    printf("\n");
    return 0;
}

