#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char id[10];
  int value;
  struct Node* next;
} Node;

int main() {
  int n;
  scanf("%d", &n);

  Node* head = NULL;
  Node* tail = NULL;

  // ---- Build list from input ----
  for (int i = 0; i < n; i++) {
    int val;
    scanf("%d", &val);

    Node* node = (Node*)malloc(sizeof(Node));
    sprintf(node->id, "n%d", i + 1);
    node->value = val;
    node->next = NULL;

    if (head == NULL) {
      head = node;
      tail = node;
    } else {
      tail->next = node;
      tail = node;
    }
  }

  // ---- Traversal ----
  Node* curr = head;
  while (curr != NULL) {
    printf("%d ", curr->value);
    curr = curr->next;
  }
  printf("\n");

  // ---- Free ----
  curr = head;
  while (curr != NULL) {
    Node* next = curr->next;
    free(curr);
    curr = next;
  }

  return 0;
}
