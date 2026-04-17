#include <stdio.h>
#include<string.h>

int main() {
	int N, a = 0, i;
	char S[2000];

	if (fgets(S, 2000, stdin) != 0) {
		N = strlen(S);
		S[N] = '\0';
		for (i = 0;i < N;) {
			if (S[i] == 'B'&&S[i + 1] == 'W') {
				S[i] = 'W';
				S[i + 1] = 'B';
				++a; i=0;
				continue;
			}
			i++;
		}

		printf("%d\n", a);
	}

	return 0;
}