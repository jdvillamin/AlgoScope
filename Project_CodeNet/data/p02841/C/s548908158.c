#include<stdio.h>
int main(void)
{
  int month1,month2,day1,day2;
  char str[16];
  
  fgets(str,sizeof(str),stdin);
  sscanf(str,"%d %d",&month1,&day1);
  fgets(str,sizeof(str),stdin);
  sscanf(str,"%d %d",&month2,&day2);
  
  if(month1 == month2)
  {
    puts("0");
  }else
  {
    puts("1");
  }
  
  return 0;
}