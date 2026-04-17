#include <stdio.h>
#include <string.h>
int main(void)
{
    char s[2050], t[2050];
    int i, j;
    int len;
    scanf("%s\n%s", s, t);
    len = strlen(s);
    for(i = 0; i < len - 1; i++) {
        for(j = i + 1; j < len; j++) {
            if((s[i] == s[j] && t[i] != t[j]) || (t[i] == t[j] && s[i] != s[j])) {
                printf("No\n");
                return 0;
            }
        }
    }
    printf("Yes\n");   
    return 0;
}
