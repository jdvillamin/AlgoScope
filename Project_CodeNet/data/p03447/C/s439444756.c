#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    int x, a, b, sub1;
    scanf("%d%d%d", &x, &a, &b);
    sub1 = x - a;
    do{
        sub1 = sub1 - b;
    }while(sub1 > b);
    
    printf("%d\n", sub1);
}