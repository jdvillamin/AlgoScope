#include<stdio.h>
#include<string.h>

int main(void)
{
    int n,i,j;
    char s[101];

    j=0;
    scanf("%d%s",&n,s);
    n=strlen(s);
    if(n%2==0){
        for(i=0;i<n/2;i++)
            if(s[i]==s[i+n/2]) j++;
        if(j==n/2) printf("Yes\n");
        else printf("No\n");
    }
    else printf("No\n");
    return 0;
}