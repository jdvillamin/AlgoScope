#include<iostream>
#include<vector>
using namespace std;
int main() {
	vector<long long int> v;
	long long int n;
	cin >> n;
	for (long long int i = 1; i <= n; i++) {
		if (i % 3 != 0 and i % 5 != 0) {
			v.push_back(i);
		}
	}
	long long int sum = 0;
	for (long long int i = 0 ; i < v.size(); i++) {
		sum += v[i];
	}
	cout << sum << endl;
	return 0;
}