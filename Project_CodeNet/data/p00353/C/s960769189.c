/*
 * ID: 0358
 */

#include <stdio.h>

int main(void)
{
    int mine, friends, book;
    scanf("%d %d %d", &mine, &friends, &book);

    if (mine >= book)
        puts("0");
    else if (mine + friends >= book)
        printf("%d\n", book - mine);
    else
        puts("NA");

    return 0;
}

