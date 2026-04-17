#include <bits/stdc++.h> // ver2.6.3
//#include <complex.h> // FFT用
//#include <boost/math/tools/minima.hpp>
//#include <boost/multiprecision/cpp_int.hpp>
//using boost::math::tools::brent_find_minima;//fmin(f,L,R,100)で最小値をmp(x,min)で取得
//using boost::multiprecision::cpp_int;//cpp_int (任意の長さのint)
#define fmin brent_find_minima
#define int long long
#define endl "\n"
#define ALL(v) (v).begin(),(v).end()
#define Vi vector<int>
#define VVi vector<Vi>
#define VVVi vector<VVi>
#define Vm vector<mint>
#define Vs vector<string>
#define Vd vector<double>
#define Pii pair<int,int>
#define Pdd pair<double,double>
#define VPii vector<Pii>
#define Tiii tuple<int,int,int>
#define VTiii vector<Tiii>
#define PQi priority_queue<int>
#define PQir priority_queue<int,vector<int>,greater<int>>
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define itos to_string
#define stoi stoll
#define FI first
#define SE second
#define cYES cout<<"YES"<<endl
#define cNO cout<<"NO"<<endl
#define cYes cout<<"Yes"<<endl
#define cNo cout<<"No"<<endl
#define cyes cout<<"yes"<<endl
#define cno cout<<"no"<<endl
#define sortr(v) sort(v,greater<>())
#define rep(i,a,b) for(int i=a;i<b;i++)
#define repeq(i,a,b) for(int i=a;i<=b;i++)
#define repreq(i,a,b) for(int i=a;i>=b;i--)
#define dem(a,b) ((a+b-1)/(b))
#define Vin(a) rep(iI,0,a.size())cin>>a[iI]
#define INF 3000000000000000000 // 3.0*10^18(MAXの1/3くらい)
#define MAX LLONG_MAX
#define PI 3.141592653589793238462
#define MOD 1000000007 // 10^9 + 7
//int MOD = 998244353; // caseに応じて変える必要がある場合はこちら
const double EPS = 1e-10;

using namespace std;

struct mint{int x;mint(int x=0):x((x%MOD+MOD)%MOD){}
mint operator-()const{return mint(-x);}
mint& operator+=(const mint a){if((x+=a.x)>=MOD)x-=MOD;return*this;}
mint& operator-=(const mint a){if((x+=MOD-a.x)>=MOD)x-=MOD;return*this;}
mint& operator*=(const mint a){(x*=a.x)%=MOD;return*this;}
mint operator+(const mint a)const{return mint(*this)+=a;}
mint operator-(const mint a)const{return mint(*this)-=a;}
mint operator*(const mint a)const{return mint(*this)*=a;}
mint pow(int t)const{if(!t)return 1;mint a=pow(t>>1);a*=a;if(t&1)a*=*this;return a;}
mint inv()const{return pow(MOD-2);}
mint& operator/=(const mint a){return*this*=a.inv();}
mint operator/(const mint a)const{return mint(*this)/=a;}};
istream& operator>>(istream& is, const mint& a) {return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) {return os << a.x;}

/* デバッグ用 */
template <typename T> // vector出力
ostream& operator<<(ostream& os,const vector<T> &V){int N=V.size();
rep(i,0,N-1){os<<V[i]<<' ';}os<<V[N-1];return os;}
template <typename T> // vector<vector>出力
ostream& operator<<(ostream& os,const vector<vector<T>> &V){
int N=V.size();rep(i,0,N-1)cout<<V[i]<<endl;cout<<V[N-1];return os;}
template <typename T,typename S> // pair出力
ostream& operator<<(ostream& os, pair<T,S> const&P){os<<P.FI<<' '<<P.SE;return os;}
template <typename T> // set出力
ostream& operator<<(ostream& os,set<T> &S){auto it=S.begin();while(it!=S.end()){
os<<*it;if(next(it,1)!=S.end())os<<' ';it++;};return os;}
template <typename T> // deque出力
ostream& operator<<(ostream& os, deque<T> &q){for(auto it=q.begin();it<q.end();it++){
os<<*it;if(it+1!=q.end())os<<" ";}return os;}



/****************************** START ******************************/

signed main() {
  cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);cout<<fixed<<setprecision(12);
  double r;
  cin >> r;
  cout << (2*PI*r) << endl;
  return 0;
}
