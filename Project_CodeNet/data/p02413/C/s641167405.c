#include <stdio.h>
 
int main(void)
{
	int a[101][101] = {0};
	int b[101] = {0};
	int d[101] = {0};
	int i,j,r,c;
	int x;
	int e = 0;

	scanf("%d %d" , &r,&c);
	for(j=0; j<r; j++) {
	for(i=0; i<c; i++) {
	scanf("%d",&x);
	a[j][i] = x;
	}
	}
	for(j=0; j<r; j++){
	for(i=0; i<c; i++) {
	b[i] += a[j][i];
	}
	}
	for(j=0; j<r; j++){
	for(i=0; i<c; i++){
		d[j] += a[j][i];
	}
}
	for(j=0; j<r; j++) {
    	for(i=0; i<c; i++) {
	printf("%d ",a[j][i]);
	}
	printf("%d\n", d[j]);
	}
	for(i =0; i<c; i++) {
	printf("%d " ,b[i]);
	e += b[i];
	}
printf("%d\n", e);
 
return 0;
}
