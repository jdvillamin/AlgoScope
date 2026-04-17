#include <stdio.h>
int main(void){
    int a,i=0,j=0,k=0,l=0,num,wei,v[4][100]={},w[100],tmp;
    long long int value=0,va[4]={},max=0,now=0,ws[4]={};
    scanf("%d %d",&num,&wei);
    for(a=0;a<num;a++){
        scanf("%d",&w[a]);
        scanf("%lld",&v[w[a]-w[0]][ws[w[a]-w[0]]]);
        ws[w[a]-w[0]]++;
    }
    for(i=0;i<4;i++){
        for(j=0;j<ws[i]-1;j++){
            for(k=ws[i]-1;k>j;k--){
                if(v[i][k-1]<v[i][k]){
                    tmp=v[i][k];
                    v[i][k]=v[i][k-1];
                    v[i][k-1]=tmp;
                }
            }
        }
        for(j=0;j<ws[i];j++){
            va[i]+=v[i][j];
        }
             
    }
   
    
    for(i=0;i<=ws[0];i++){
        if(i!=0){
            now+=w[0];
            value+=v[0][i-1];
        }
        
        for(j=0;j<=ws[1];j++){
            if(j!=0){
                now+=w[0]+1;
                value+=v[1][j-1];
            }
            
            for(k=0;k<=ws[2];k++){
                if(k!=0){
                now+=w[0]+2;
                value+=v[2][k-1];
                }
                for(l=0;l<=ws[3];l++){
                    if(l!=0){
                        now+=w[0]+3;
                        value+=v[3][l-1];
                    }
                
                    if(now<=wei){
                        if(max<value){
                           
                            max=value;
                        }
                    }
                    
                }
                now-=(w[0]+3)*ws[3];
                value-=va[3];
                
            }
            now-=(w[0]+2)*ws[2];
            value-=va[2];
        }
        now-=(w[0]+1)*ws[1];
        value-=va[1];
    }
    printf("%lld",max);
}
