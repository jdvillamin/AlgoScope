
#include <stdio.h>
int main(void)
{
	int i, n;
	char t[4];
	int c[4];
	for (i=0; i<4; ++i) c[i]=0;
	while (scanf("%d,%s", &n, t) != EOF) {
		switch (t[0]) {
			case 'A': if (t[1]=='B') c[2]++; else c[0]++; break;
			case 'B': c[1]++; break;
			case 'O': c[3]++; break;
		}
	}
	if (c[0] < 20) return 1;
	for (i=0; i<4; ++i) printf("%d\n", c[i]);
	return 0;
}