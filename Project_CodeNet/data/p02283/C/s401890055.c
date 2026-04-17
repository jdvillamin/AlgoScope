#include<stdio.h>
#include<stdlib.h>

struct node{
  struct node *r;
  struct node *l;
  struct node *p;
  int key;
};
typedef struct node * Node;
#define NIL NULL

Node root;

Node tSearch(Node u, int k){

}

Node tSuccessor(Node x){

}


Node trMinimum(Node x){

}

void tDelete(Node z){
  Node y; 
  Node x;
}

void preorder(Node u){
  printf(" %d",u->key);
  if(u->l != NIL){
    preorder(u->l);
  }
  if(u->r != NIL){
    preorder(u->r);
  }
}


void inorder(Node u){
  if(u->l != NIL){
    inorder(u->l);
  }
  printf(" %d",u->key);
  if(u->r != NIL){
    inorder(u->r);
  }			
}

void insert(int k){
  Node y = NIL;
  Node x = root;
  Node z;

  z = malloc(sizeof(struct node));
  z->key = k;
  z->l = NIL;
  z->r = NIL;

  while(x != NIL){
    y=x;
    if(z->key < x->key){
      x = x->l;
    }
    else{
      x = x->r;
    }
  }
  z->p = y;

  if(y == NIL){
    root=z;
  }
  else if(z->key < y->key){
    y->l = z;
  }
  else y->r = z;
}

int main(){
  int n, i, x;
  char c[20];
  scanf("%d", &n);

  for (i = 0; i < n; i++){
    scanf("%s", c);
    if (c[0] == 'f'){
      scanf("%d", &x);
      Node t = tSearch(root, x);
      if(t != NIL){
	printf("yes\n");
      }
      else{
	printf("no\n");
      }
    }
    else if(c[0] == 'i'){
      scanf("%d", &x);
      insert(x);
    }
    else if( c[0] == 'p' ){
      inorder(root);
      printf("\n");
      preorder(root);
      printf("\n");
    }
    else if(c[0] == 'd'){
      scanf("%d", &x);
      tDelete(tSearch(root, x));
    }
  }

  return 0;
}


