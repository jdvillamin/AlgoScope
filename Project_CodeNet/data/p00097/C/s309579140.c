#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
long xxx[10][1001][101];

long pattern(int n,int s,int from){
	long i,x=0;
	if(xxx[n][s][from]>=0)x=xxx[n][s][from];
	else{
		for(i=(s-100*(n-1)>from?s-100*(n-1):from); i<100 && i<=s ;i++){x+=pattern(n-1,s-i,i+1);}
		xxx[n][s][from]=x;
	}
	return x;
}

long pattern2(int n,int s,int from){
    if(n>1){
        long i,x=0;
        if(xxx[n][s][from]>=0)x=xxx[n][s][from];
        else{
        for(i=s-100*(n-1)>from?s-100*(n-1):from; i<100 && i<=s ;i++){x+=pattern(n-1,s-i,i+1);}
        xxx[n][s][from]=x;
        }
        return x;
    }
    else{if(from<=s && s<=100)return 1; else return 0;}
}

int main(void){
	int n,s,i,j,k;
	for(j=0;j<1001;j++){
		for(k=0;k<101;k++){
			xxx[1][j][k]=( (j<=100 && k<=j)?1:0 );
			xxx[2][j][k]=( (2*k<=j && j<=200) ? ((100-k+1)-abs((100-k)-(j-k*2)))/2 : 0 );
		}
	}

	for(i=3;i<10;i++){for(j=0;j<1001;j++){for(k=0;k<101;k++){xxx[i][j][k]=-1;}}}
    while(scanf("%d %d",&n,&s)*(n+s)){
	if(pattern(n,s,0)!=pattern2(n,s,0)){
		fprintf(stderr,"%d %d\n",n,s);
		assert(0);
	}
	printf("%ld\n",pattern(n,s,0));}
    return 0;
}