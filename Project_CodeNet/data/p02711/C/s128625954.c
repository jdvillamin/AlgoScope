#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <functional>
 
using namespace std;

int main() {
    int n;
    cin >> n;
    while (n > 0) {
        if (n%10==7){
            cout<<"Yes";
            return 0;
        }
        n/=10;
    }
    cout << "No";
    int n;
    
}