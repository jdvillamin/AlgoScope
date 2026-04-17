#include<bits/stdc++.h>
using namespace std;
 
#define rep(i, a, n) for(int i=a; i<n; i++)
#define ll long long
#define all(x) begin(x), end(x)
#define toInt(x) (x - '0')
#define pll pair<ll, ll>
#define pli pair<ll, int>

const long long INF = 1LL<<60;
const int inf = 1 << 30;
const int mod = 1e9+7;


template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main(){
  int n, k;
  cin >> n >> k;
  vector<int> v(n+1);
  rep(i, 0, n+1){
    v[i] = i;
  }
  unordered_set<long long > st;
  vector<long long> s(n+1);
  s[0] = 0;
  rep(i, 1, n){
    s[i] = s[i-1] + v[i];
    // cout << s[i] << endl;
  }

  long long ans = 0;
  long long L, R;
  for (long long i=k; i<=n+1; i++){
    L = i * (i-1) / 2;
    R = i * (2 * n - i + 1) / 2;
    ans += (R - L + 1);
    ans %= mod;
  }
  cout << ans << endl;
}
