#include <stdio.h>
#include <string.h>

int main()
{
    char S[10], T[10];
    int i, n = 0;

    scanf("%s", S);
    scanf("%s", T);

    for (i = 0; i < strlen(S); i++)
    {
        if (S[i] == T[i])
            n++;
    }

    if (n + 1 == strlen(T))
    {
        puts("Yes");
    }
    else
    {
        puts("No");
    }
    return 0;
}