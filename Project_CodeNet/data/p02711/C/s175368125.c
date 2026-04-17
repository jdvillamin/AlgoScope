#include <iostream>

using namespace std;

int main(){
    string S;
    cin>>S;
    bool ans=false;
    for(int i=0;i<S.size();i++){
        if(S[i]=='7'){
            ans=true;
        }
    }
    if(ans){
        cout<<"Yes";
    }else{
        cout<<"No";
    }

}