#include <stdio.h>

int main()
{
    int iPeople, iFoods;
    // 1行目
    scanf("%d %d", &iPeople, &iFoods);

    // 食べ物の上限は30
#define FOOD_LIMIT (30)
    int aiFoodResult[FOOD_LIMIT] = {1};
    // 一人の結果を集計するための一時変数
    int aiFoodResultTemp[FOOD_LIMIT] = {0};

    int i, j;
    for (i = 0; i < iPeople; i++)
    {
        int iFoodNum;
        scanf("%d ", &iFoodNum);

        // 人の好きな食べ物の数ループ
        for (j = 0; j < iFoodNum; j++)
        {
            int iFoodId;
            scanf("%d ", &iFoodId);
            aiFoodResultTemp[iFoodId] = 1;
        }
        // 一人の結果をもとに全体を結果を生成
        for (j = 0; j < FOOD_LIMIT; j++)
        {
            aiFoodResult[j] &= aiFoodResultTemp[j];
        }
    }

    // 結果の出力
    int iResultNum = 0;
    for (j = 0; j < FOOD_LIMIT; j++)
    {
        if (aiFoodResult[j] == 1) {
            iResultNum++;
        }
    }

    printf("%d", iResultNum);

    return 0;
}