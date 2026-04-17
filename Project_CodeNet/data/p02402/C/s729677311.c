#include <stdio.h>

int main(void)
{
    int n, i, min, max;
    long long int sum = 0;

    scanf("%d", &n);

    int a = 0;

    for (i = 0; i <= n - 1; i++)
    {
        scanf("%d", &a);

        if (i == 0)
        {
            min = max = a;
        } //min,maxをaと同じ値に初期化
        else if (a >= max)
        {
            max = a;
        } //aがmaxより大きい時、maxにa[i]を代入
        else if (a <= min)
        {
            min = a;
        }         //aがminより小さい時、minにaを代入
        sum += a; //aの合計
    }

    printf("%d %d %lld\n", min, max, sum);


    return 0;
}
