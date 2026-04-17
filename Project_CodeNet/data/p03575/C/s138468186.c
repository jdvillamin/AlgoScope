#include <stdio.h>
int par[50];
int root(int x){
    if(par[x] == x){return x;}
    return par[x] = root(par[x]);
}

int unite(int x, int y){
    int rx = root(x);
    int ry = root(y);
    if(rx == ry){
        return 0;
    }
    par[rx] = ry;
    return 1;
}

int same(int x, int y){
    int rx = root(x);
    int ry = root(y);
    if(rx == ry){
        return 1;
    }
    return 0;
}
int main(void){
    int N, M;
    int i, j;
    int a[1225], b[1225];
    scanf("%d%d", &N, &M);

    for(i = 0; i < M; i++){
        scanf("%d%d", &a[i], &b[i]);
        a[i]--;
        b[i]--;
    }
    
    int ans = 0;

    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++){
            par[j] = j;
        }
        for(j = 0; j < M; j++){
            if(i == j){
                continue;
            }
            unite(a[j], b[j]);
        }
        if(same(a[i], b[i]) == 0){
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;   
}