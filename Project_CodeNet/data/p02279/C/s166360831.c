include <stdio.h>
#define N 100000
 
typedef struct{
  int id,p,d,k;
  int jisu[1000];
}Node;
// tree{0, 1, 2, 3, 4, 5, 6}                                                                  
// tree                                                                                       
Node tree[N];
 
int jisu(int,int);
 
int kaisu = 0,n;
main(){
 
  int j,i,nodeb;
 
  scanf("%d",&n);
 
  for(j = 0 ; j < n; j++){
    tree[j].d = 0;
    tree[j].p = -2;
    tree[j].k = 0;
  }
 
  for(j = 0 ; j < n; j++){
    scanf("%d",&nodeb);
    // 入力されたノード番号のIDをtreeの”入力されたノード番号”番目に設定する                   
    tree[nodeb].id = nodeb;
    scanf("%d",&tree[nodeb].k);
    jisu(tree[nodeb].k,nodeb);
  }
 
  for(j = 0 ; j < n; j++ ){
    if(tree[j].p == -2)tree[j].p = -1;
     printf("node %d: parent = %d, depth = %d,",tree[j].id,tree[j].p,tree[j].d);
 
    if(tree[j].p == -1){
      printf(" root, [");
      for(i = 0 ; i < tree[j].k ; i++ ){
        printf("%d",tree[j].jisu[i]);
        if(i != tree[j].k - 1){
          printf(", ");
        }
 
      }
      printf("]");
    }
 
    //&& tree[j].id != 0                                                                      
 
    if(tree[j].k == 0 && tree[j].p != -1){
      printf(" leaf, []");
    }
 
    if(tree[j].k != 0 && tree[j].p != -1){
      printf(" internal node, [");
     for(i = 0 ; i < tree[j].k ; i++ ){
        printf("%d",tree[j].jisu[i]);
        if(i != tree[j].k - 1){
          printf(", ");
        }
     }
      printf("]");
    }
 
    printf("\n");
  }
 
  return 0;
 
}
 
 
 
 
int jisu(int k,int now){
  int ii,g;
 
    for(ii = 0 ; ii < k; ii++){
      scanf("%d",&tree[now].jisu[ii]);
      if(tree[now].jisu[ii] == 0 && tree[tree[now].jisu[ii]].d != 0){
        tree[now].p = -1;
      }
      //次数に親のidいれる                                                                    
      tree[tree[now].jisu[ii]].p = now;
      tree[tree[now].jisu[ii]].d = tree[now].d + 1;
 
    for(g = 0 ; g < n; g++){
      if(tree[g].p == -1 || tree[g].p == -2) continue;
      if(tree[g].d == tree[tree[g].p].d) tree[g].d++;
    }
 
    }
    return 1;
}