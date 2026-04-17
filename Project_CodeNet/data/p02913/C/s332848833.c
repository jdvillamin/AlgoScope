#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
int acs(const void *a, const void *b){return *(int*)a - *(int*)b;} /* 1,2,3,4.. */
int des(const void *a, const void *b){return *(int*)b - *(int*)a;} /* 8,7,6,5.. */
#define min(a,b) (a < b ? a: b)
#define max(a,b) (a > b ? a: b)

#define MAXN (5000)
#define MOD (998244353)

char s[MAXN+1];
int dp[MAXN+1][MAXN+1];

int main(void)
{
    int n;
    scanf("%d",&n);
    scanf("%s",s);

    int ans = 0;
    for(int i=n-1;i>=0;i--) for(int j=n-1;j>=0;j--)
    {
        if(s[i]==s[j])
        {
            dp[i][j] = dp[i+1][j+1]+1;
            int score = min(abs(i-j),dp[i][j]);
            ans = max(ans, score);
        }
    }
 
    printf("%d\n", ans);
    return 0;
}
