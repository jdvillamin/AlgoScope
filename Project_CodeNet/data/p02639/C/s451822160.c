#include <stdio.h>
#include <stdlib.h>

int main(){
    int a, b, c, d, e;
    int out;
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    if (a == 0){
        out = 1;
    } else if(b == 0){
        out = 2;
    } else if(c == 0){
        out = 3;
    } else if(d == 0){
        out = 4;
    } else {
        out = 5;
    }
    printf("%d", out);
    return 0;
}