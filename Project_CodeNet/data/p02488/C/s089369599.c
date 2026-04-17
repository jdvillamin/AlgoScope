#include <stdio.h>
#include <string.h>

int main(void)
{
	int n, i, a;
	char s[2][21] ;
	scanf("%d", &n);
	
	scanf ("%s", s[1]);
	for (i = 0; i < n -1; i++){
		scanf("%s", s[0]);
		if (strcmp(s[0], s[1]) < 0) {
			strcpy(s[1], s[0]);
		}
	}
	printf("%s\n", s[1]);
	return(0);
}