#include <stdio.h>

int main()
{
    int n, m, i, j, k, t;
    int A[100][100] = {0}, b[100] = {0};

    scanf("%d %d\n", &n, &m);
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d" &A[i][j]);
        }
        printf("\n");
    }
 
    for(j = 0; j < m; i++)
    {
        scanf("%d\n", &b[j]);
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            t =+ (A[i][j] * b[j]);
        }
        printf("%d\n", t);
        t = 0;
    }

    return 0;
}