#include<stdio.h>
#include<stdlib.h>
 
struct node{
  struct node *right;
  struct node *left;
  struct node *parent;
  int key;
};
typedef struct node * Node;

#define NIL NULL

Node treeSearch(Node, int);
void insert(int);
void inorder(Node);
void preorder(Node);

Node root;

int main()
{
  int n, i, x;
  char com[20];

  scanf("%d", &n);
 
  for(i = 0; i < n; i++){
    scanf("%s", com);
    if( com[0] == 'f' ){
      scanf("%d", &x);
      Node t = treeSearch(root, x);
    }

    else if( com[0] == 'i' ){
      scanf("%d", &x);
      insert(x);
    }

    else if( com[0] == 'p' ){
      inorder(root);
      printf("\n");
      preorder(root);
      printf("\n");
    }
  }
  return 0;
}

/* 探索 */
Node treeSearch(Node u, int k)
{

  if(u == NIL || k == u->key) return u;   
  if(k < u->key) return treeSearch(u->left,k);
  else return treeSearch(u->right,k);

}

/* 挿入 */
void insert(int k)
{

  Node y = NIL;
  Node x = root;
  Node z;
 
  z = malloc(sizeof(struct node));
  z->key = k;
  z->left = NIL;
  z->right = NIL;
 
  while(x != NIL){
    y = x;
    if(z->key < x->key) x = x->left;
    else x = x->right;
  }

  z->parent = y;
 
  if(y == NIL) root = z;
  else if(z->key < y->key) y->left = z;
  else y->right = z;

}

/* 中間順巡回 */
void inorder(Node u)
{

  if(u != NIL){
    inorder(u->left);
    printf(" %d", u->key);
    inorder(u->right);
  }

}

/* 先行順巡回 */
void preorder(Node u)
{

  if(u != NIL){
    printf(" %d", u->key);
    preorder(u->left);
    preorder(u->right);
  }

}