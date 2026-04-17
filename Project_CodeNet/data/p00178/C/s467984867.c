/*
AizuOnline A0178
Title
*/
#include <stdio.h>
#include <string.h>
char ban[5000];
int N;
//
int cnt5bits(int x) //0~31
{
  int i,s;
  s=0;
  for(i=0;i<5;i++)
    if((1<<i)&x)
      s++;
  return(s);
}


void show()
{
  int i,s;
  s=0;
  for(i=0;i<20 && ban[i];i++)
    {
#ifdef DEBUG
      printf("%d:",ban[i]);
#endif
      s += cnt5bits(ban[i]);
    }
#ifdef DEBUG
  printf("\n");
#endif
  printf("%d\n",s);
}
main()
{
  int i,j,k,d,l,p,v,top;

  while(EOF!=scanf("%d ",&N) && N)
    {
      memset(ban,0,1000);
      for(i=0;i<N;i++)
	{
	  scanf("%d %d %d",&d,&l,&p);
	  if(d==1)
	    v=((1<<l)-1)*(1<<(6-l-p));
	  else
	    v=(1<<(5-p));

	  top=0;                  //calc highest pos
	  while(ban[++top]);
	  j=top+1;
	  while((v & ban[j-1])==0 && j>0)
	    {  j--;
	    }	  
	  ban[j]|=v;
      
	  if(d==2)
	    for(k=1;k<l;k++)
	      ban[j+k]|=v;

	  top=0;
	  while(ban[++top]);
	  

	  for(k=top;k>=0;k--)
	    if(ban[k]==31)
	      {
		l=k;
		do
		  {
		    ban[l]=ban[l+1];
		    l=l+1;
		  }
		while(ban[l] && l<5000);
	      }
	  //show();
	}
      show();
    }     
return(0);
}