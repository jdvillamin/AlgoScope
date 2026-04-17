#include<stdio.h>
int main(void)
{
	int S,h,m,s;
	S=46979;
    ((S>=0)&&(S<86400));
	h = S/3600;
	S %= 3600;
	m = S/60;
	S %= 60;
	s = S;
	
	return 0;											
}