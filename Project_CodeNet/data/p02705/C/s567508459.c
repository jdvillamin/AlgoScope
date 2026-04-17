#include <bits/stdc++.h>
typedef long long int ll;
typedef long double ld;
using namespace std;
ll mod=1e18;
const ll inf = (ll)1e17;
const ld eps = 1e-12;
const ld PI = 3.14159265358979323846;
ll mul(ll a, ll b, ll m = mod) { return (ll)(a * b) % m;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
ll powmod(ll a,ll b){ll res=1;a%=mod;assert(b>=0);for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res%mod;}
long modInverse(long a) {return powmod(a, mod-2);}
ll my_rand(){ll a=rand();ll b=rand();return (a*RAND_MAX+1)+b;}
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()


int main(){
    ios::sync_with_stdio(false);
    srand(chrono::steady_clock::now().time_since_epoch().count());
    cin.tie(0);
    cout.tie(0);
    cout.precision(20);
    int n;
    cin>>n;
    long double res=2*PI*n;
    cout<<res<<endl;

    return 0;
    }
