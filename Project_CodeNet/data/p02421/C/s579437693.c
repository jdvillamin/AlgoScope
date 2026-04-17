#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(void) {
    int a, b;
    int n; scanf("%d", &n);
 
    a = 0, b = 0;
 
    while(n--) {
        int res;
        char s1[101];
        char s2[101];
        scanf(" %s", s1);
        scanf(" %s", s2);
 
        res = strcmp(s1, s2);
        if(res > 0) a += 3;
        else if(res < 0) b += 3;
        else a++, b++;
    }
 
    printf("%d %d\n", a, b);
 
    return EXIT_SUCCESS;
}
