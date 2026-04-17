// AOJ 0322: Slates
// 2018.1.1 bal4u@uu

#include <stdio.h>
#include <string.h>

typedef unsigned long long ull;
#define HASHSIZ 100019

ull hash[HASHSIZ+2], *hashend = hash+HASHSIZ;

int lookup(ull a)
{
	ull *p = hash + a % HASHSIZ;
	while (*p) {
		if (*p == a) return 1;
		if (++p == hashend) p = hash;
	}
	return 0;
}

void insert(ull a)
{
	ull *p = hash + a % HASHSIZ;
	while (*p) {
		if (*p == a) return;
		if (++p == hashend) p = hash;
	}
	*p = a;
}

#define M1     29
#define HEAD_S 1
#define TAIL_S 2
#define QMARK  4
#define QNUM   50004

int wlen[50002];
ull f1[50005][202];
ull powl[202];
char buf[202], *p;

int in()
{
	int n = 0;
	while (*p >= '0') n = 10*n + (*p++ & 0xf);
	p++;
	return n;
}

void rollingHash(int i, char *s, int w)
{
	int j;
	char c;

	f1[i][0] = 0;
	for (j = 0; j < w; j++) {
		c = *s++ - ('a'-1);
		f1[i][j+1] =  f1[i][j] * M1 + c;
	}
}

ull a;
#define calc(i,l,r) (a=f1[i][r]-f1[i][l]*powl[(r)-(l)])

int main()
{
	int n, m, i, j, w, w1, w2, f, ans;
	ull u1, v1;
	char *p2;
	
	powl[0] = 1;
	for (i = 0; i < 202; i++) powl[i+1] =  powl[i] * M1;

	fgets(p=buf, 20, stdin);
	n = in(), m = in();
	for (i = 0; i < n; i++) {
		fgets(p=buf, 202, stdin);
		w = strlen(p)-1;
		if (*(p+w) < ' ') *(p+w) = 0; else w++;
		wlen[i] = w;

		rollingHash(i, p, w);
		insert(f1[i][w]);
	}

	for (i = 0; i < m; i++) {
		f = 0;
		fgets(p=buf, 202, stdin);

		if (*p == '*') p++, f |= HEAD_S;
		while (*p >= ' ') {
			if      (*p == '?') f |= QMARK, p2 = p, w1 = p2-buf;
			else if (*p == '*') f |= TAIL_S;
			p++;
		}
		*p = 0;
		if (f & QMARK) *p2++ = 0, w = p-p2; 
		else w = p-buf;

		ans = 0;
		if (!f) {
			rollingHash(QNUM, buf, w);
			if (lookup(f1[QNUM][w])) ans++;
		} else if (f & QMARK) {
			if (f & HEAD_S) {
				w1--;
				rollingHash(QNUM, buf+1, w1), u1 = f1[QNUM][w1];
				w2 = w;
				rollingHash(QNUM, p2,    w2), v1 = f1[QNUM][w2];
				for (j = 0; j < n; j++) {
					w = wlen[j];
					if (w <= w1+w2) continue;
					calc(j, w-w2-w1-1, w-w2-1); if (a != u1) continue;
					calc(j, w-w2, w); if (a == v1) ans++;
				}
			} else if (f & TAIL_S) {
				rollingHash(QNUM, buf, w1), u1 = f1[QNUM][w1];
				w2 = w-1;
				rollingHash(QNUM, p2,  w2), v1 = f1[QNUM][w2];
				for (j = 0; j < n; j++) {
					w = wlen[j];
					if (w <= w1+w2) continue;
					calc(j, 0,    w1); if (a != u1) continue;
					calc(j, w1+1, w1+w2+1); if (a == v1) ans++;
				}
			} else {
				rollingHash(QNUM, buf, w1), u1 = f1[QNUM][w1];
				w2 = w;
				rollingHash(QNUM, p2,  w2), v1 = f1[QNUM][w2];
				for (j = 0; j < n; j++) {
					w = wlen[j];
					if (w != w1+w2+1) continue;
					calc(j, 0,   w1); if (a != u1) continue;
					calc(j, w1+1, w); if (a == v1) ans++;
				}
			}
		} else {
			if (f & HEAD_S) {
				rollingHash(QNUM, buf+1, --w), u1 = f1[QNUM][w];
				for (j = 0; j < n; j++) {
					w1 = wlen[j];
					if (w1 >= w) { calc(j, w1-w, w1); if (a == u1) ans++; }
				}
			} else if (f & TAIL_S) {
				rollingHash(QNUM, buf, --w), u1 = f1[QNUM][w];
				for (j = 0; j < n; j++) {
					if (wlen[j] >=  w) { calc(j, 0, w); if (a == u1) ans++; }
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

