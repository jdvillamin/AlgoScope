#include<stdio.h>

int main()
{
    int a[200000],n,x,y,z,sum=0,an,mi=0,pl=0;
    scanf("%d",&n);

    for(x=0;x<n;x++){
        scanf("%d",&a[x]);
        a[x]-=x+1;
        if(a[x]>=0)
            pl++;
        if(a[x]<0)
            mi++;
    }
    for(x=0;x<n;x++){
        if(a[x]>0)
            sum+=a[x];
        if(a[x]<0)
            sum+=a[x]*-1;
    }
    an=sum;
    sum=0;
    if(pl-mi>0){
        while(1){
            for(x=0;x<n;x++){
                a[x]--;
            }
            for(x=0;x<n;x++){
                if(a[x]>0)
                    sum+=a[x];
                if(a[x]<0)
                    sum+=a[x]*-1;
            }
            if(an>sum)
                an=sum;
            else
                break;
            sum=0;
        }
    }
    if(pl-mi<0){
        while(1){
            for(x=0;x<n;x++){
                a[x]++;
            }
            for(x=0;x<n;x++){
                if(a[x]>0)
                    sum+=a[x];
                if(a[x]<0)
                    sum+=a[x]*-1;
            }
            if(an>sum)
                an=sum;
            else
                break;
            sum=0;
        }
    }

    printf("%d\n",an);



    return 0;
}
