#include<stdio.h>
int main()
{
    int A,B,C;
    scanf("%d %d %d",&A,&B,&C);
    if(A==B && B==C)
    {
        printf("No\n");
}
        else if(A!=B && B!=C )

        {

        printf("No\n");
        }

    else
    {
        printf("Yes\n");
    }
    return 0;
}
