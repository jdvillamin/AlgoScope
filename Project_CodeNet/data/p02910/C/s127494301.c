#include<stdio.h>
int main(void)
{
	int i=0;
	int cnt=0;
	char S[101];
	scanf("%s",S);
	do
	{
		if(i%2)
		{
			if(S[i]=='R' || S[i]=='U' || S[i]=='D')
			cnt=cnt+0;
			else
			cnt++;
		}
		else
		{
			if(S[i]=='L' || S[i]=='U' || S[i]=='D')
			cnt=cnt+0;
			else
			cnt++;
		}
		i++;
	}while(S[i]!='\0');
	if(cnt==0)
	printf("Yes");
	else
	printf("No");
	return 0;
}
