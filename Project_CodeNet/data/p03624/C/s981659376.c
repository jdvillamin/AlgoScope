#include<stdio.h>

int main()
{
    unsigned long long len,i,count[26],k,l,a[26];
    for(i=0;i<26;i++)count[i]=0;
    char s[1000000];
    scanf("%s",s);
    len=strlen(s);
    for(i=0;i<len;i++){
        count[s[i]-97]++;
    }
    for(i=0;i<26;i++){
        k=1;if(count[i]==0){k=5;break;}
    }
    if(k==1){printf("None\n");return 0;}
    for(i=0;i<26;i++){
        if(count[i]==0){printf("%c\n",i+97);return 0;}
    }

}
