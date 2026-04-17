#include <stdio.h>

int main(void){
    char S[2000001];
    scanf("%s", S);
    long int s=0;
    long int bs=0;
    long int i=0;
    for (i = 0; S[i+1]!='\0'; i++) {
        if (S[i] == 'B'){
            bs++;
        } else {
            s = s + bs;
        }
    }
    printf("%d\n", s);
    return 0;
}
