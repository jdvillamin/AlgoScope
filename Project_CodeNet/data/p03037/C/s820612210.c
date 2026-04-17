#include <stdio.h>

int main(void){
	int N,M;
	scanf("%d %d",&N,&M);
	int L,R;
	int min=1;
	int max=N;
	int count=0;
	int card[N];

	for(int i=0; i<M; i++){
		scanf("%d %d",&L,&R);
		if(min>R || max<L) {printf("%d\n",0 ); return 0;}
		if(min<L) min=L;
		if(max>R)max=R;
	}
	printf("%d %d\n",min,max );
	printf("%d\n",max-min+1 );
}