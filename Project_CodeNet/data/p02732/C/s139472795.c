#include<stdio.h>
#include<stdlib.h>

int comp(const void *p1, const void *p2);

int main(void){
		int n,i,size,count,tmp,index;
		unsigned long long pattern;
		int *array, *sortArr,*kind,*num,*mul;
			
		scanf("%d",&n);
		array=(int *)calloc(n,sizeof(int));
		sortArr=(int *)calloc(n,sizeof(int));
		for(i=0;i<n;i++){
			scanf("%d",&array[i]);
			sortArr[i]=array[i];
		}
		qsort(sortArr,n,sizeof(int),comp);
		/*
		for(i=0;i<n;i++){
			printf("%d%c",sortArr[i],(i<n-1)?' ':'\n');
		}*/
		size=0;
		tmp=0;
		for(i=0;i<n;i++){
			if(tmp!=sortArr[i]){
				size++;
				tmp=sortArr[i];
			}
		}
		kind=(int *)calloc(size,sizeof(int));
		num=(int *)calloc(size,sizeof(int));
		mul=(int *)calloc(size,sizeof(int));
		index=0;
		tmp=sortArr[0];
		count=0;
		pattern=0;
		for(i=0;i<=n;i++){
			if(i<n && tmp==sortArr[i]){
				count++;
			}else{
				kind[index]=tmp;
				num[index]=count;
				mul[index]=count*(count-1)/2;
				pattern+=mul[index];
				index++;
				count=1;
				if(i<n) tmp=sortArr[i];
			}
		}
		/*
		for(i=0;i<size;i++){
			printf("%d%c",kind[i],(i<size-1)?' ':'\n');
		}
		*/
		int diff;
		for(i=0;i<n;i++){
			diff=(int *)bsearch(array+i,kind,size,sizeof(int),comp)-kind;
			//printf("%p %p\n",sIndex,kind);
			printf("%llu\n",pattern-mul[diff]+(num[diff]-1)*(num[diff]-2)/2);
		}
		free(array);
		free(sortArr);
		free(kind);
		free(num);
		free(mul);
		return 0;
	}
	
	int comp(const void *p1, const void *p2){
		int n1,n2;
		n1=*((const int *)p1);
		n2=*((const int *)p2);
		return n1-n2;
	}
	
			
