#include <stdio.h>

int
main(void)
{
	char a, b;
	scanf("%c %c", &a, &b);

	puts(a == b ? "H" : "D");
	return 0;
}
