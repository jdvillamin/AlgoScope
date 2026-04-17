#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    char stc[100];
    int i;
    int m = 0;
    int total = 0;
    long len;
    while (scanf("%s", stc) != EOF) {
        len = strlen(stc);
        for (i = 0; i < len; i++) {
            if (isdigit(stc[i])) {
                m = m * 10 + stc[i] - '0';
            }
            else {
                total += m;
                m = 0;
            }
        }
    }
    printf("%d\n", total);
    return 0;
}