#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define MAXSIZE 100001
int main(int argc, char *argv[]) {
//	char res[4];
	char N[MAXSIZE];
	scanf("%s", N);
	
	int i = 0;
	int sum = 0;
	for (i = 0; i < strlen(N); ++i)
	{
		sum = sum + (N[i] - '0');
	}
	if (N[0] - '0' == 0 && strlen(N) == 1) 
	{
		printf("%s", "YES");
		return;
	}
	
	if (sum % 9 == 0)
	{
		printf("%s", "YES");
		
		return ;
	}
	else 
	{
		printf("%s", "NO");
	}
	
	
	return 0;
}