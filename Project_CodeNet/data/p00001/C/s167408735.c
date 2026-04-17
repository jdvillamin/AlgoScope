#include<stdio.h>
int main(){
	int i,j,k,tmp;
	int ym[10001]={0};
	for(i=0;i<10;i++)scanf("%d",&ym[i]);
	for(i=0;i<10;i++){
		for(j=i+1;j<10;j++){
			if(ym[i]<ym[j]){
				tmp=ym[i];
				ym[i]=ym[j];
				ym[j]=tmp;
			}
		}
	}
	for(k=0;k<3;k++)printf("%d\n",ym[k]);
	return 0;
}
