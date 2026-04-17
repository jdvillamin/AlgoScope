// #include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main() {
  int64_t n;
  cin>>n;

  int64_t sum3 = (n/3)*(n/3+1)/2*3;
  int64_t sum5 = (n/5)*(n/5+1)/2*5;
  int64_t sum15 = (n/15)*(n/15+1)/2*15;

  int64_t sum = n*(n+1)/2;

  cout<<sum-sum3-sum5+sum15<<endl;

  return 0;
}