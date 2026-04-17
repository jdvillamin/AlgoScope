/*  ex4_1
    Rikuta  */

#include <stdio.h>
#include <math.h>
int main(void){
    int tree_number,monitor_range,ans;

    //入力受け取り
    scanf("%d %d",&tree_number,&monitor_range);

    //答えの計算　一人の監視員が見れる最大幅が2*monitor_range+1であり，少数は繰り上げるので
    ans=ceil(tree_number/(2*monitor_range+1));

    //答えの出力
    printf("%d\n",ans);

    return 0;
}