#include <stdio.h>
#include <stdlib.h>

long cmp(const void *a, const void *b)
{
	return *(long *)a - *(long *)b;
}

int main()
{
    int i,f=1,n;
    long a[200010]={0};
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%ld",&a[i]);
    qsort(a,n,sizeof(long),cmp);
    for(i=0;i<n-1;i++)
        if(a[i] == a[i+1])
        {
            f=0;break;
        }
    if(f)
        printf("Yes");
    else
        printf("No");
    return 0;
}