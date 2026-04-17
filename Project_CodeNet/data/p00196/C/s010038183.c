#include <stdio.h>

struct TEAM{
  char n;
  int w, l;
};

int main(){
  struct TEAM t[1000];
  int n, r, i, j, max;

  while(scanf("%d", &n) && n){
    for(i = 0; i < n; ++i){
      getchar();
      scanf("%c", &t[i].n);
      t[i].w = t[i].l = 0;
      for(j = 0; j < n - 1; ++j){
	scanf("%d", &r);
	switch(r){
	case 0: t[i].w++; break;
	case 1: t[i].l++; break;
	}
      }
      printf("%d\n", i);
    }

    for(i = 0; i < n; ++i){
      max = 0;
      for(j = 0; j < n; ++j){
	if(t[max].w < t[j].w) max = j;
	else if(t[max].w == t[j].w && t[max].l > t[j].l) max = j;
      }
      printf("%c\n", t[max].n);
      t[max].w = t[max].l = -1;
    }
  }
  return 0;
}