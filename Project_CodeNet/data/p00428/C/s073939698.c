#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int no;
	int num;
} place_t;

int comp(const void* x,const void* y) {
	place_t* a=(place_t*)x;
	place_t* b=(place_t*)y;
	if(a.num>b.num)return 1;
	if(a.num<b.num)return -1;
	if(a.no>b.no)return 1;
	if(a.no<b.no)return -1;
	return 0;
}

int main(void) {
	place_t place[100];
	int i,j,n,m;
	int one;
	while(1) {
		scanf("%d %d",&n,&m);
		if(n==0 && m==0)break;
		for(i=0;i<100;i++) {
			place[i].no=i;
			place[i].num=0;
		for(i=0;i<n;i++) {
			for(j=0;j<m;j++) {
				scanf("%d",&one);
				if(one)place[j].num++;
			}
		}
		qsort(place,m,sizeof(place_t),comp);
		for(i=0;i<m-1;i++) {
			printf("%d ",place[i].no+1);
		}
		printf("%d\n".place[m-1].no+1);
	}
	return 0;
}