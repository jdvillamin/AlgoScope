#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <bitset>
using namespace std;

typedef long long ll;
const ll inf = 1e18 + 1;
const ll limit = 1e9;

int main() {
    int n; cin >> n;
    vector<int> b(n+1);
    for (int i = 0; i < n - 1; i++) {
        int a; cin >> a;
        b[a]++;
    }
    for (int i = 1; i <= n; i++) cout << b[i] << "\n";
}