#include <stdio.h>

int main()
{
  int H,W;
  scanf("%d %d", &H, &W);
  char c[100][100];
  for(int i=0;i<H;i++){
    scanf("%s", &c[i]);
  }
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      printf("%c", c[i][j]);
    }
    putchar('\n');
    for(int j=0;j<W;j++){
      printf("%c", c[i][j]);
    }
    putchar('\n');
  }
  return 0;
}