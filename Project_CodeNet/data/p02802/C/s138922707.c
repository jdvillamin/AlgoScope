#include<stdio.h>
int main()
{
  int p,s,i,n,a=0,w=0;
  char ch[100000][3],t[3];
  scanf("%d%d",&p,&s);
  if(s==0)
	  ;
  else
  {
  i=0;
  do
  {
    scanf("%d",&n);
    if(ch[n][0]!='A')
    {
      scanf("%s",ch[n]);
      if(ch[n][0]=='A')
        a++;
      else if(ch[n][0]=='W')
        w++;
    }
    else
      scanf("%s",t);
    i++;
  }while(i<s);
  }
  printf("%d %d",a,w);
  return 0;
}