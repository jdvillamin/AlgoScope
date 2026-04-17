#include<stdio.h>
#include<string.h>
#define max 100000
void change(int );
int node[max],k[max],root[max][20],leaf[max];
int main(){

  int n,h,i,j,m = 0,par,dep,dep0,jud1,jud2,count = 0,jud,count2 = 0;

  scanf("%d",&n);

  for(i = 0; i < n; i++){
    scanf("%d %d",&node[i],&k[i]);
    for(j = 0; j < k[i];j++){
      scanf("%d",&root[i][j]);
    }
  }
  jud = node[0];
  change(n);
  
  for(i = 0;i < n;i++){

    if(jud != node[i]){
    for(j = 0;j < n;j++){
      for(h = 0; h < n;h++){
	if(count ==0){
	  if(node[i] == root[j][h]){
	    par = node[j];
	    count++;
	  }
	}
	if(par == node[0]){
	  dep = 1;
	  jud1 = i;
	}
	else if(par != node[0] && par == root[0][h]){
	  dep = 2;
	  jud2 = i;
	}
	else if(par == jud2){
	  dep = 3;
	}
      }
    }
    }
    if(jud == node[i] && count2 == 0){
      par = -1;
      dep0 = 0;
      printf("node %d: parent %d, depth = %d, root, [",node[i],par,dep0);
      m = k[i];
      if(m != 0){
      for(j = 0;j < m-1;j++){
	printf("%d, ",root[i][j]);
      }
      printf("%d]\n",root[i][m-1]);
      }
      else printf("]\n");
      count2++;
    }

    if(k[i] == 0 && jud != node[i]){
      printf("node %d: parent %d, depth = %d, leaf, []\n",node[i],par,dep);
    }

    else if(jud != node[i]){
      printf("node %d: parent %d, depth = %d, internal node, [",node[i],par,dep);
      m = k[i];
      for(j = 0;j < m-1;j++){
	printf("%d, ",root[i][j]);
      }
      printf("%d]\n",root[i][m-1]);
    }
     
    par = 0;
    count = 0;
  }
  return 0;
}

void change(int n){
  int i,j,l,dum,dum2,dum3[n];

   for(i = 0;i < n;i++){
    for(j = i+1;j < n;j++){
      if(node[i] > node[j]){
      dum = node[i];
      node[i] = node[j];
      node[j] = dum;
      dum2 = k[i];
      k[i] = k[j];
      k[j] = dum2;
      for(l = 0;l <n;l++){
	dum3[l] = root[i][l];
	root[i][l] = root[j][l];
	root[j][l] = dum3[l];
      }
    }
  }
   }
}