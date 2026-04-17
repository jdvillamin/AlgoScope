#include<iostream>
using namespace std;
 
int main(){
    int x,y;
    cin >> x>>y;
    printf("%d %d %lf\n",x/y,x%y,(double)x/(double)y);     
    return 0;
}