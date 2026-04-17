#include<stdio.h>
 
int main(void)
{
	char a,b;
	scanf("%c %c",&a,&b);
	if(a>b)
    {
	printf(">\n");
    }
    else if(a<b)
    {
      printf("<\n");
    }
    else
    {
      printf("=\n");
    }  
	return 0;
} 