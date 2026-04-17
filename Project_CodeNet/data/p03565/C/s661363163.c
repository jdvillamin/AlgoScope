#include <stdio.h>
#include <string.h>
#define STMAX 50
int main(void)
{
  int i, slen, tlen, spos, tpos, sflag = 0;
  char str[STMAX+1], ttr[STMAX+1];
  scanf("%s%*c", str);
  scanf("%s%*c", ttr);
  slen = strlen(str);
  tlen = strlen(ttr);
  spos = slen - 1;
  tpos = tlen - 1;
  while (spos >= 0) {
    if (str[spos] != '?') {
      while (tpos < tlen && str[spos] != ttr[tpos]) tpos++;
    }
    tpos--;
    if (tpos == -1) {
      sflag = 1;
      break;
    }
    spos--;
  }
  if (sflag) {
    for (i = spos; i < spos + tlen; i++) str[i] = ttr[i-spos];
    for (i = 0; i < slen; i++) {
      if (str[i] == '?') str[i] = 'a';
    }
    printf("%s\n", str);
  } else printf("UNRESTORABLE\n");
}
