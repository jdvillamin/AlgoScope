#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
long long a[10010],b[10010],cnt;
int N;
int read()
{
	static int x;
	static char ch;
	x = 0;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(;ch>='0'&&ch<='9';ch=getchar()) x = x * 10 + ch - '0';
	return x;
}
int main()
{
	N = read();
	for (int i = 1;i<=N;++i) a[i] = read();
	for (int i = 1;i<=N;++i) b[i] = read();
	for (int i = 1;i<=N;++i) 
		if  (a[i]>=b[i]) cnt-=a[i]-b[i];
		else cnt += (b[i] - a[i])>>1;
	if (cnt<0) puts("No");else puts("Yes");
	return 0;
}