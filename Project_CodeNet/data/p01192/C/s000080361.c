#include <stdio.h>
#include <string.h>

int min(int a, int b)
{
    if (a > b){
        return (b);
    }
    
    return (a);
}

int main(void)
{
    char message[3][30] = {"OK", "Cannot pay some amount", "Cannot use greedy algorithm"};
    int t;
    int i, j, k;
    int n, array[50];
    static int dp[1001], greedy[1001];
    char f;
    
    t = 0;
    while (1){
        scanf("%d", &n);
        
        if (n == 0){
            break;
        }
        f = 1;
        for (i = 0; i < n; i++){
            scanf("%d", &array[i]);
            if (array[i] == 1){
                f = 0;
            }
        }
        printf("Case #%d: ", ++t);
        
        if (f){
            printf("%s\n", message[1]);
            continue;
        }
        
        f = 0;
        
        memset(dp, 0, sizeof(dp));
        for (i = 0; i < n; i++){
            for (j = 0; j + array[i] <= 1000; j++){
                if (dp[j + array[i]] == 0){
                    dp[j + array[i]] = dp[j] + 1;
                }
                else {
                    dp[j + array[i]] = min(dp[j] + 1, dp[j + array[i]]);
                }
            }
        }
        memset(greedy, 0, sizeof(greedy));
        for (i = 0; i <= 1000; i++){
            k = i;
            for (j = n - 1; j >= 0; j--){
                greedy[i] += (k / array[j]);
                k -= array[j] * (k / array[j]);
            }
        }
        for (i = 0; i <= 1000; i++){
            if (dp[i] != greedy[i]){
                f = 1;
                break;
            }
        }
        if (f){
            printf("%s\n", message[2]);
        }
        else {
            printf("%s\n", message[0]);
        }
    }
    
    return (0);
}