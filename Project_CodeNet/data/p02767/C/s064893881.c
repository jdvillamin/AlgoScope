#include<stdio.h>
#include<math.h>
int main()
{
    float a,b,c;
    int n,x[100],i,j,s=0,m,p=0,q=0,temp;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&x[i]);
      b=(float)x[i];
      s=s+x[i];
      //c=(float)s;
    }
    c=(float)s;
    b=c/n;
    m=ceil(b);
    for(i=0;i<n;i++)
    {
        p=(m-x[i]);
        p=p*p;
        q=p+q;

        //if(x[i]>=m)
        //{
           // temp=x[i];
            //p=pow((temp-m),2);
      //  }
       // else if(x[i]<m)
        //{
           // temp=x[i];
            //p=pow((m-temp),2);
       // }
    }
    printf("%d\n",q);
    return 0;
}
