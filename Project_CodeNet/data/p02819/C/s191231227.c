#include<stdio.h>
#include<string.h>
#include<math.h>
#define ll long long int

void sort(int array[],ll n){

ll i,j,temp;

for(i=0;i<n;i++)
{

    for(j=0;j<n;j++)
    {

        if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }

    }



}




}



int main()
{


ll x,n,i,flag,ans,c;

flag=0;

scanf("%lld",&x);

   

    n=x;
    while(1)
    {   c=0;
        for(i=1;i<=sqrt(n);i++)
        {

            if(n%i==0)
            {
                c++;

            }
            if(c>1)
            {
                c=0;
                break;

            }

        }
        if(c==1)
        {   ans=n;
            break;

        }
        n++;





    }

   printf("%lld",ans);







    return 0;
}
