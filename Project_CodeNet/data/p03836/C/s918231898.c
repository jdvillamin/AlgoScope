#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
 
#define sl(x) scanf("%ld", &x)
#define ss(x) scanf("%s", x)
#define pl(x) printf("%ld\n", x)
#define ps(x) printf("%s\n", x)
 
#define INF 100000000000
#define MOD 1000000007
 
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
 
int main() {
	long sx, sy, tx, ty;
	long idx = 0;
	long i, j;
	long tmp;
	char ans[10000];
	
	sl(sx); sl(sy); sl(tx); sl(ty);
	
	ans[idx++] = 'D';
	for(i=0;i<(tx-sx);i++) ans[idx++] = 'R';
	ans[idx++] = 'R';
	for(i=0;i<(ty-sy);i++) ans[idx++] = 'U';
	ans[idx++] = 'U';
	ans[idx++] = 'L';
	ans[idx++] = 'U';
	for(i=0;i<(tx-sx);i++) ans[idx++] = 'L';
	ans[idx++] = 'L';
	for(i=0;i<(ty-sy);i++) ans[idx++] = 'D';
	ans[idx++] = 'D';
	ans[idx++] = 'R';
	for(i=0;i<(tx-sx);i++) ans[idx++] = 'R';
	for(i=0;i<(ty-sy);i++) ans[idx++] = 'U';
	for(i=0;i<(tx-sx);i++) ans[idx++] = 'L';
	for(i=0;i<(ty-sy);i++) ans[idx++] = 'D';
	
	ans[idx++] = '\0';
	
	ps(ans);
	
	return 0;
}