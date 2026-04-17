#include <stdio.h>

int main()
{
    int N,re = 0;
    char s[100000];
    scanf("%d",&N);
    scanf("%s",&s);
    for(int i = 0;i < N;i++)
    {
        if(s[i] == s[i+1])re--;
    }
    re += N;
    printf("%d",re);
    return 0;
}