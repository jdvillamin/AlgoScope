#include <stdio.h>

int main(){
  int h, w, i = 0, j = 0;
  scanf("%d%d", &h, &w);
  char a[h][w];
  for(i = 0; i < h; i++){
    for(j = 0; j < w; j++){
        scanf("%c", &a[i][j]);
    }
  }
  for(i = 0; i < h+2; i++){
    printf("#");
  }
  printf("/n");
  for(i = 0; i < h; i++){
    printf("#");
    for(j = 0; j < w; j++){
      printf("%c", a[i][j]);
    }
    printf("#\n");
  }
  printf("\n");
  for(i = 0; i < h+2; i++){
    printf("#");
  }
  return 0;
}