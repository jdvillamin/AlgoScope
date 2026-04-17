#include<stdio.h>

int t[101][101];
char map[101][101];

int absolute(int n){
    return n < 0 ? -1 * n : n;
}

void init(int x, int y, int h){
    for(int i=0; i<=100; i++){
        for(int j=0; j<=100; j++){
            if(t[i][j] >= absolute(i-x) + absolute(j-y) + h || map[i][j] == '*'){
                t[i][j] = absolute(i-x) + absolute(j-y) + h;
                map[i][j] = '.';
            }else{
                map[i][j] = '#';
            }
        }
    }
}

void func(int x, int y, int h){
    for(int i=0; i<=100; i++){
        for(int j=0; j<=100; j++){
            if(map[i][j] == '.'){
                int buf = absolute(i-x) + absolute(j-y) + h;
                if(buf != t[i][j]){
                    map[i][j] = '#';
                }
            }
        }
    }
}

void subfunc(int x, int y){
    for(int i=0; i<=100; i++){
        for(int j=0; j<=100; j++){
            if(map[i][j] == '.'){
                if(t[i][j] > absolute(i-x) + absolute(j-y)){
                    map[i][j] = '#';
                }
            }else if(map[i][j] == '*'){
                if(t[i][j] > absolute(i-x) + absolute(j-y)){
                    map[i][j] = '#';
                }else{
                    t[i][j] = absolute(i-x) + absolute(j-y);
                }
            }
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int f = 1;
    for(int i=0; i<=100; i++){
        for(int j=0; j<=100; j++){
            map[i][j] = '*';
            t[i][j] = 0;
        }
    }
    for(int i=0; i<n; i++){
        int x, y, h;
        scanf("%d %d %d", &x, &y, &h);
        if(h == 0){
            map[x][y] = '#';
            subfunc(x, y);
            continue;
        }
        if(f){
            init(x, y, h);
            f=0;
        }else{
            func(x, y, h);
        }
    }
    int ans_x, ans_y, ans_h = -1;
    for(int i=0; i<=100; i++){
        for(int j=0; j<=100; j++){
            if(map[i][j] != '#'){
                if(t[i][j] > ans_h){
                    ans_h = t[i][j];
                    ans_x = i;
                    ans_y = j;
                }
            }
        }
    }
    printf("%d %d %d", ans_x, ans_y, ans_h);

    return 0;
}