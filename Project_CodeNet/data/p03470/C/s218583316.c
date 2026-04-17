#include<stdio.h>
int main(void){
	int i, N, d[101] = { 0 }, in, ans = 0;
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &in);
		d[in - 1] = 1;
	}
	for (i = 0; i < N; i++) {
		if (d[i] == 1) ans++;
	}
	printf("%d\n", ans);
    return 0;
}