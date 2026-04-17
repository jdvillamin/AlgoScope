#include <stdio.h>

int main() {
	int helt;
	int atk;
	scanf("%d%d", &helt, &atk);
	int nmbr = helt/atk;
	nmbr >= 1 ? printf("%d\n", nmbr+1) : printf("%d\n", 1);
	
	return 0;
}