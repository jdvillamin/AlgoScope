#include<stdio.h>

int main(){
    int n,i,flg=0,j,k=0;

    scanf("%d",&n);
    int a[n];

    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(i=1;n>1 && i<n;i++){
        if(a[i-1]-a[i]==1){
            if(i<n-1 && a[i]-a[i+1]>0){
                flg=1;
                break;
            }else if(a[i]-a[i+1]==0){
                j=i+1;
                while(j<n-1 && a[j]-a[j+1]==0 ){
                    j++;
                }if(a[j]-a[j+1]>0){
                    flg=1;
                    break;
                }
            }
        }else if(a[i-1]-a[i]>1){
            flg=1;
            break;
        }
    }
    if(flg){
        printf("No\n");
    }else{
        printf("Yes\n");
    }
}