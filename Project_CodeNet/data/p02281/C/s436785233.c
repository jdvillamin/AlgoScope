#include<stdio.h>
#define MAX 100005
#define NIL -1

struct Node{ 
  int p,l,r;
};

struct Node T[MAX]; 

void Preorder(int u){
  printf(" %d",u);
  if(u!=NIL){
    if(T[u].l!=NIL)Preorder(T[u].l);
    if(T[u].r!=NIL)Preorder(T[u].r);
  }
}

void Inorder(int u){
  
  if(u!=NIL){
    if(T[u].l!=NIL){
      Inorder(T[u].l);
    }
    printf(" %d",u);
    
    if(T[u].r!=NIL){
      Inorder(T[u].r);
    }
  }
}

void Postorder(int u){
  if(u!=NIL){
    if(T[u].l!=NIL)Postorder(T[u].l);
    if(T[u].r!=NIL)Postorder(T[u].r);
  }
  printf(" %d",u);
}

main(){
  int n,i,id,c1,c2;

  scanf("%d",&n);

  for(i=0;i<n;i++){
    T[i].p=T[i].l=T[i].r=NIL;
  }
  
  for(i=0;i<n;i++){
    scanf("%d%d%d",&id,&c1,&c2);

    T[c1].p=id;
    T[c2].p=id;
    T[id].l=c1;
    T[id].r=c2;
  }
  
  for(i=0;i<n;i++){
    if(T[i].p==NIL)break;
  }
  printf("Preorder\n");
  Preorder(i);
  printf("\n");
  
  printf("Inorder\n");
  Inorder(i);
  printf("\n");
  
  printf("Postorder\n");
  Postorder(i);
  printf("\n");

  return 0;
}