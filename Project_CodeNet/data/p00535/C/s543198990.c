#include <stdio.h>
#include <stdlib.h>
int st,map1[2000];
char map[1002][1002];
void snake(int x,int y){
    if(map[y][x+1]=='.')
        st++;
    if(map[y+1][x]=='.')
        st++;
    if(map[y][x-1]=='.')
        st++;
    if(map[y-1][x]=='.')
        st++;
    if(map[y-1][x+1]=='.')
        st++;
    if(map[y+1][x+1]=='.')
        st++;
    if(map[y+1][x-1]=='.')
        st++;
    if(map[y-1][x-1]=='.')
        st++;
}
int main(void){
    int h,w,sign=1,sum=-1,i,t=0,o,p;
    scanf("%d %d",&h,&w);
    p=getchar();
    for(i=1;i<=h;i++){
        for(o=1;o<=w;o++){
            map[i][o]=getchar();
        }
        p=getchar();
    }
    while(sign){
        sign=0;
        for(i=1;i<=h;i++){
            for(o=1;o<=w;o++){
                if(st=0,map[i][o] != '.' && map[i][o] < '9'){
                    snake(o,i);
                    if(map[i][o]-48<=st){
                        sign=1;
                        map1[t++]=i;
                        map1[t++]=o;
                    }
                }
            }
        }
        for(p=0;p<t;p+=2)
            map[map1[p]][map1[p+1]]='.';
        sum++;
    }
    printf("%d\n",sum);
    return 0;
}