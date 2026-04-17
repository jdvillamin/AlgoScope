#include<stdio.h>
#include<string.h>
int main()
{
    int len,maxsum,flag,i;
    char str[50];
    while(gets(str)!=NULL)
    {
        flag=1;
        len = strlen(str);
        for(i=1;i<len;i++)
        {
            if(str[i]<'9')
            {
                flag=0;
                break;
            }
        }
        if(flag==0)
            maxsum=9*(len-1)-1+str[0]-'0';
            else
                maxsum=9*(len-1)+str[0]-'0';
        printf("%d\n",maxsum);
    }
    return 0;
}