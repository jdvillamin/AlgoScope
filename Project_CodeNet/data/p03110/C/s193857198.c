#include <stdio.h>

int main()
{
    int N;
    scanf("%d\n", &N);
    double x;
    char u[5];
    
    double sum = 0;
    for(int i = 0; i < N; i++){
        scanf("%lf %s\n", &x, u);
        if(u[0] == 'J' && u[1] == 'P' && u[2] == 'Y'){
            sum += x;
        }
        else if(u[0] == 'B' && u[1] == 'T' && u[2] == 'C'){
            sum += x * 380000.0;
        }
        else{
           (void)0; //NO STATEMENT
        }
    }
    printf("%.8f",sum);
    return 0;
}
