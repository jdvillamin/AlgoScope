#include<stdio.h>
int main(){
int r=0,c=0,h=0,w=0,num=0,wsum=0,hsom=0,sum=0;
	int a[101][101] = {0};
	
	scanf("%d %d",&r,&c);
	
		for(h=1;h<=r;h++){
			for(w=1;w<=c;w++){
			scanf("%d",&num);
			a[h][w]=num;
			}
		}
		
		for(h=1;h<=r;h++){
			for(w=1;w<=c;w++){
			printf("%d",a[h][w]);
					if(w<=c){printf(" ");}
			}
				for(w=1;w<=c;w++){
				wsum+=a[h][w];
				}
				printf("%d",wsum);
				wsum=0;
				printf("\n");
		}
		
	for(w=1;w<=c;w++){
		for(h=1;h<=r;h++){
		hsom+=a[h][w];
		sum+=a[h][w];
		}
		printf("%d",hsom);
		if(w<c){printf(" ");}
		hsom=0;
	}
	printf(" %d\n",sum);
	
return 0;
}