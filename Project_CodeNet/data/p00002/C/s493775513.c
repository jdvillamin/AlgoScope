#include<stdio.h>
int main(void){
    int a, b, c, n;
    
    while(scanf("%d %d", &a, &b) != EOF){
        c=a+b;
        n=0;
        do{
            n++;
            c /= 10;
        }while(c);
        
        printf("%d\n", n);
    }
    return 0;
}
    
