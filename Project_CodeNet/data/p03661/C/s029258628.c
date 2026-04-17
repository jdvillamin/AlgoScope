#include<stdio.h>
int main()
{
    int N,i,p,suml=0,sumr=0,min,x;
    scanf("%d",&N);
    int a[N];
    for(i=0;i<N;i++)
    {
        scanf(" %d",&a[i]);
    }
    p=N/2;
    if(N!=2){
    for(i=0;i<p;i++)
    {
        suml=suml+a[i];
    }
    for(i=p;i<N;i++)
    {
        sumr=sumr+a[i];
    }
    if(suml>sumr)
    {
        min=suml-sumr;
        while(p>=0){if(a[--p]>=0)
        {suml=suml-a[p];
        sumr=sumr+a[p];}
        else {suml=suml+a[p];
        sumr=sumr-a[p];}
        if(suml>=sumr){x=suml-sumr;
        if(x<min) min=x;}
        else {x=sumr-suml;
        if(x<min) min=x;break;}
        }
    }
    else if(suml<sumr)
    {
        min=sumr-suml;
        while(p<N){if(a[p]>=0){
            suml=suml+a[p];
            sumr=sumr-a[p++];}
            else {suml=suml-a[p];
            sumr=sumr+a[p++];}
            if(suml<=sumr){x=sumr-suml;
            if(x<min) min=x;}
            else {x=suml-sumr;
            if(x<min) min=x;break;}
    }
        }
    else
        min=0;}
            else {if(a[0]>a[1])
        min=a[0]-a[1];
        else min=a[1]-a[0];}
    printf("%d",min);
    return 0;
}
