#include<stdio.h>
#define MAX 100005
#define NIL -1
 
/*
 p: parent
 l: left-child
 r: right sibling
 */
 
struct Node{
    int p, l, r;
};
struct Node T[MAX]; // Tree
int n;

void Preorder(int u){
  if(u != NIL){
  printf(" %d",u);  
  Preorder(T[u].l); 
  Preorder(T[u].r);
  }
}

void  Inorder(int u){
  if(u != NIL){
   Inorder(T[u].l); 
  printf(" %d",u);
 Inorder(T[u].r);
  }
}

void  Postorder(int u){
 if(u != NIL){
Postorder(T[u].l); 
Postorder(T[u].r); 
 printf(" %d",u);
}

}

main(){
  int i, j, d, v, c, l;
  int first/*semfirst,lasfirst,flag=0,tmp*/;
     
    scanf("%d", &n);
     
    for ( i = 0; i < n; i++ ) {
        T[i].p = T[i].l = T[i].r = NIL;
    }
    for (i = 0; i <n ; i++){
      scanf("%d %d %d", &v, &d, &c);
      //  if(i==0)tmp=v;
             T[d].p=v;
	     T[c].p=v;
             T[v].l=d;
             T[v].r=c;
    }
	     /*	     if(flag==0 /*|| flag==2) && (d!=NIL && c!=NIL)){
	       flag=3;
	       first=v;
	     }
	     if(flag==0 && (d!=NIL || c!=NIL)){
	       flag=2;
	       semfirst=v;
	     }
	   
}
    if(flag==0){
      lasfirst=tmp;
      flag=1;
      }*/
    for(i=0;i<n;i++){
      if(T[i].p == NIL)first=i;
      break;
    }

    
    /*...*/
    printf("Preorder\n");
    Preorder(first);
    
    printf("\n");
    printf("Inorder\n");
    Inorder(first);
 
    printf("\n");
    printf("Postorder\n");
    Postorder(first);
 
    printf("\n");
    return 0;
}