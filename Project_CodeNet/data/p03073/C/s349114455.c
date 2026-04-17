#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char s[10000];
  int n = scanf("%s\n", s);
  int count = 0;
  for (int i = 0; i < n - 1; i++) {
    if (s[i + 1] == s[i]) {
      s[i + 1] = ~s[i + 1];
      count++;
    }
  }
  printf("%d\n", count);
  return 0;
}