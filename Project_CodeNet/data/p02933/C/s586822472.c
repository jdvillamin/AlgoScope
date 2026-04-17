#include<stdio.h>
int main()
{
    int a;
    char str[50];
    scanf("%d %s",&a,str);
    if(a>=3200)
    {
        printf("%s",str);
    }
    else if(a<3200)
    {
        printf("red\n");
    }
    return 0;
}
