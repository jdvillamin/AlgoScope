#include <stdio.h>

#define MOD_BY 1000000007

int add(int a, int b) {
	return a + b - (a + b >= MOD_BY ? MOD_BY : 0);
}

int sub(int a, int b) {
	return b == 0 ? a : add(a, MOD_BY - b);
}

int mul(int a, int b) {
	int r = 0;
	while (b > 0) {
		if (b & 1) r = add(r, a);
		a = add(a, a);
		b >>= 1;
	}
	return r;
}

int pou(int a, int b) {
	int r = 1;
	while (b > 0) {
		if (b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

int inv(int a) {
	return pou(a, MOD_BY - 2);
}

int d2;

/*
https://www.kwansei.ac.jp/hs/z90010/sugakua/suuretu/tousasum/tousasum.htm

Sn = n(a+l) / 2
*/
int wa(int a, int l) {
	int n = l - a + 1;
	return mul(mul(n, add(a, l)), d2);
}

int main(void) {
	int N, K;
	int m;
	int kotae = 0;
	d2 = inv(2);
	if (scanf("%d%d", &N, &K) != 2) return 1;
	for (m = K; m <= N + 1; m++) {
		int sita, ue;
		/* 一番下m個 */
		sita = wa(0, m - 1);
		/* 一番上m個 */
		ue = wa(N - m + 1, N);

		kotae = add(kotae, add(sub(ue, sita), 1));
	}
	printf("%d\n", kotae);
	return 0;
}

/*

m個選ぶ時、一番下m個～一番上m個まで全て1個ずつ動かして作れる

*/
