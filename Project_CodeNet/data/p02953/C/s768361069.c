#include <stdio.h>

int main(void) {
   
   int N;
   
   scanf("%d",&N);
  
   int H[N];
   
   int i;
   
   for (i = 0; i < N; i++) {
      scanf("%d",&H[i]);
   }
   
   for (i = 0; i < N - 1; i++) {
      if (H[i] - H[i+1] >= 1) {
         H[i] = H[i] - 1;
         break;
      }
   }
   
   int check = 0;
   for (i = 0; i < N - 1; i++) {
      if (H[i] > H[i+1]) {
         check = 1;
         break;
      }
   }
   
   if (check == 0) {
      printf("Yes\n");
   }
   else {
      printf("No\n");
   }

   return 0;
}
