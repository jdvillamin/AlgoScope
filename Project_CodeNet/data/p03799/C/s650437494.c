#include<stdio.h>
#include<math.h>
__int64 a,b;
int main(){
	while(scanf("%I64d %I64d",&a,&b)==2)
	{
		__int64 sum=0;
		if(b/2>a)
		{
			sum+=a;
			b-=2*a;
			sum+=b/4;
			printf("%I64d\n",sum);
		}
		else
		{
			sum+=b/2;
			printf("%I64d\n",sum);
		}
	}
	return 0;
}