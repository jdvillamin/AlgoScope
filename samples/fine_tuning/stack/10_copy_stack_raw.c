#include <stdio.h>

#define MAX 10

int main() {
  int src[MAX], tmp[MAX], dst[MAX];
  int srcTop = -1, tmpTop = -1, dstTop = -1;

  srcTop++; src[srcTop] = 1;
  srcTop++; src[srcTop] = 2;
  srcTop++; src[srcTop] = 3;

  while (srcTop >= 0) {
    tmpTop++;
    tmp[tmpTop] = src[srcTop];
    srcTop--;
  }

  while (tmpTop >= 0) {
    dstTop++;
    dst[dstTop] = tmp[tmpTop];
    tmpTop--;
  }

  return 0;
}
