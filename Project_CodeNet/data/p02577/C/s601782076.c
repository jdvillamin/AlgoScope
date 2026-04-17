#include <stdio.h>

char N[271828];

int main(void) {
	int i, asumisu = 0;
	if (scanf("%271827s", N) != 1) return 1;
	for (i = 0; N[i] != '\0'; i++) {
		asumisu = (asumisu + (N[i] - '0')) % 9;
	}
	puts(asumisu == 0 ? "Yes" : "No");
	return 0;
}
