#include<stdio.h>
#include<stdlib.h>

int main(int argc,char** argv)
{
	int a, b, x, y;
	scanf("%d%d",&a, &b);
	x = a + b;
	y = x / 2;
	if(x % 2 > 0){
		y++;
	}
	printf("%d\n",y);
	return(0);
}