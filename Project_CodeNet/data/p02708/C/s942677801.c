#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const long long MOD = 1000000007;
const int MAX_C = 20001;
long long Com[MAX_C][MAX_C];

int main()
{
  ll n, k;
  cin >> n >> k;
  vector<ll> dp = {};
  dp.resize(n, 0);

  // 累積和
  for (auto i = 0; i < n + 1; i++)
  {
    if (i != 0)
    {
      dp[i] = (dp[i - 1] + i) % MOD;
    }
  }

  ll total = 0;
  for (auto i = k; i < n + 1; i++)
  {
    auto max = dp[n] - dp[n - i];
    auto min = dp[i - 1];
    auto val = max - min + 1;
    if (val < 0)
      val += MOD;
    total += val;
    total %= MOD;
  }

  total += 1;
  total %= MOD;
  cout << total << endl;
  return 0;
}
