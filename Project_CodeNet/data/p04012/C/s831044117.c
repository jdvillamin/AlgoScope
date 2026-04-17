#include<stdio.h>
int main()
{
	int i,j,t[26] = {0},flag = 0;
	char s[101],s1[27] = {'a','b','c','d','e','f','h','i','j','k','l','m','n','o','p','q','r','i','s','t','u','v','w','x','y','z'};
	scanf("%s",&s);
	for(i = 0;s[i] != '\0';i++)
	{
		for(j = 0;j < 26;j++)
		{
			if(s[i] == s1[j])
			{
				t[j]++;
			}
		}
	}
	for(i = 0;i < 26;i++)
	{
		if(t[i] % 2 != 0)
		{
			flag = 1;
			break;
		}
	}
	if(flag == 1)
		printf("NO\n");
	else
		printf("YES\n");
	return 0;
}

