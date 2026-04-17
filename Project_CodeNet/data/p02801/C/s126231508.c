#include<stdio.h>
 
int main()
{
    int n,count;
 
    scanf("%d",&n);

    char s[n];
    
    scanf("%s",s);
    
    count=0;

    for (int i=0;i<n-2;i++) {
        if (s[i]=='A' && s[i+1]=='B' && s[i+2]=='C') {
            count++;
        }
    }
    printf("%d",count);
    return 0;
}