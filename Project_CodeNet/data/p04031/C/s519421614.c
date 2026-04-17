# include"stdio.h"
# include"math.h"
int main(){
    int n;
    scanf("%d",&n);
    double sum=0;
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        sum += a[i];
    }
    int med = (int)round(sum/n);
    int sc=0;
    for(int i=0;i<n;i++){
        sc += (med-a[i])*(med-a[i]);
    }
    printf("%d\n",sc );

}
