#include <stdio.h>

#define MAX 20

int main() {
  int queue[MAX];
  int front = 0;
  int rear = -1;

  int even[MAX];
  int efront = 0;
  int erear = -1;

  int odd[MAX];
  int ofront = 0;
  int orear = -1;

  rear++;
  queue[rear] = 3;

  rear++;
  queue[rear] = 8;

  rear++;
  queue[rear] = 5;

  rear++;
  queue[rear] = 12;

  rear++;
  queue[rear] = 7;

  while (front <= rear) {
    int val = queue[front];
    front++;
    if (val % 2 == 0) {
      erear++;
      even[erear] = val;
    } else {
      orear++;
      odd[orear] = val;
    }
  }

  printf("Even: ");
  while (efront <= erear) {
    printf("%d ", even[efront]);
    efront++;
  }
  printf("\n");

  printf("Odd: ");
  while (ofront <= orear) {
    printf("%d ", odd[ofront]);
    ofront++;
  }
  printf("\n");

  return 0;
}
