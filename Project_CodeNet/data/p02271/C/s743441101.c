#include <stdio.h>

void solve(int*, int, int);
int flag = 0;

int main() {
  int n, q, i, A[20], B[200];

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &A[i]);
  }
  scanf("%d", &q);
  for (i = 0; i < q; i++ ) {
    scanf("%d", &B[i]);
  }

  for (i = 0; i < q; i++) {
    solve(A, B[i], n);
    if(flag == 0) printf("no\n");
    flag = 0;
  }

  return 0;
}

void solve(int *A, int m, int j) {
  if(m == 0 && j > -1) {
    printf("yes\n");
    flag = 1;
  }
  else if(m > 0 && flag == 0 && j > -1) {
    solve(A, m, j-1);
    solve(A, m-A[j], j-1);
  }
}