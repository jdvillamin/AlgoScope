#include<stdio.h>
#include<string.h>
#include <stdlib.h>

struct Node{
  int key;
  struct Node *p,*l,*r;
};

struct Node *root,*NIL;

void insert(int);
void inorder(struct Node*);
void preorder(struct Node*);
struct Node* find(struct Node*,int);
int main(){
  int m,x;
  int i,j=0,c=0;
  char k[10];
  struct Node *a[50000];
  scanf("%d",&m);
  for(i=0; i < m; i++){
    scanf("%s",k);
    if(strcmp(k,"insert")==0){
      scanf("%d",&x);
      insert(x);
    }
    else if(strcmp(k,"find")==0){
      scanf("%d",&x);
      a[j]=find(root,x);
      j++;
      c++;
    }
    else if(strcmp(k,"print")==0){
      for(j=0; j < c; j++){
      if(a[j]!=NIL) printf("yes\n");
      else printf("no\n");
      }
     inorder(root);
      printf("\n");
      preorder(root);
      printf("\n");
    }
  }

  return 0;
}

void insert(int a){
  struct Node *y=NIL;
  struct Node *x=root;
  struct Node *z;

  z=((struct Node *)malloc(sizeof(struct Node)));
  z->key=a;
  z->l=NIL;
  z->r=NIL;

  while(x!=NIL){
    y=x;
    if(z->key < x->key) x=x->l;
    else x=x->r;
  }
  z->p=y;

  if(y==NIL) root=z;
  else {
    if(z->key < y->key){
      y->l=z;
    }
  else y->r =z;
  }
}

void inorder(struct Node *x){
 if(x == NIL) return;
  inorder(x->l);
  printf(" %d",x->key);
  inorder(x->r);
}

void preorder(struct Node *x){
  if(x==NIL) return;
  printf(" %d",x->key);
  preorder(x->l);
  preorder(x->r);
}

struct Node* find(struct Node *x,int k){
  while(x !=NIL && k !=x->key){
    if(k < x->key) x=x->l;
    else x=x->r;
  }
  return x;
}