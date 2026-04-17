#include <stdio.h>
#include <stdlib.h>

long int digit(long int num){
    long int dig=0;
    while (num!=0) {
        dig++;
        num/=10;
    }
    return dig;
}

int main()
{
    int j=0;
    long int N,i,flag,a=1,b=1;
    scanf("%ld",&N);
    int *box;
    box=(int *)malloc(sizeof(box)*N/2+1);
    flag=N;
    for(i=2;i<=N/2;i++){
        while (flag%i==0) {
            box[i]++;
            flag/=i;
        }
        if(flag==1) break;
    }
    if(flag==N){
        flag=digit(flag);
        printf("%ld\n",flag);
    }
    else{
        for (j=i; j>1; j--) {
            while (box[j]!=0) {
                a<b?(a*=j):(b*=j);
                box[j]--;
            }
        }
        printf("%ld\n",a<b?digit(b):digit(a));
    }
    free(box);
    return 0;
}