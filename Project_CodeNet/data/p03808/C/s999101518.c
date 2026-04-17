
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
	//変数の宣言
	int n;
	int a[100010];
	long long int sum;
	
	//よく使う変数
	int i,j,k,l;
	int flag=0;
	int ans=0;
	int count=0;
	int temp,temp1,temp2;
	int max,min;
	int len;
	//データの読み込み
	
	scanf("%d",&n);
	
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	a[n]=a[0];
	
//	printf("nは%dです\n", n);
//	printf("データの読み込み終了\n");
	//実際の処理
	
	sum=0;
	for(i=0;i<n;i++){
		sum=sum+a[i];
	}
	
	if(sum%(n*(n+1)/2)!=0){
		printf("No");
		return 0;
	}else{
		temp=sum/(n*(n+1)/2);
	}
	
	temp2=temp;
	for(i=0;i<n;i++){
		if((temp+a[i]-a[i+1])%n!=0){
			printf("No");
			return 0;
		}else{
			temp2=temp2-(temp+a[i]-a[i+1])/n;
		}
	}
	
	
//	printf("計算部分終了\n");
	//出力
	
	if(temp2==0){
		printf("Yes");
	}else{
		printf("No");
	}
	
//	printf("結果の出力終了\n");
	
	return 0;
	
}

