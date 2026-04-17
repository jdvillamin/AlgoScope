// AOJ 0272: The Lonely Girl's Lie
// 2017.10.14 bal4u@uu
// 2018.1.2

#include <stdio.h>
#include <string.h>

int n;
int a[40003], b[40003];
int f[100002];

//#define getchar_unlocked()  getchar()
int in()
{
	int n, c;

	c = getchar_unlocked();
	n = 0;
	do n = (n<<3)+(n<<1) + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

void getdata(int *a)
{
	int i, j, k, max;
	int *aa;

	memset(f, 0, sizeof(f));
	max = 0, k = n;
	while (k--) {
		i = in(), f[i]++; if (i > max) max = i;
	} 
	for (k = n, aa = a, i = max; k; i--) if (f[i]) {
		j = f[i], k -= j; while (j--) *aa++ = i;
	}
}

int main()
{
	int i, k, ans;

	while (n = in()) {
		getdata(a);
		getdata(b);

		ans = n;
		i = 0;
		for (k = 0; k < n; k += 2) {
			if (a[k] > b[i++]) { ans = k + 1; break; }
		}
		if (ans == n) puts("NA");
		else printf("%d\n", ans);
	}
	return 0;
}

