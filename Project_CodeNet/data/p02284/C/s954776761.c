#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
  int key;
  struct Node *right, *left, *parent;
};

struct Node *root,*NIL;

void insert(int);
void inorder(struct Node *);
void preorder(struct Node *);
int search(struct Node *,int);

int main(){
  int m,i,z;
  char s[10];
  int *find,n;
  scanf("%d",&m);
  find = (int *)malloc(sizeof(int)*m);

  for(i=0; i<m; i++){
    scanf("%s",s);
    if(strcmp(s,"insert") == 0){
      scanf("%d",&z);
      insert(z);
    }
    else if(strcmp(s,"print") == 0){
      inorder(root);
      printf("\n");
      preorder(root);
      printf("\n");
    }
    else if(strcmp(s,"find") == 0){
        scanf("%d",&n);
        if(search(root,n) == 0) printf("yes\n");
        else printf("no\n");
    }
  }
  return 0;
}

void insert(int k){
  struct Node *y = NIL;
  struct Node *x = root;
  struct Node *z;

  z = (struct Node *)malloc(sizeof(struct Node));
  z->key = k;
  z->left = NIL;
  z->right = NIL;

  while( x != NIL){
    y = x;
    if(z->key < x->key) {
      x = x->left;
    }
    else{
      x = x->right;
    }
  }
  z->parent = y;
  if(y == NIL){
    root = z;
  }
  else{
    if(z->key < y->key ){
      y->left = z;
    }
    else {
      y->right = z;
    }
  }
}

void inorder(struct Node *u){
  if(u == NIL) return;
  inorder(u->left);
  printf(" %d", u->key);
  inorder(u->right);
}

void preorder(struct Node *u){
  if(u == NIL) return;
  printf(" %d", u->key);
  preorder(u->left);
  preorder(u->right);
}

int search(struct Node *u, int n){
    while(u != NULL){
        if(n == u->key) return 0;
        else if(n < u->key) u = u->left;
        else u = u->right;
    }
    return -1;
}