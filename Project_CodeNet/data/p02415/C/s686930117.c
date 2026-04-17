#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main (void)
{
	char str1[1200];
	int i = 0;
	scanf("");
	fgets(str1 , 1300 , stdin);
	while(str1[i] != '\0')
	{
		if(str1[i] >= 'a' && str1[i] <= 'z')
		{
			str1[i] -= 32;
		}
		else if(str1[i] >= 'A' && str1[i] <= 'Z')
		{
			str1[i] += 32;
		}
		i++;
	}
	printf("%s" , str1);
 } 
