#include<stdio.h>

int main(){
	char a[105];
	int n, x = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%c", &a[i]);
		if(a[i] == 'I')
			x ++;
			else if(a[i] == 'D') x --;
	}
	if(x < 0) x = 0;
	printf("%d\n", x);
}



