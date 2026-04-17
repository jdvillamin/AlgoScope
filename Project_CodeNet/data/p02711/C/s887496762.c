#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int(i) = 0; (i) < (n); (i)++)

int main(){
  int N;
  cin >> N;
  int a,b,c;
  c = N % 10;
  b = (N % 100)/10;
  a = N / 100;
  if (a == 7 || b == 7 || c == 7)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
 
}