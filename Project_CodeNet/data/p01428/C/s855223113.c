#include <stdio.h>

#define SIZE_MAX 8

typedef unsigned int ui;

char s[SIZE_MAX][SIZE_MAX + 1];

int isMami;
int remain;

ui fucker;

int isvalidcoor(int n){
	return (0 <= n) && (n < SIZE_MAX);
}

char cake(){
	return (isMami ? 'o' : 'x');
}

void progress(int h, int w){
	int vects[8][2] = {
		{-1, -1},
		{-1,  0},
		{-1, +1},
		{ 0, -1},
		{ 0, +1},
		{+1, -1},
		{+1,  0},
		{+1, +1}
	};
	int v;
	char c = cake();
	s[h][w] = c;
	// printf("fucker: %d", fucker);
	for (v = 0; v < 8; v++) {
		int i, j;
		int isLinable = fucker & 1;
		fucker /= 2;
		if (!isLinable) continue;
		i = h;
		j = w;
		// printf("%d ", v);
		for (;;) {
			i += vects[v][0];
			j += vects[v][1];
			if (isvalidcoor(i) && isvalidcoor(j)) {
				if (s[i][j] == c) {
					break;
				} else {
					s[i][j] = c;
				}
			} else {
				break;
			}
		}
	}
	// putchar('\n');
	return;
}

ui isvalidturn(int h, int w){
	ui n = 0;
	char c;
	int vects[8][2] = {
		{-1, -1},
		{-1,  0},
		{-1, +1},
		{ 0, -1},
		{ 0, +1},
		{+1, -1},
		{+1,  0},
		{+1, +1}
	};
	int v;
	char k = cake();
	ui raper = 0;
	for (v = 0; v < 8; v++) {
		int i, j;
		int m = 0;
		i = h;
		j = w;
		for (;;) {
			i += vects[v][0];
			j += vects[v][1];
			c = s[i][j];
			if (!isvalidcoor(i) || !isvalidcoor(j) || c == '.') {
				m = 0;
				break;
			} else if (c == k) {
				raper |= (1 << v);
				break;
			} else {
				m++;
			}
		}
		n += m;
	}
	// printf("r = %d\n", raper);
	// printf("n = %d\n", n);
	return (n << 8) + raper;
}

int isBetter(int h, int w, int i, int j){
	if (isMami) {
		return ((i < h) || (i == h && j < w));
	} else {
		return ((i > h) || (i == h && j > w));
	}
}

int virtuoso(){
	int h = 0, w = -1;
	ui n = 0;
	int i, j;
	ui f;
	for (i = 0; i < SIZE_MAX; i++)
		for (j = 0; j < SIZE_MAX; j++) {
			ui m;
			if (s[i][j] != '.')
				continue;
			// printf("%d %d", i, j);
			m = isvalidturn(i, j);
			f = m % (1 << 8);
			m = m >> 8;
			// printf("f = %d\n", f);
			// printf("m = %d\n", m);
			if (m > n || (m == n && isBetter(h, w, i, j))) {
				h = i, w = j;
				n = m;
				fucker = f;
			}
		}
	return(n ? (h * SIZE_MAX + w) : SIZE_MAX * SIZE_MAX);
}

int output(){
	int i;
	for (i = 0; i < SIZE_MAX; i++) {
		puts(s[i]);
	}
	return! 810;
}

int hideous(){
	int n;
	int is_collapse = 2;
	while (is_collapse && remain) {
		// printf("%d %d", is_collapse, remain);
		isMami ^= 1;
		n = virtuoso();
		// printf("%d %d\n", n / 8, n % 8);
		// printf("%d\n", fucker);
		if (n == SIZE_MAX * SIZE_MAX) {
			is_collapse--;
			continue;
		}
		is_collapse = 2;
		progress(n / 8, n % 8);
		remain--;
		// output();
		// putchar('\n');
	}
	return output();
}

int main(void){
	int i;
	for (i = 0; i < SIZE_MAX; i++) {
		scanf("%s", s[i]);
		{
			char *c = s[i];
			while (*c) {
				if (*c == '.')
					remain++;
				c++;
			}
		}
	}
	hideous();
	return! 114514;
}