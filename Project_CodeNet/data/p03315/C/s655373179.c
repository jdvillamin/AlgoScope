#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char s[1000];
    int a,b,i,c;
    while(~scanf("%s",s))
    {
        b=0;
        a=strlen(s);
        for(i=0;i<a;i++)
        {
            if(s[i]=='+')
                b=b+1;
            else
                b=b-1;
        }
        printf("%d\n",b);
    }
    return 0;
}
