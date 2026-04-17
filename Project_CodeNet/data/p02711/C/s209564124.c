#include <iostream>
using namespace std;
int main(void){
    
    int n;
    cin >> n;
    if(n/100 == 7 || n/10==7 || n%10==7) cout << "Yes" << endl;
    else cout << "No" << endl;
    
    return 0;
}