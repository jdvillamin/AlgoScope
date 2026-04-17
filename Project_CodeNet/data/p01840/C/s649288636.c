/*
A2739.c
title:Delivery to a Luxurious House
@kankichi573
*/

#include <stdio.h>

int main()
{
  int n,m,t,a,i;
  int st,en,all;
  
  scanf("%d %d %d",&n,&m,&t);

  all=0;
  scanf("%d",&a);
  st=a-m,en=a+m;

  for(i=1;i<n;i++)
      {
	scanf("%d",&a);
	if(a>en+m)
	  {
	    all += (en-st); 
	    st=a-m,en=a+m;
	  }
	else
	en = a+m;
      }
  if(en < t)
    all += (en-st);
  else
    all += t-st;
  printf("%d",t-all);
  return(0);
}