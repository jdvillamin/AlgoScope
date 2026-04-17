#include<stdio.h>
int left[100];
long long int solve(int n, int right) {
  long long int dp[100][21];
  int i, j, index;
  for (i = 0; i < 100; i ++) for (j = 0; j < 21; j ++) dp[i][j] = 0;
  dp[1][left[0]] = 1;
  for (i = 2; i <= n; i ++) {
    for (j = 0; j < 21; j ++) {
      index = j + left[i - 1];
      if (index < 21) dp[i][index] += dp[i - 1][j];
      index = j - left[i - 1];
      if (index > -1) dp[i][index] += dp[i - 1][j];
    }
  }
  return dp[n][right];
}
int main() {
  int n, right;
  int i;
  scanf("%d", &n);
  for (i = 0; i < n - 1; i ++) scanf("%d", &left[i]);
  scanf("%d", &right);
  printf("%lld\n", solve(n - 1, right));
  return 0;
}