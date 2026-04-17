#include<stdio.h>
int a[300]={0};
int main ()
{  char s[7];
    int ans=0,flag=1;
   for(int i=1;i<=6;i++)
     {
	 scanf("%c",&s[i]);
	     if(a[s[i]]==0) 
	       ans++,a[s[i]]++;
	    if(s[i]>='A'&&s[i]<='Z')
	       flag=0;
      }
      if(flag&&ans==4&&s[3]==s[4]&&s[5]==s[6])
         printf("YES");
    else   printf("NO");
    return 0;
}