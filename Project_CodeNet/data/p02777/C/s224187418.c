#include <stdio.h>
#include <strings.h>
int main() {
    int a,b;
    char s[10],t[10],u[10];
    scanf("%s %s", &s, &t);
    scanf("%d %d", &a, &b);
    scanf("%s", &u);
    if(strcmp(s,u) == 0) {
        a--;
    } else if(strcmp(t,u) == 0) {
        b--;
    }
    printf("%d %d\n", a, b);
    return 0;
}