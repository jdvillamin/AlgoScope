#include <stdio.h>


int main(void){
    int n;
    scanf("%d", &n);
    char s[n+1];
    scanf("%s", s);
    int flag = 0;
    int count = 0;
    for(int i = 0; i< n; i++){
        if(flag == 0 && s[i] == '#'){
            flag = 1;
        }
        if(flag == 1 && s[i] == '.'){
            count += 1;
        }
    }
    printf("%d\n", count);
    return 0; 
}