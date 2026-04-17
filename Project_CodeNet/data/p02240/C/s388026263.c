#include<stdlib.h>
#define MAX 100000

int **matrix;
int color=0;
int n;

int push(int stack[],int x,int top){
	stack[top++]=x;
	return top;
}

int pop(int stack[],int *top){
	(*top)--;
	return stack[*top];
}

void Get_Color(int C[],int x){
	int *stack=malloc(sizeof(int)*n);
	int top=0;
	int temp;
	int i;
	
	color++;
	top=push(stack,x,top);
	while(top>0){
		temp=pop(stack,&top);
		if(C[temp]==0)C[temp]=color;
		i=0;
		while(matrix[temp][i]!=-1){
			if(C[matrix[temp][i]]==0){
				top=push(stack,matrix[temp][i],top);
				C[matrix[temp][i]]=color;
			}
			i++;
		}
	}
	free(stack);
	return;
}


int main(){
	int m,q;
	int i,j,x,y;
	int C[MAX];
	
	scanf("%d %d",&n,&m);
	
	matrix=malloc(sizeof(int *)*n);
	
	for(i=0;i<n;i++){
		C[i]=0;
		matrix[i]=malloc(sizeof(int)*n);
		for(j=0;j<n;j++)matrix[i][j]=-1;
	}
	
	for(i=0;i<m;i++){
		scanf("%d %d",&x,&y);
		j=0;
		while(matrix[x][j]!=-1){
			if(matrix[x][j]==y)break;
			j++;
		}
		matrix[x][j]=y;
		
		j=0;
		while(matrix[y][j]!=-1){
			if(matrix[y][j]==x)break;
			j++;
		}
		matrix[y][j]=x;
	}
	
	scanf("%d",&q);
	
	for(i=0;i<q;i++){
		scanf("%d %d",&x,&y);
		if(C[x]==0)Get_Color(C,x);
		if(C[y]==0)Get_Color(C,y);
		if(C[x]==C[y])printf("yes\n");
		else printf("no\n");
	}
	
	return 0;
	
}
