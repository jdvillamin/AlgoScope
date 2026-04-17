/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d\n",&n);
    long long int a[n];
    int i, j;
    int check;
    
    for (i=0;i<n;i++)
    {
        scanf("%lld",&a[i]);
    }
    
    for (i=0;i<=n;i++)
    {
        if (i == n)
        {
            if (check == 1)
            {
                printf("NO");
            }
            else
            {
                printf("YES");
            }
        }
        else 
        {
            for (j=0;j<n;j++)
            {
                if (a[i] == a[j])
                {
                    if (i == j)
                    {
                        continue;
                    }
                    else
                    {
                        check = 1;
                    }
                }
            }
        }
    }
}
