#include <stdio.h>

int main(){
    int N;
    scanf("%d", &N);

    int ans = 0, i, j;
    char S[N];
    scanf("%s", &S);

    int bnum[N], tmp=0, wht=0, max_sequence, cnt=0;
    double max=0.0;
    for (i=N-1; i>=0; i--){
        if (S[i] == '#'){
            tmp++;
        }else{
            wht++;
        }
        bnum[i] = tmp;
        if ( bnum[i] - wht > max){
            max = bnum[i] - wht;
            max_sequence = i;
        }
    }

    if (tmp != 0){
        for (i=0; i<N; i++){
            if (i<max_sequence){
                if (S[i] != '.') ans++;
            }else{
                if (S[i] != '#') ans++;
            }
        }
    }

    printf("%d", ans);
 
    return 0;
}