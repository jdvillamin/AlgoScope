#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include <cmath>
#include <bitset>
#include <complex>
#include <functional>
#include <numeric>
#include <iomanip>

// output
#define SPBR(w, n) std::cout<<(w + 1 == n ? '\n' : ' ');
#define YES cout << "YES" << endl
#define Yes cout << "Yes" << endl
#define NO cout << "NO" << endl
#define No cout << "No" << endl
// utility
#define ALL(i) (i).begin(), (i).end()
#define FOR(i, a, n) for(int i=(a);i<(n);++i)
#define RFOR(i, a, n) for(int i=(n)-1;i>=(a);--i)
#define REP(i, n) for(int i=0;i<int(n);++i)
#define RREP(i, n) for(int i=int(n)-1;i>=0;--i)
#define IN(a, x, b) (a<=x && x<b)
#define OUT(a, x, b) (x<a || b<=x)
template<class T> inline T chmax(T & a, const T b) { return a = (a < b) ? b : a; }
template<class T> inline T chmin(T& a, const T b) { return a = (a > b) ? b : a; }

// type/const
#define int ll
using ll = long long;
using ull = unsigned long long;
using ld = long double;
const int MOD = 1000000007;
/* const int MOD = 998244353; */
const int INF = 1e18;
const double PI = acos(-1);

using namespace std;
struct INIT { INIT(){
  cin.tie(0); ios::sync_with_stdio(false);
  cout << fixed << setprecision(10);
}}INIT;

using P = pair<int, int>;
using Edge = pair<int, P>;

signed main() {
  int N, M, S;
  cin >> N >> M >> S;

  vector<vector<Edge>> graph(N);
  REP(i, M){
    int u, v, a, b;
    cin >> u >> v >> a >> b;
    u--; v--;
    graph[u].emplace_back(Edge(v, make_pair(a, b)));
    graph[v].emplace_back(Edge(u, make_pair(a, b)));
  }

  vector<int> c(N), d(N);
  REP(i, N) cin >> c[i] >> d[i];

  const int MAX = 2500;
  chmin(S, MAX);

  vector<vector<int>> dp(N, vector<int>(MAX+1, INF));
  dp[0][S] = 0;

  priority_queue<Edge, vector<Edge>, greater<Edge>> q;
  q.push({0, {0, S}});

  while(!q.empty()){
    auto p = q.top(); q.pop();
    int time = p.first;
    int v = p.second.first;
    int s = p.second.second;
    if(time >= dp[v][s]) continue;

    if(s+c[v] <= MAX){
      if(chmin(dp[v][s+c[v]], time+d[v])){
        q.push({time+d[v], {v, s+c[v]}});
      }
    }

    for(auto e : graph[v]){
      if(s < e.second.first) continue;
      if(chmin(dp[e.first][s-e.second.first], time+e.second.second)){
        q.push({time+e.second.second, {e.first, s-e.second.first}});
      }
    }
  }

  FOR(i, 1, N){
    int ret = INF;
    REP(j, MAX) chmin(ret, dp[i][j]);
    cout << ret << "\n";
  }

  return 0;
}