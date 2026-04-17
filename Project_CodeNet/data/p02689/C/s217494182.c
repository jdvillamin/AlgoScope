#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int gcd(int a,int b);
int compare(const void* a, const void* b);

int main(void){
    int N;
    int M;
    int add;
    int i,j,k,ret;
    long h;
    long H[100000];
    long Hr[100000];
    int start[100000];  //M番目の道の始点
    int end[100000];    //M番目の道の終点
    int result[100000];
    long max = 0;
    ret = 0;

    scanf("%d %d",&N,&M);
    //高さ入力
    for(i = 0 ; i < N; i++){
        scanf("%ld",&h);
        H[i] = h;                
        Hr[i] = h;
    }
    //ルート情報入力
    //見晴らしがよくない展望台はH=0にする
    for(i = 0 ; i < M ; i++){
        scanf("%d %d",&(start[i]),&(end[i]));
        start[i]--;
        end[i]--;        
        if( H[start[i]] < H[end[i]]){   // endのほうが大きい場合
            //startは見晴らしがよくない
            Hr[start[i]] = 0;
        }else if( H[start[i]] > H[end[i]]){
            Hr[end[i]] = 0;
        }  //等しい場合は両方0
        if (H[start[i]] == H[end[i]]){
            //printf("hoge\n");
            Hr[start[i]] = 0;
            Hr[end[i]] = 0;
        }
    }
    for(i=0;i<N;i++){
        if(Hr[i]>0){
            ret++;
        }else{
//            printf("%d : %ld\n",i,H[i]);
        }
    }
    printf("%d\n",ret);
    return 0;
    //↓全探索ではTLE
    // いい展望台か調べる
    for(i = 0 ; i < N ; i++){
        //startになっている道がある？
        max = H[i];
        add = 1;
        for ( j = 0 ; j < M ; j++){
            if (start[j] == i){
                if (H[end[j]] >= max){  //H[i]より標高が高い？
                    add = 0;
                    //break;
                }
            }
            if (end[j] == i){
                if (H[start[j]] >= max){  //H[i]より標高が高い？
                    add = 0;
                    //break;
                }
            }

        }
        ret += add;
    }
    printf("%d\n",ret);
    return 0;

}
int compare(const void* a, const void* b){
    return strcmp(a, b);
}
// 最大公約数
int gcd(int a,int b){
    int c;
    int tmp;
    if(b > a){  //bがaより大きい場合bとaを入れ替える
        c = a;
        a = b;
        b = c;
    }
    tmp = a % b;
    while(tmp!=0){
        a = b;
        b = tmp;
        tmp = a % b;
    }
    return b;
}
