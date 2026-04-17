#include<stdio.h>
int main()
{
    int n,d;
    while(scanf("%d %d",&d,&n)!=EOF)
    {
        if(d==0)
        {
            if(n==100)
            {
                printf("101\n");
            }
            else{
            printf("%d\n",n);}
        }
        else if(d==1)
        {
            printf("%d\n",n*100);
        }
        else if(d==2)
        {
            printf("%d\n",n*10000);
        }
    }
    return 0;
}

