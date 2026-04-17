#include<stdio.h>
#define max 26
#define NIL -1

typedef struct{
  int parent;
  int left;
  int right;
}node;

node Y[max];

int Max(int , int);
int depth(int);
int height(int);

int main(){
  int i,n;
  int id,l,r;
  
  scanf("%d",&n);
  
  for(i=0;i<=n-1;i++){
    Y[i].parent=NIL;
  }
  
  for(i=0;i<=n-1;i++){
    scanf("%d %d %d",&id,&l,&r);
    Y[id].left=l,Y[id].right=r;
    if(l!=NIL)Y[l].parent=id;
    if(r!=NIL)Y[r].parent=id;
  }
    
  for(i=0;i<=n-1;i++){
    printf("node %d: parent = %d, sibling = ",i,Y[i].parent);
    
    if(Y[i].parent==NIL){
      printf("-1");
    }
    else if(Y[Y[i].parent].left==i){
      printf("%d",Y[Y[i].parent].right);
    }
    else{
      printf("%d",Y[Y[i].parent].left);
    }
    printf(", degree = ");
    if(Y[i].left==NIL && Y[i].right==NIL){
      printf("0");
    }
    else if (Y[i].left!=NIL && Y[i].right!=NIL){
      printf("2");
    }
    else{
      printf("1");
    }
    printf(", depth = %d, height = %d, ",depth(i),height(i));
    if(Y[i].parent==NIL){
      printf("root\n");
    }
    else if(Y[i].left==NIL && Y[i].right==NIL){
      printf("leaf\n");
    }
    else{
      printf("internal node\n");
    }
  }
  return 0;
}

int Max(int c,int d){
  if(c>d)return c;
  else return d;
}

int depth(int j){
  int k=0;
  while(Y[j].parent!=NIL){
    j=Y[j].parent;
    k++;
  }
  return k;
}

int height(int k){
  int H1=0,H2=0;
  if(Y[k].left!=NIL){
    H1=height(Y[k].left)+1;
  }
  if(Y[k].right!=NIL){
    H2=height(Y[k].right)+1;
  }
  return Max(H1,H2);
}

