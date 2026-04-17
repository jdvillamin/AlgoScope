#include <stdio.h>

int main(void) {
int a=0,b=0,c=0;
scanf("%d %d %d",&a,&b,&c);
if(b>=a*c)
printf("%d",c);
else{
c=b/c;
printf("%d",c);
}
	return 0;
}

