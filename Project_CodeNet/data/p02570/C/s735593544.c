#include <stdio.h>

int main(void)
{

    int d, s, t;

    scanf("%d %d %d", &d, &s, &t);

    if (d / s <= t)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
    return 0;
}