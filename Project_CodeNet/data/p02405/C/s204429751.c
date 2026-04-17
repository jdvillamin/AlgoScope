#include<stdio.h>

int main()
{
    int a, b, i, j;

    scanf("%d%d", &a, &b);

    if(a == b == 0) break;
    for(i=1; i<=a;i++){
	for(j=1; j<=b; j++){
	    if((a+b)%2  ==0) printf("#");
	    else printf(".");}
	printf("\n");
    }
    printf("\n");

    return 0;
}
