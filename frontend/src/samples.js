const SAMPLE_CATEGORIES = [
  {
    name: "Arrays",
    samples: [
      {
        name: "Array",
        code: `int main() {
  int arr[5];
  int i = 0;

  for (i = 0; i < 5; i++) {
    arr[i] = i * i;
  }

  return 0;
}
`,
        instrumentedCode: `#include "tracer.h"

int main() {
  int arr[5];
  trace_line(2);
  trace_array_init("arr", 5);

  int i = 0;
  trace_line(3);
  trace_var_init("i", i);
  trace_array_cell("arr", "i", i);

  trace_line(5);
  for (i = 0; i < 5; i++) {
    trace_line(5);
    trace_var("i", i);
    trace_array_cell("arr", "i", i);
    trace_array_highlight("arr", i);
    arr[i] = i * i;
    trace_line(6);
    trace_array("arr", i, arr[i]);
  }

  trace_line(9);
  return 0;
}
`,
      },
      {
        name: "2D Matrix",
        code: `int main() {
  int mat[3][5];
  int r = 0;
  int c = 0;

  for (r = 0; r < 3; r++) {
    for (c = 0; c < 5; c++) {
      mat[r][c] = (r + 1) * (c + 1);
    }
  }

  return 0;
}
`,
        instrumentedCode: `#include "tracer.h"

int main() {
  int mat[3][5];
  trace_line(2);
  trace_array2d_init("mat", 3, 5);

  int r = 0;
  trace_line(3);
  trace_var_init("r", r);

  int c = 0;
  trace_line(4);
  trace_var_init("c", c);

  trace_line(6);
  for (r = 0; r < 3; r++) {
    trace_line(6);
    trace_var("r", r);
    trace_line(7);
    for (c = 0; c < 5; c++) {
      trace_line(7);
      trace_var("c", c);
      trace_array2d_cell("mat", "r,c", r, c);
      trace_array2d_highlight("mat", r, c);
      mat[r][c] = (r + 1) * (c + 1);
      trace_line(8);
      trace_array2d("mat", r, c, mat[r][c]);
    }
  }

  trace_line(12);
  return 0;
}
`,
      },
    ],
  },
  {
    name: "Linked Lists",
    samples: [
      {
        name: "Singly Linked List",
        code: `#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char id[10];
  int value;
  struct Node* next;
} Node;

int main() {
  Node* n1 = (Node*)malloc(sizeof(Node));
  strcpy(n1->id, "n1");
  n1->value = 5;
  n1->next = NULL;
  Node* head = n1;

  Node* n2 = (Node*)malloc(sizeof(Node));
  strcpy(n2->id, "n2");
  n2->value = 10;
  n2->next = NULL;
  n1->next = n2;

  Node* n3 = (Node*)malloc(sizeof(Node));
  strcpy(n3->id, "n3");
  n3->value = 15;
  n3->next = NULL;
  n2->next = n3;

  // Traversal
  Node* temp = head;
  while (temp != NULL) {
    temp = temp->next;
  }

  free(n1);
  free(n2);
  free(n3);

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tracer.h"

typedef struct Node {
  char id[10];
  int value;
  struct Node* next;
} Node;

int main() {
  trace_ll_init("list");

  trace_line(12);
  Node* n1 = (Node*)malloc(sizeof(Node));
  trace_line(13);
  strcpy(n1->id, "n1");
  trace_line(14);
  n1->value = 5;
  trace_line(15);
  n1->next = NULL;
  trace_ll_node("list", n1->id, n1->value);
  trace_line(16);
  Node* head = n1;
  trace_ll_pointer("list", "head", n1->id);

  trace_line(18);
  Node* n2 = (Node*)malloc(sizeof(Node));
  trace_line(19);
  strcpy(n2->id, "n2");
  trace_line(20);
  n2->value = 10;
  trace_line(21);
  n2->next = NULL;
  trace_ll_node("list", n2->id, n2->value);
  trace_line(22);
  n1->next = n2;
  trace_ll_link("list", n1->id, n2->id);

  trace_line(24);
  Node* n3 = (Node*)malloc(sizeof(Node));
  trace_line(25);
  strcpy(n3->id, "n3");
  trace_line(26);
  n3->value = 15;
  trace_line(27);
  n3->next = NULL;
  trace_ll_node("list", n3->id, n3->value);
  trace_line(28);
  n2->next = n3;
  trace_ll_link("list", n2->id, n3->id);

  // Traversal
  trace_line(31);
  Node* temp = head;
  trace_ll_pointer("list", "temp", temp->id);
  trace_line(32);
  while (temp != NULL) {
    trace_line(32);
    trace_ll_highlight("list", temp->id);
    trace_line(33);
    temp = temp->next;
    if (temp != NULL) trace_ll_pointer("list", "temp", temp->id);
  }

  trace_ll_free("list", n1->id);
  trace_line(36);
  free(n1);
  trace_ll_free("list", n2->id);
  trace_line(37);
  free(n2);
  trace_ll_free("list", n3->id);
  trace_line(38);
  free(n3);

  trace_line(40);
  return 0;
}
`,
      },
      {
        name: "Doubly Linked List",
        code: `#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char id[10];
  int value;
  struct Node* prev;
  struct Node* next;
} Node;

int main() {
  Node* n1 = (Node*)malloc(sizeof(Node));
  strcpy(n1->id, "n1");
  n1->value = 5;
  n1->prev = NULL;
  n1->next = NULL;
  Node* head = n1;

  Node* n2 = (Node*)malloc(sizeof(Node));
  strcpy(n2->id, "n2");
  n2->value = 10;
  n2->prev = NULL;
  n2->next = NULL;
  n1->next = n2;
  n2->prev = n1;

  Node* n3 = (Node*)malloc(sizeof(Node));
  strcpy(n3->id, "n3");
  n3->value = 15;
  n3->prev = NULL;
  n3->next = NULL;
  n2->next = n3;
  n3->prev = n2;

  // Forward traversal
  Node* temp = head;
  while (temp != NULL) {
    temp = temp->next;
  }

  // Backward traversal
  temp = n3;
  while (temp != NULL) {
    temp = temp->prev;
  }

  // Free
  Node* curr = head;
  while (curr != NULL) {
    Node* nextNode = curr->next;
    if (curr->prev != NULL) {
      curr->prev->next = NULL;
    }
    if (curr->next != NULL) {
      curr->next->prev = NULL;
    }
    free(curr);
    curr = nextNode;
  }

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tracer.h"

typedef struct Node {
  char id[10];
  int value;
  struct Node* prev;
  struct Node* next;
} Node;

int main() {
  trace_dll_init("list");

  trace_line(13);
  Node* n1 = (Node*)malloc(sizeof(Node));
  trace_line(14);
  strcpy(n1->id, "n1");
  trace_line(15);
  n1->value = 5;
  trace_line(16);
  n1->prev = NULL;
  trace_line(17);
  n1->next = NULL;
  trace_dll_node("list", n1->id, n1->value);
  trace_line(18);
  Node* head = n1;
  trace_dll_pointer("list", "head", n1->id);

  trace_line(20);
  Node* n2 = (Node*)malloc(sizeof(Node));
  trace_line(21);
  strcpy(n2->id, "n2");
  trace_line(22);
  n2->value = 10;
  trace_line(23);
  n2->prev = NULL;
  trace_line(24);
  n2->next = NULL;
  trace_dll_node("list", n2->id, n2->value);
  trace_line(25);
  n1->next = n2;
  trace_dll_next_link("list", n1->id, n2->id);
  trace_line(26);
  n2->prev = n1;
  trace_dll_prev_link("list", n2->id, n1->id);

  trace_line(28);
  Node* n3 = (Node*)malloc(sizeof(Node));
  trace_line(29);
  strcpy(n3->id, "n3");
  trace_line(30);
  n3->value = 15;
  trace_line(31);
  n3->prev = NULL;
  trace_line(32);
  n3->next = NULL;
  trace_dll_node("list", n3->id, n3->value);
  trace_line(33);
  n2->next = n3;
  trace_dll_next_link("list", n2->id, n3->id);
  trace_line(34);
  n3->prev = n2;
  trace_dll_prev_link("list", n3->id, n2->id);

  // Forward traversal
  trace_line(37);
  Node* temp = head;
  trace_dll_pointer("list", "temp", temp->id);
  trace_line(38);
  while (temp != NULL) {
    trace_line(38);
    trace_dll_highlight("list", temp->id);
    trace_line(39);
    temp = temp->next;
    if (temp != NULL) trace_dll_pointer("list", "temp", temp->id);
  }

  // Backward traversal
  trace_line(43);
  temp = n3;
  trace_dll_pointer("list", "temp", n3->id);
  trace_line(44);
  while (temp != NULL) {
    trace_line(44);
    trace_dll_highlight("list", temp->id);
    trace_line(45);
    temp = temp->prev;
    if (temp != NULL) trace_dll_pointer("list", "temp", temp->id);
  }

  // Free
  trace_line(49);
  Node* curr = head;
  trace_line(50);
  while (curr != NULL) {
    trace_line(50);
    trace_line(51);
    Node* nextNode = curr->next;
    trace_line(52);
    if (curr->prev != NULL) {
      trace_line(53);
      curr->prev->next = NULL;
    }
    trace_line(55);
    if (curr->next != NULL) {
      trace_line(56);
      curr->next->prev = NULL;
    }
    trace_dll_free("list", curr->id);
    trace_line(58);
    free(curr);
    trace_line(59);
    curr = nextNode;
  }

  trace_line(62);
  return 0;
}
`,
      },
      {
        name: "Linked List (Input)",
        stdin: "5 3 7 1 9 4",
        code: `#include <stdio.h>
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

  // Traversal
  Node* curr = head;
  while (curr != NULL) {
    curr = curr->next;
  }

  // Free
  curr = head;
  while (curr != NULL) {
    Node* next = curr->next;
    free(curr);
    curr = next;
  }

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tracer.h"

typedef struct Node {
  char id[10];
  int value;
  struct Node* next;
} Node;

int main() {
  trace_ll_init("list");

  int n;
  trace_line(13);
  scanf("%d", &n);
  trace_var_init("n", n);

  Node* head = NULL;
  Node* tail = NULL;

  trace_line(18);
  for (int i = 0; i < n; i++) {
    trace_line(18);
    trace_var_init("i", i);
    int val;
    trace_line(20);
    scanf("%d", &val);
    trace_var_init("val", val);

    trace_line(22);
    Node* node = (Node*)malloc(sizeof(Node));
    trace_line(23);
    sprintf(node->id, "n%d", i + 1);
    trace_line(24);
    node->value = val;
    trace_line(25);
    node->next = NULL;
    trace_ll_node("list", node->id, node->value);

    trace_line(27);
    if (head == NULL) {
      trace_line(28);
      head = node;
      trace_line(29);
      tail = node;
      trace_ll_pointer("list", "head", node->id);
      trace_ll_pointer("list", "tail", node->id);
    } else {
      trace_line(31);
      tail->next = node;
      trace_ll_link("list", tail->id, node->id);
      trace_line(32);
      tail = node;
      trace_ll_pointer("list", "tail", node->id);
    }
  }

  // Traversal
  trace_line(37);
  Node* curr = head;
  if (curr != NULL) trace_ll_pointer("list", "curr", curr->id);
  trace_line(38);
  while (curr != NULL) {
    trace_line(38);
    trace_ll_highlight("list", curr->id);
    trace_line(39);
    curr = curr->next;
    if (curr != NULL) trace_ll_pointer("list", "curr", curr->id);
  }

  // Free
  trace_line(43);
  curr = head;
  trace_line(44);
  while (curr != NULL) {
    trace_line(44);
    trace_line(45);
    Node* next = curr->next;
    trace_ll_free("list", curr->id);
    trace_line(46);
    free(curr);
    trace_line(47);
    curr = next;
  }

  trace_line(50);
  return 0;
}
`,
      },
    ],
  },
  {
    name: "Stacks & Queues",
    samples: [
      {
        name: "Stack",
        code: `#include <stdio.h>

#define MAX 10

int main() {
  int stack[MAX];
  int top = -1;

  // push 5
  top++;
  stack[top] = 5;

  // push 10
  top++;
  stack[top] = 10;

  // push 15
  top++;
  stack[top] = 15;

  // pop
  top--;

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

#define MAX 10

int main() {
  trace_stack_init("S");

  int stack[MAX];
  int top = -1;
  trace_line(7);
  trace_var_init("top", top);

  // push 5
  trace_line(10);
  top++;
  trace_var("top", top);
  trace_line(11);
  stack[top] = 5;
  trace_stack_push("S", 5);

  // push 10
  trace_line(14);
  top++;
  trace_var("top", top);
  trace_line(15);
  stack[top] = 10;
  trace_stack_push("S", 10);

  // push 15
  trace_line(18);
  top++;
  trace_var("top", top);
  trace_line(19);
  stack[top] = 15;
  trace_stack_push("S", 15);

  // pop
  trace_stack_pop("S");
  trace_line(22);
  top--;
  trace_var("top", top);

  trace_line(24);
  return 0;
}
`,
      },
      {
        name: "Queue",
        code: `#include <stdio.h>

#define MAX 10

int main() {
  int queue[MAX];
  int front = 0, rear = -1;

  // enqueue 5
  rear++;
  queue[rear] = 5;

  // enqueue 10
  rear++;
  queue[rear] = 10;

  // enqueue 15
  rear++;
  queue[rear] = 15;

  // dequeue
  front++;

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

#define MAX 10

int main() {
  trace_queue_init("Q");

  int queue[MAX];
  int front = 0, rear = -1;
  trace_line(7);
  trace_var_init("front", front);
  trace_var_init("rear", rear);

  // enqueue 5
  trace_line(10);
  rear++;
  trace_var("rear", rear);
  trace_line(11);
  queue[rear] = 5;
  trace_queue_enqueue("Q", 5);

  // enqueue 10
  trace_line(14);
  rear++;
  trace_var("rear", rear);
  trace_line(15);
  queue[rear] = 10;
  trace_queue_enqueue("Q", 10);

  // enqueue 15
  trace_line(18);
  rear++;
  trace_var("rear", rear);
  trace_line(19);
  queue[rear] = 15;
  trace_queue_enqueue("Q", 15);

  // dequeue
  trace_queue_dequeue("Q");
  trace_line(22);
  front++;
  trace_var("front", front);

  trace_line(24);
  return 0;
}
`,
      },
      {
        name: "Stack (Input)",
        stdin: "5 3 7 1 9 4",
        code: `#include <stdio.h>

#define MAX 20

int main() {
  int stack[MAX];
  int top = -1;

  int n;
  scanf("%d", &n);

  // Push values from input
  for (int i = 0; i < n; i++) {
    int val;
    scanf("%d", &val);
    top++;
    stack[top] = val;
  }

  // Pop all
  while (top >= 0) {
    top--;
  }

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

#define MAX 20

int main() {
  trace_stack_init("S");

  int stack[MAX];
  int top = -1;
  trace_line(7);
  trace_var_init("top", top);

  int n;
  trace_line(10);
  scanf("%d", &n);
  trace_var_init("n", n);

  // Push values from input
  trace_line(13);
  for (int i = 0; i < n; i++) {
    trace_line(13);
    trace_var_init("i", i);
    int val;
    trace_line(15);
    scanf("%d", &val);
    trace_var_init("val", val);
    trace_line(16);
    top++;
    trace_var("top", top);
    trace_line(17);
    stack[top] = val;
    trace_stack_push("S", val);
  }

  // Pop all
  trace_line(21);
  while (top >= 0) {
    trace_line(21);
    trace_stack_pop("S");
    trace_line(22);
    top--;
    trace_var("top", top);
  }

  trace_line(25);
  return 0;
}
`,
      },
      {
        name: "Queue (Input)",
        stdin: "5 3 7 1 9 4",
        code: `#include <stdio.h>

#define MAX 20

int main() {
  int queue[MAX];
  int front = 0, rear = -1;

  int n;
  scanf("%d", &n);

  // Enqueue values from input
  for (int i = 0; i < n; i++) {
    int val;
    scanf("%d", &val);
    rear++;
    queue[rear] = val;
  }

  // Dequeue all
  while (front <= rear) {
    front++;
  }

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

#define MAX 20

int main() {
  trace_queue_init("Q");

  int queue[MAX];
  int front = 0, rear = -1;
  trace_line(7);
  trace_var_init("front", front);
  trace_var_init("rear", rear);

  int n;
  trace_line(10);
  scanf("%d", &n);
  trace_var_init("n", n);

  // Enqueue values from input
  trace_line(13);
  for (int i = 0; i < n; i++) {
    trace_line(13);
    trace_var_init("i", i);
    int val;
    trace_line(15);
    scanf("%d", &val);
    trace_var_init("val", val);
    trace_line(16);
    rear++;
    trace_var("rear", rear);
    trace_line(17);
    queue[rear] = val;
    trace_queue_enqueue("Q", val);
  }

  // Dequeue all
  trace_line(21);
  while (front <= rear) {
    trace_line(21);
    trace_queue_dequeue("Q");
    trace_line(22);
    front++;
    trace_var("front", front);
  }

  trace_line(25);
  return 0;
}
`,
      },
    ],
  },
  {
    name: "Hash Tables",
    samples: [
      {
        name: "Hash Map",
        code: `#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef struct Node {
  int key;
  int value;
  struct Node* next;
} Node;

Node* table[SIZE];

int hash(int key) { return key % SIZE; }

void put(int key, int value) {
  int index = hash(key);

  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->key = key;
  newNode->value = value;
  newNode->next = NULL;

  if (table[index] == NULL) {
    table[index] = newNode;
  } else {
    Node* temp = table[index];
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

void removeKey(int key) {
  int index = hash(key);

  Node* temp = table[index];
  Node* prev = NULL;

  while (temp != NULL && temp->key != key) {
    prev = temp;
    temp = temp->next;
  }

  if (temp == NULL) return;

  if (prev == NULL) {
    table[index] = temp->next;
  } else {
    prev->next = temp->next;
  }

  free(temp);
}

int main() {
  for (int i = 0; i < SIZE; i++) {
    table[i] = NULL;
  }

  put(10, 100);
  put(15, 150);
  put(20, 200);
  put(7, 70);

  removeKey(15);

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

#define SIZE 5

typedef struct Node {
  int key;
  int value;
  struct Node* next;
} Node;

Node* table[SIZE];

int hash(int key) { return key % SIZE; }

void put(int key, int value) {
  trace_line(17);
  int index = hash(key);

  trace_line(19);
  Node* newNode = (Node*)malloc(sizeof(Node));
  trace_line(20);
  newNode->key = key;
  trace_line(21);
  newNode->value = value;
  trace_line(22);
  newNode->next = NULL;

  trace_line(24);
  if (table[index] == NULL) {
    trace_line(25);
    table[index] = newNode;
  } else {
    trace_line(27);
    Node* temp = table[index];
    trace_line(28);
    while (temp->next != NULL) {
      trace_line(28);
      trace_line(29);
      temp = temp->next;
    }
    trace_line(31);
    temp->next = newNode;
  }

  trace_hash_put("H", key, value, index);
}

void removeKey(int key) {
  trace_line(36);
  int index = hash(key);

  trace_line(38);
  Node* temp = table[index];
  trace_line(39);
  Node* prev = NULL;

  trace_line(41);
  while (temp != NULL && temp->key != key) {
    trace_line(41);
    trace_line(42);
    prev = temp;
    trace_line(43);
    temp = temp->next;
  }

  trace_line(46);
  if (temp == NULL) return;

  trace_line(48);
  if (prev == NULL) {
    trace_line(49);
    table[index] = temp->next;
  } else {
    trace_line(51);
    prev->next = temp->next;
  }

  trace_hash_remove("H", key, index);

  trace_line(54);
  free(temp);
}

int main() {
  trace_hash_init("H", SIZE);

  trace_line(58);
  for (int i = 0; i < SIZE; i++) {
    trace_line(58);
    trace_line(59);
    table[i] = NULL;
  }

  trace_line(62);
  put(10, 100);
  trace_line(63);
  put(15, 150);
  trace_line(64);
  put(20, 200);
  trace_line(65);
  put(7, 70);

  trace_line(67);
  removeKey(15);

  trace_line(69);
  return 0;
}
`,
      },
      {
        name: "Linear Probing",
        code: `#include <stdio.h>

#define SIZE 7

int keys[SIZE];
int values[SIZE];
int occupied[SIZE];

int hash(int key) { return key % SIZE; }

void put(int key, int value) {
  int index = hash(key);
  while (occupied[index]) {
    index = (index + 1) % SIZE;
  }
  keys[index] = key;
  values[index] = value;
  occupied[index] = 1;
}

int main() {
  for (int i = 0; i < SIZE; i++) {
    occupied[i] = 0;
  }

  put(10, 100);
  put(17, 170);
  put(24, 240);
  put(3, 30);

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

#define SIZE 7

int keys[SIZE];
int values[SIZE];
int occupied[SIZE];

int hash(int key) { return key % SIZE; }

void put(int key, int value) {
  trace_line(12);
  int index = hash(key);
  trace_var_init("index", index);
  trace_line(13);
  while (occupied[index]) {
    trace_line(13);
    trace_line(14);
    index = (index + 1) % SIZE;
    trace_var("index", index);
  }
  trace_line(16);
  keys[index] = key;
  trace_line(17);
  values[index] = value;
  trace_line(18);
  occupied[index] = 1;
  trace_hash_put("H", key, value, index);
}

int main() {
  trace_hash_init("H", SIZE);

  trace_line(22);
  for (int i = 0; i < SIZE; i++) {
    trace_line(22);
    trace_line(23);
    occupied[i] = 0;
  }

  trace_line(26);
  put(10, 100);
  trace_line(27);
  put(17, 170);
  trace_line(28);
  put(24, 240);
  trace_line(29);
  put(3, 30);

  trace_line(31);
  return 0;
}
`,
      },
    ],
  },
  {
    name: "Trees",
    samples: [
      {
        name: "Binary Tree",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
} Node;

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  return n;
}

void inorder(Node* node) {
  if (node == NULL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  Node* n50 = createNode(50);
  Node* n30 = createNode(30);
  Node* n70 = createNode(70);
  Node* n20 = createNode(20);
  Node* n40 = createNode(40);
  Node* n60 = createNode(60);
  Node* n80 = createNode(80);

  n50->left = n30;
  n50->right = n70;
  n30->left = n20;
  n30->right = n40;
  n70->left = n60;
  n70->right = n80;

  inorder(n50);
  printf("\\n");

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
} Node;

Node* createNode(int data) {
  trace_line(11);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(12);
  n->data = data;
  trace_line(13);
  n->left = NULL;
  trace_line(14);
  n->right = NULL;
  trace_btree_node("T", n, n->data);
  trace_line(15);
  return n;
}

void inorder(Node* node) {
  trace_line(19);
  if (node == NULL) return;
  trace_line(20);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(21);
  printf("%d ", node->data);
  trace_line(22);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(26);
  Node* n50 = createNode(50);
  trace_line(27);
  Node* n30 = createNode(30);
  trace_line(28);
  Node* n70 = createNode(70);
  trace_line(29);
  Node* n20 = createNode(20);
  trace_line(30);
  Node* n40 = createNode(40);
  trace_line(31);
  Node* n60 = createNode(60);
  trace_line(32);
  Node* n80 = createNode(80);

  trace_line(34);
  n50->left = n30;
  trace_btree_left("T", n50, n50->left);
  trace_line(35);
  n50->right = n70;
  trace_btree_right("T", n50, n50->right);
  trace_line(36);
  n30->left = n20;
  trace_btree_left("T", n30, n30->left);
  trace_line(37);
  n30->right = n40;
  trace_btree_right("T", n30, n30->right);
  trace_line(38);
  n70->left = n60;
  trace_btree_left("T", n70, n70->left);
  trace_line(39);
  n70->right = n80;
  trace_btree_right("T", n70, n70->right);

  trace_line(41);
  inorder(n50);
  trace_line(42);
  printf("\\n");

  trace_line(44);
  return 0;
}
`,
      },
      {
        name: "BST Insert",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
} Node;

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  return n;
}

Node* insert(Node* root, int data) {
  if (root == NULL) {
    return createNode(data);
  }
  if (data < root->data) {
    root->left = insert(root->left, data);
  } else {
    root->right = insert(root->right, data);
  }
  return root;
}

void inorder(Node* node) {
  if (node == NULL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  int values[7] = {50, 30, 70, 20, 40, 60, 80};

  Node* root = NULL;
  for (int i = 0; i < 7; i++) {
    root = insert(root, values[i]);
  }

  inorder(root);
  printf("\\n");

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
} Node;

Node* createNode(int data) {
  trace_line(11);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(12);
  n->data = data;
  trace_line(13);
  n->left = NULL;
  trace_line(14);
  n->right = NULL;
  trace_btree_node("T", n, n->data);
  trace_line(15);
  return n;
}

Node* insert(Node* root, int data) {
  trace_line(19);
  if (root == NULL) {
    trace_line(20);
    return createNode(data);
  }
  trace_btree_highlight("T", root);
  trace_line(22);
  if (data < root->data) {
    trace_line(23);
    root->left = insert(root->left, data);
    trace_btree_left("T", root, root->left);
  } else {
    trace_line(25);
    root->right = insert(root->right, data);
    trace_btree_right("T", root, root->right);
  }
  trace_line(27);
  return root;
}

void inorder(Node* node) {
  trace_line(31);
  if (node == NULL) return;
  trace_line(32);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(33);
  printf("%d ", node->data);
  trace_line(34);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(38);
  int values[7] = {50, 30, 70, 20, 40, 60, 80};

  trace_line(40);
  Node* root = NULL;
  trace_line(41);
  for (int i = 0; i < 7; i++) {
    trace_line(41);
    trace_line(42);
    root = insert(root, values[i]);
  }

  trace_line(45);
  inorder(root);
  trace_line(46);
  printf("\\n");

  trace_line(48);
  return 0;
}
`,
      },
      {
        name: "BST Delete",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
} Node;

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  return n;
}

Node* insert(Node* root, int data) {
  if (root == NULL) {
    return createNode(data);
  }
  if (data < root->data) {
    root->left = insert(root->left, data);
  } else {
    root->right = insert(root->right, data);
  }
  return root;
}

Node* findMin(Node* node) {
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
}

Node* deleteNode(Node* root, int data) {
  if (root == NULL) return NULL;

  if (data < root->data) {
    root->left = deleteNode(root->left, data);
  } else if (data > root->data) {
    root->right = deleteNode(root->right, data);
  } else {
    if (root->left == NULL) {
      Node* temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      Node* temp = root->left;
      free(root);
      return temp;
    }
    Node* succ = findMin(root->right);
    root->data = succ->data;
    root->right = deleteNode(root->right, succ->data);
  }
  return root;
}

int main() {
  int values[7] = {50, 30, 70, 20, 40, 60, 80};

  Node* root = NULL;
  for (int i = 0; i < 7; i++) {
    root = insert(root, values[i]);
  }

  root = deleteNode(root, 20);
  root = deleteNode(root, 30);
  root = deleteNode(root, 50);

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
} Node;

Node* createNode(int data) {
  trace_line(11);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(12);
  n->data = data;
  trace_line(13);
  n->left = NULL;
  trace_line(14);
  n->right = NULL;
  trace_btree_node("T", n, n->data);
  trace_line(15);
  return n;
}

Node* insert(Node* root, int data) {
  trace_line(19);
  if (root == NULL) {
    trace_line(20);
    return createNode(data);
  }
  trace_btree_highlight("T", root);
  trace_line(22);
  if (data < root->data) {
    trace_line(23);
    root->left = insert(root->left, data);
    trace_btree_left("T", root, root->left);
  } else {
    trace_line(25);
    root->right = insert(root->right, data);
    trace_btree_right("T", root, root->right);
  }
  trace_line(27);
  return root;
}

Node* findMin(Node* node) {
  trace_btree_highlight("T", node);
  trace_line(31);
  while (node->left != NULL) {
    trace_line(31);
    trace_line(32);
    node = node->left;
    trace_btree_highlight("T", node);
  }
  trace_line(34);
  return node;
}

Node* deleteNode(Node* root, int data) {
  trace_line(38);
  if (root == NULL) return NULL;

  trace_btree_highlight("T", root);
  trace_line(40);
  if (data < root->data) {
    trace_line(41);
    root->left = deleteNode(root->left, data);
    trace_btree_left("T", root, root->left);
  } else if (data > root->data) {
    trace_line(43);
    root->right = deleteNode(root->right, data);
    trace_btree_right("T", root, root->right);
  } else {
    trace_line(45);
    if (root->left == NULL) {
      trace_line(46);
      Node* temp = root->right;
      trace_btree_delete("T", root);
      trace_line(47);
      free(root);
      trace_line(48);
      return temp;
    } else if (root->right == NULL) {
      trace_line(50);
      Node* temp = root->left;
      trace_btree_delete("T", root);
      trace_line(51);
      free(root);
      trace_line(52);
      return temp;
    }
    trace_line(54);
    Node* succ = findMin(root->right);
    trace_line(55);
    root->data = succ->data;
    trace_btree_update("T", root, root->data);
    trace_line(56);
    root->right = deleteNode(root->right, succ->data);
    trace_btree_right("T", root, root->right);
  }
  trace_line(58);
  return root;
}

int main() {
  trace_btree_init("T");

  trace_line(62);
  int values[7] = {50, 30, 70, 20, 40, 60, 80};

  trace_line(64);
  Node* root = NULL;
  trace_line(65);
  for (int i = 0; i < 7; i++) {
    trace_line(65);
    trace_line(66);
    root = insert(root, values[i]);
  }

  trace_line(69);
  root = deleteNode(root, 20);
  trace_line(70);
  root = deleteNode(root, 30);
  trace_line(71);
  root = deleteNode(root, 50);

  trace_line(73);
  return 0;
}
`,
      },
      {
        name: "AVL Right Rotation (LL)",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  n->height = 1;
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

Node* leftRotate(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

Node* insert(Node* node, int data) {
  if (node == NULL) return createNode(data);

  if (data < node->data) {
    node->left = insert(node->left, data);
  } else if (data > node->data) {
    node->right = insert(node->right, data);
  } else {
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalance(node);

  if (balance > 1 && data < node->left->data) {
    return rightRotate(node);
  }
  if (balance < -1 && data > node->right->data) {
    return leftRotate(node);
  }
  if (balance > 1 && data > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  if (balance < -1 && data < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

void inorder(Node* node) {
  if (node == NULL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  Node* root = NULL;

  root = insert(root, 30);
  root = insert(root, 20);
  root = insert(root, 10);

  inorder(root);
  printf("\\n");

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  trace_line(21);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(22);
  n->data = data;
  trace_line(23);
  n->left = NULL;
  trace_line(24);
  n->right = NULL;
  trace_line(25);
  n->height = 1;
  trace_btree_node("T", n, n->data);
  trace_line(26);
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  trace_line(35);
  Node* x = y->left;
  trace_line(36);
  Node* T2 = x->right;
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", y);
  trace_btree_highlight("T", x);
  trace_line(37);
  x->right = y;
  trace_btree_right("T", x, x->right);
  trace_line(38);
  y->left = T2;
  trace_btree_left("T", y, y->left);
  trace_line(39);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(40);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(41);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return x;
}

Node* leftRotate(Node* x) {
  trace_line(45);
  Node* y = x->right;
  trace_line(46);
  Node* T2 = y->left;
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", x);
  trace_btree_highlight("T", y);
  trace_line(47);
  y->left = x;
  trace_btree_left("T", y, y->left);
  trace_line(48);
  x->right = T2;
  trace_btree_right("T", x, x->right);
  trace_line(49);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(50);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(51);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return y;
}

Node* insert(Node* node, int data) {
  trace_line(55);
  if (node == NULL) return createNode(data);
  trace_btree_highlight("T", node);
  trace_line(57);
  if (data < node->data) {
    trace_line(58);
    node->left = insert(node->left, data);
    trace_btree_left("T", node, node->left);
  } else if (data > node->data) {
    trace_line(60);
    node->right = insert(node->right, data);
    trace_btree_right("T", node, node->right);
  } else {
    trace_line(62);
    return node;
  }
  trace_line(65);
  node->height = 1 + max(height(node->left), height(node->right));
  trace_line(66);
  int balance = getBalance(node);
  trace_line(68);
  if (balance > 1 && data < node->left->data) {
    trace_line(69);
    return rightRotate(node);
  }
  trace_line(71);
  if (balance < -1 && data > node->right->data) {
    trace_line(72);
    return leftRotate(node);
  }
  trace_line(74);
  if (balance > 1 && data > node->left->data) {
    trace_line(75);
    node->left = leftRotate(node->left);
    trace_btree_left("T", node, node->left);
    trace_line(76);
    return rightRotate(node);
  }
  trace_line(78);
  if (balance < -1 && data < node->right->data) {
    trace_line(79);
    node->right = rightRotate(node->right);
    trace_btree_right("T", node, node->right);
    trace_line(80);
    return leftRotate(node);
  }
  trace_line(83);
  return node;
}

void inorder(Node* node) {
  trace_line(87);
  if (node == NULL) return;
  trace_line(88);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(89);
  printf("%d ", node->data);
  trace_line(90);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(94);
  Node* root = NULL;

  trace_line(96);
  root = insert(root, 30);
  trace_line(97);
  root = insert(root, 20);
  trace_line(98);
  root = insert(root, 10);

  trace_line(100);
  inorder(root);
  trace_line(101);
  printf("\\n");

  trace_line(103);
  return 0;
}
`,
      },
      {
        name: "AVL Left Rotation (RR)",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  n->height = 1;
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

Node* leftRotate(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

Node* insert(Node* node, int data) {
  if (node == NULL) return createNode(data);

  if (data < node->data) {
    node->left = insert(node->left, data);
  } else if (data > node->data) {
    node->right = insert(node->right, data);
  } else {
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalance(node);

  if (balance > 1 && data < node->left->data) {
    return rightRotate(node);
  }
  if (balance < -1 && data > node->right->data) {
    return leftRotate(node);
  }
  if (balance > 1 && data > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  if (balance < -1 && data < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

void inorder(Node* node) {
  if (node == NULL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  Node* root = NULL;

  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);

  inorder(root);
  printf("\\n");

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  trace_line(21);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(22);
  n->data = data;
  trace_line(23);
  n->left = NULL;
  trace_line(24);
  n->right = NULL;
  trace_line(25);
  n->height = 1;
  trace_btree_node("T", n, n->data);
  trace_line(26);
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  trace_line(35);
  Node* x = y->left;
  trace_line(36);
  Node* T2 = x->right;
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", y);
  trace_btree_highlight("T", x);
  trace_line(37);
  x->right = y;
  trace_btree_right("T", x, x->right);
  trace_line(38);
  y->left = T2;
  trace_btree_left("T", y, y->left);
  trace_line(39);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(40);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(41);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return x;
}

Node* leftRotate(Node* x) {
  trace_line(45);
  Node* y = x->right;
  trace_line(46);
  Node* T2 = y->left;
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", x);
  trace_btree_highlight("T", y);
  trace_line(47);
  y->left = x;
  trace_btree_left("T", y, y->left);
  trace_line(48);
  x->right = T2;
  trace_btree_right("T", x, x->right);
  trace_line(49);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(50);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(51);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return y;
}

Node* insert(Node* node, int data) {
  trace_line(55);
  if (node == NULL) return createNode(data);
  trace_btree_highlight("T", node);
  trace_line(57);
  if (data < node->data) {
    trace_line(58);
    node->left = insert(node->left, data);
    trace_btree_left("T", node, node->left);
  } else if (data > node->data) {
    trace_line(60);
    node->right = insert(node->right, data);
    trace_btree_right("T", node, node->right);
  } else {
    trace_line(62);
    return node;
  }
  trace_line(65);
  node->height = 1 + max(height(node->left), height(node->right));
  trace_line(66);
  int balance = getBalance(node);
  trace_line(68);
  if (balance > 1 && data < node->left->data) {
    trace_line(69);
    return rightRotate(node);
  }
  trace_line(71);
  if (balance < -1 && data > node->right->data) {
    trace_line(72);
    return leftRotate(node);
  }
  trace_line(74);
  if (balance > 1 && data > node->left->data) {
    trace_line(75);
    node->left = leftRotate(node->left);
    trace_btree_left("T", node, node->left);
    trace_line(76);
    return rightRotate(node);
  }
  trace_line(78);
  if (balance < -1 && data < node->right->data) {
    trace_line(79);
    node->right = rightRotate(node->right);
    trace_btree_right("T", node, node->right);
    trace_line(80);
    return leftRotate(node);
  }
  trace_line(83);
  return node;
}

void inorder(Node* node) {
  trace_line(87);
  if (node == NULL) return;
  trace_line(88);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(89);
  printf("%d ", node->data);
  trace_line(90);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(94);
  Node* root = NULL;

  trace_line(96);
  root = insert(root, 10);
  trace_line(97);
  root = insert(root, 20);
  trace_line(98);
  root = insert(root, 30);

  trace_line(100);
  inorder(root);
  trace_line(101);
  printf("\\n");

  trace_line(103);
  return 0;
}
`,
      },
      {
        name: "AVL Left-Right Rotation (LR)",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  n->height = 1;
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

Node* leftRotate(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

Node* insert(Node* node, int data) {
  if (node == NULL) return createNode(data);

  if (data < node->data) {
    node->left = insert(node->left, data);
  } else if (data > node->data) {
    node->right = insert(node->right, data);
  } else {
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalance(node);

  if (balance > 1 && data < node->left->data) {
    return rightRotate(node);
  }
  if (balance < -1 && data > node->right->data) {
    return leftRotate(node);
  }
  if (balance > 1 && data > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  if (balance < -1 && data < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

void inorder(Node* node) {
  if (node == NULL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  Node* root = NULL;

  root = insert(root, 30);
  root = insert(root, 10);
  root = insert(root, 20);

  inorder(root);
  printf("\\n");

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  trace_line(21);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(22);
  n->data = data;
  trace_line(23);
  n->left = NULL;
  trace_line(24);
  n->right = NULL;
  trace_line(25);
  n->height = 1;
  trace_btree_node("T", n, n->data);
  trace_line(26);
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  trace_line(35);
  Node* x = y->left;
  trace_line(36);
  Node* T2 = x->right;
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", y);
  trace_btree_highlight("T", x);
  trace_line(37);
  x->right = y;
  trace_btree_right("T", x, x->right);
  trace_line(38);
  y->left = T2;
  trace_btree_left("T", y, y->left);
  trace_line(39);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(40);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(41);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return x;
}

Node* leftRotate(Node* x) {
  trace_line(45);
  Node* y = x->right;
  trace_line(46);
  Node* T2 = y->left;
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", x);
  trace_btree_highlight("T", y);
  trace_line(47);
  y->left = x;
  trace_btree_left("T", y, y->left);
  trace_line(48);
  x->right = T2;
  trace_btree_right("T", x, x->right);
  trace_line(49);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(50);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(51);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return y;
}

Node* insert(Node* node, int data) {
  trace_line(55);
  if (node == NULL) return createNode(data);
  trace_btree_highlight("T", node);
  trace_line(57);
  if (data < node->data) {
    trace_line(58);
    node->left = insert(node->left, data);
    trace_btree_left("T", node, node->left);
  } else if (data > node->data) {
    trace_line(60);
    node->right = insert(node->right, data);
    trace_btree_right("T", node, node->right);
  } else {
    trace_line(62);
    return node;
  }
  trace_line(65);
  node->height = 1 + max(height(node->left), height(node->right));
  trace_line(66);
  int balance = getBalance(node);
  trace_line(68);
  if (balance > 1 && data < node->left->data) {
    trace_line(69);
    return rightRotate(node);
  }
  trace_line(71);
  if (balance < -1 && data > node->right->data) {
    trace_line(72);
    return leftRotate(node);
  }
  trace_line(74);
  if (balance > 1 && data > node->left->data) {
    trace_line(75);
    node->left = leftRotate(node->left);
    trace_btree_left("T", node, node->left);
    trace_line(76);
    return rightRotate(node);
  }
  trace_line(78);
  if (balance < -1 && data < node->right->data) {
    trace_line(79);
    node->right = rightRotate(node->right);
    trace_btree_right("T", node, node->right);
    trace_line(80);
    return leftRotate(node);
  }
  trace_line(83);
  return node;
}

void inorder(Node* node) {
  trace_line(87);
  if (node == NULL) return;
  trace_line(88);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(89);
  printf("%d ", node->data);
  trace_line(90);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(94);
  Node* root = NULL;

  trace_line(96);
  root = insert(root, 30);
  trace_line(97);
  root = insert(root, 10);
  trace_line(98);
  root = insert(root, 20);

  trace_line(100);
  inorder(root);
  trace_line(101);
  printf("\\n");

  trace_line(103);
  return 0;
}
`,
      },
      {
        name: "AVL Right-Left Rotation (RL)",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  n->height = 1;
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

Node* leftRotate(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

Node* insert(Node* node, int data) {
  if (node == NULL) return createNode(data);

  if (data < node->data) {
    node->left = insert(node->left, data);
  } else if (data > node->data) {
    node->right = insert(node->right, data);
  } else {
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalance(node);

  if (balance > 1 && data < node->left->data) {
    return rightRotate(node);
  }
  if (balance < -1 && data > node->right->data) {
    return leftRotate(node);
  }
  if (balance > 1 && data > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  if (balance < -1 && data < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

void inorder(Node* node) {
  if (node == NULL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  Node* root = NULL;

  root = insert(root, 10);
  root = insert(root, 30);
  root = insert(root, 20);

  inorder(root);
  printf("\\n");

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  trace_line(21);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(22);
  n->data = data;
  trace_line(23);
  n->left = NULL;
  trace_line(24);
  n->right = NULL;
  trace_line(25);
  n->height = 1;
  trace_btree_node("T", n, n->data);
  trace_line(26);
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  trace_line(35);
  Node* x = y->left;
  trace_line(36);
  Node* T2 = x->right;
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", y);
  trace_btree_highlight("T", x);
  trace_line(37);
  x->right = y;
  trace_btree_right("T", x, x->right);
  trace_line(38);
  y->left = T2;
  trace_btree_left("T", y, y->left);
  trace_line(39);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(40);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(41);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return x;
}

Node* leftRotate(Node* x) {
  trace_line(45);
  Node* y = x->right;
  trace_line(46);
  Node* T2 = y->left;
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", x);
  trace_btree_highlight("T", y);
  trace_line(47);
  y->left = x;
  trace_btree_left("T", y, y->left);
  trace_line(48);
  x->right = T2;
  trace_btree_right("T", x, x->right);
  trace_line(49);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(50);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(51);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return y;
}

Node* insert(Node* node, int data) {
  trace_line(55);
  if (node == NULL) return createNode(data);
  trace_btree_highlight("T", node);
  trace_line(57);
  if (data < node->data) {
    trace_line(58);
    node->left = insert(node->left, data);
    trace_btree_left("T", node, node->left);
  } else if (data > node->data) {
    trace_line(60);
    node->right = insert(node->right, data);
    trace_btree_right("T", node, node->right);
  } else {
    trace_line(62);
    return node;
  }
  trace_line(65);
  node->height = 1 + max(height(node->left), height(node->right));
  trace_line(66);
  int balance = getBalance(node);
  trace_line(68);
  if (balance > 1 && data < node->left->data) {
    trace_line(69);
    return rightRotate(node);
  }
  trace_line(71);
  if (balance < -1 && data > node->right->data) {
    trace_line(72);
    return leftRotate(node);
  }
  trace_line(74);
  if (balance > 1 && data > node->left->data) {
    trace_line(75);
    node->left = leftRotate(node->left);
    trace_btree_left("T", node, node->left);
    trace_line(76);
    return rightRotate(node);
  }
  trace_line(78);
  if (balance < -1 && data < node->right->data) {
    trace_line(79);
    node->right = rightRotate(node->right);
    trace_btree_right("T", node, node->right);
    trace_line(80);
    return leftRotate(node);
  }
  trace_line(83);
  return node;
}

void inorder(Node* node) {
  trace_line(87);
  if (node == NULL) return;
  trace_line(88);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(89);
  printf("%d ", node->data);
  trace_line(90);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(94);
  Node* root = NULL;

  trace_line(96);
  root = insert(root, 10);
  trace_line(97);
  root = insert(root, 30);
  trace_line(98);
  root = insert(root, 20);

  trace_line(100);
  inorder(root);
  trace_line(101);
  printf("\\n");

  trace_line(103);
  return 0;
}
`,
      },
      {
        name: "AVL Insert",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  n->height = 1;
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

Node* leftRotate(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

Node* insert(Node* node, int data) {
  if (node == NULL) return createNode(data);

  if (data < node->data) {
    node->left = insert(node->left, data);
  } else if (data > node->data) {
    node->right = insert(node->right, data);
  } else {
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalance(node);

  if (balance > 1 && data < node->left->data) {
    return rightRotate(node);
  }
  if (balance < -1 && data > node->right->data) {
    return leftRotate(node);
  }
  if (balance > 1 && data > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  if (balance < -1 && data < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

void inorder(Node* node) {
  if (node == NULL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  int values[7] = {1, 2, 3, 4, 5, 6, 7};

  Node* root = NULL;
  for (int i = 0; i < 7; i++) {
    root = insert(root, values[i]);
  }

  inorder(root);
  printf("\\n");

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  trace_line(21);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(22);
  n->data = data;
  trace_line(23);
  n->left = NULL;
  trace_line(24);
  n->right = NULL;
  trace_line(25);
  n->height = 1;
  trace_btree_node("T", n, n->data);
  trace_line(26);
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  trace_line(35);
  Node* x = y->left;
  trace_line(36);
  Node* T2 = x->right;
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", y);
  trace_btree_highlight("T", x);
  trace_line(37);
  x->right = y;
  trace_btree_right("T", x, x->right);
  trace_line(38);
  y->left = T2;
  trace_btree_left("T", y, y->left);
  trace_line(39);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(40);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(41);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return x;
}

Node* leftRotate(Node* x) {
  trace_line(45);
  Node* y = x->right;
  trace_line(46);
  Node* T2 = y->left;
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", x);
  trace_btree_highlight("T", y);
  trace_line(47);
  y->left = x;
  trace_btree_left("T", y, y->left);
  trace_line(48);
  x->right = T2;
  trace_btree_right("T", x, x->right);
  trace_line(49);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(50);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(51);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return y;
}

Node* insert(Node* node, int data) {
  trace_line(55);
  if (node == NULL) return createNode(data);
  trace_btree_highlight("T", node);
  trace_line(57);
  if (data < node->data) {
    trace_line(58);
    node->left = insert(node->left, data);
    trace_btree_left("T", node, node->left);
  } else if (data > node->data) {
    trace_line(60);
    node->right = insert(node->right, data);
    trace_btree_right("T", node, node->right);
  } else {
    trace_line(62);
    return node;
  }
  trace_line(65);
  node->height = 1 + max(height(node->left), height(node->right));
  trace_line(66);
  int balance = getBalance(node);
  trace_line(68);
  if (balance > 1 && data < node->left->data) {
    trace_line(69);
    return rightRotate(node);
  }
  trace_line(71);
  if (balance < -1 && data > node->right->data) {
    trace_line(72);
    return leftRotate(node);
  }
  trace_line(74);
  if (balance > 1 && data > node->left->data) {
    trace_line(75);
    node->left = leftRotate(node->left);
    trace_btree_left("T", node, node->left);
    trace_line(76);
    return rightRotate(node);
  }
  trace_line(78);
  if (balance < -1 && data < node->right->data) {
    trace_line(79);
    node->right = rightRotate(node->right);
    trace_btree_right("T", node, node->right);
    trace_line(80);
    return leftRotate(node);
  }
  trace_line(83);
  return node;
}

void inorder(Node* node) {
  trace_line(87);
  if (node == NULL) return;
  trace_line(88);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(89);
  printf("%d ", node->data);
  trace_line(90);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(94);
  int values[7] = {1, 2, 3, 4, 5, 6, 7};

  trace_line(96);
  Node* root = NULL;
  trace_line(97);
  for (int i = 0; i < 7; i++) {
    trace_line(97);
    trace_line(98);
    root = insert(root, values[i]);
  }

  trace_line(101);
  inorder(root);
  trace_line(102);
  printf("\\n");

  trace_line(104);
  return 0;
}
`,
      },
      {
        name: "AVL Delete",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  n->height = 1;
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

Node* leftRotate(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

Node* insert(Node* node, int data) {
  if (node == NULL) return createNode(data);

  if (data < node->data) {
    node->left = insert(node->left, data);
  } else if (data > node->data) {
    node->right = insert(node->right, data);
  } else {
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalance(node);

  if (balance > 1 && data < node->left->data) {
    return rightRotate(node);
  }
  if (balance < -1 && data > node->right->data) {
    return leftRotate(node);
  }
  if (balance > 1 && data > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  if (balance < -1 && data < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

Node* minValueNode(Node* node) {
  Node* current = node;
  while (current->left != NULL) {
    current = current->left;
  }
  return current;
}

Node* deleteNode(Node* root, int data) {
  if (root == NULL) return NULL;

  if (data < root->data) {
    root->left = deleteNode(root->left, data);
  } else if (data > root->data) {
    root->right = deleteNode(root->right, data);
  } else {
    if (root->left == NULL) {
      Node* temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      Node* temp = root->left;
      free(root);
      return temp;
    }
    Node* succ = minValueNode(root->right);
    root->data = succ->data;
    root->right = deleteNode(root->right, succ->data);
  }

  root->height = 1 + max(height(root->left), height(root->right));
  int balance = getBalance(root);

  if (balance > 1 && getBalance(root->left) >= 0) {
    return rightRotate(root);
  }
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  if (balance < -1 && getBalance(root->right) <= 0) {
    return leftRotate(root);
  }
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

void inorder(Node* node) {
  if (node == NULL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  int values[7] = {9, 5, 10, 0, 6, 11, -1};

  Node* root = NULL;
  for (int i = 0; i < 7; i++) {
    root = insert(root, values[i]);
  }

  root = deleteNode(root, 10);

  inorder(root);
  printf("\\n");

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  trace_line(21);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(22);
  n->data = data;
  trace_line(23);
  n->left = NULL;
  trace_line(24);
  n->right = NULL;
  trace_line(25);
  n->height = 1;
  trace_btree_node("T", n, n->data);
  trace_line(26);
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  trace_line(35);
  Node* x = y->left;
  trace_line(36);
  Node* T2 = x->right;
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", y);
  trace_btree_highlight("T", x);
  trace_line(37);
  x->right = y;
  trace_btree_right("T", x, x->right);
  trace_line(38);
  y->left = T2;
  trace_btree_left("T", y, y->left);
  trace_line(39);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(40);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(41);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return x;
}

Node* leftRotate(Node* x) {
  trace_line(45);
  Node* y = x->right;
  trace_line(46);
  Node* T2 = y->left;
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", x);
  trace_btree_highlight("T", y);
  trace_line(47);
  y->left = x;
  trace_btree_left("T", y, y->left);
  trace_line(48);
  x->right = T2;
  trace_btree_right("T", x, x->right);
  trace_line(49);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(50);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(51);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return y;
}

Node* insert(Node* node, int data) {
  trace_line(55);
  if (node == NULL) return createNode(data);
  trace_btree_highlight("T", node);
  trace_line(57);
  if (data < node->data) {
    trace_line(58);
    node->left = insert(node->left, data);
    trace_btree_left("T", node, node->left);
  } else if (data > node->data) {
    trace_line(60);
    node->right = insert(node->right, data);
    trace_btree_right("T", node, node->right);
  } else {
    trace_line(62);
    return node;
  }
  trace_line(65);
  node->height = 1 + max(height(node->left), height(node->right));
  trace_line(66);
  int balance = getBalance(node);
  trace_line(68);
  if (balance > 1 && data < node->left->data) {
    trace_line(69);
    return rightRotate(node);
  }
  trace_line(71);
  if (balance < -1 && data > node->right->data) {
    trace_line(72);
    return leftRotate(node);
  }
  trace_line(74);
  if (balance > 1 && data > node->left->data) {
    trace_line(75);
    node->left = leftRotate(node->left);
    trace_btree_left("T", node, node->left);
    trace_line(76);
    return rightRotate(node);
  }
  trace_line(78);
  if (balance < -1 && data < node->right->data) {
    trace_line(79);
    node->right = rightRotate(node->right);
    trace_btree_right("T", node, node->right);
    trace_line(80);
    return leftRotate(node);
  }
  trace_line(83);
  return node;
}

Node* minValueNode(Node* node) {
  trace_line(87);
  Node* current = node;
  trace_btree_highlight("T", current);
  trace_line(88);
  while (current->left != NULL) {
    trace_line(89);
    current = current->left;
    trace_btree_highlight("T", current);
  }
  trace_line(91);
  return current;
}

Node* deleteNode(Node* root, int data) {
  trace_line(95);
  if (root == NULL) return NULL;
  trace_btree_highlight("T", root);
  trace_line(97);
  if (data < root->data) {
    trace_line(98);
    root->left = deleteNode(root->left, data);
    trace_btree_left("T", root, root->left);
  } else if (data > root->data) {
    trace_line(100);
    root->right = deleteNode(root->right, data);
    trace_btree_right("T", root, root->right);
  } else {
    trace_line(102);
    if (root->left == NULL) {
      trace_line(103);
      Node* temp = root->right;
      trace_btree_delete("T", root);
      trace_line(104);
      free(root);
      trace_line(105);
      return temp;
    } else if (root->right == NULL) {
      trace_line(107);
      Node* temp = root->left;
      trace_btree_delete("T", root);
      trace_line(108);
      free(root);
      trace_line(109);
      return temp;
    }
    trace_line(111);
    Node* succ = minValueNode(root->right);
    trace_line(112);
    root->data = succ->data;
    trace_btree_update("T", root, root->data);
    trace_line(113);
    root->right = deleteNode(root->right, succ->data);
    trace_btree_right("T", root, root->right);
  }
  trace_line(116);
  root->height = 1 + max(height(root->left), height(root->right));
  trace_line(117);
  int balance = getBalance(root);
  trace_line(119);
  if (balance > 1 && getBalance(root->left) >= 0) {
    trace_line(120);
    return rightRotate(root);
  }
  trace_line(122);
  if (balance > 1 && getBalance(root->left) < 0) {
    trace_line(123);
    root->left = leftRotate(root->left);
    trace_btree_left("T", root, root->left);
    trace_line(124);
    return rightRotate(root);
  }
  trace_line(126);
  if (balance < -1 && getBalance(root->right) <= 0) {
    trace_line(127);
    return leftRotate(root);
  }
  trace_line(129);
  if (balance < -1 && getBalance(root->right) > 0) {
    trace_line(130);
    root->right = rightRotate(root->right);
    trace_btree_right("T", root, root->right);
    trace_line(131);
    return leftRotate(root);
  }
  trace_line(134);
  return root;
}

void inorder(Node* node) {
  trace_line(138);
  if (node == NULL) return;
  trace_line(139);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(140);
  printf("%d ", node->data);
  trace_line(141);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(145);
  int values[7] = {9, 5, 10, 0, 6, 11, -1};

  trace_line(147);
  Node* root = NULL;
  trace_line(148);
  for (int i = 0; i < 7; i++) {
    trace_line(148);
    trace_line(149);
    root = insert(root, values[i]);
  }

  trace_line(152);
  root = deleteNode(root, 10);

  trace_line(154);
  inorder(root);
  trace_line(155);
  printf("\\n");

  trace_line(157);
  return 0;
}
`,
      },
      {
        name: "AVL (Full)",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  n->height = 1;
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

Node* leftRotate(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

Node* insert(Node* node, int data) {
  if (node == NULL) return createNode(data);

  if (data < node->data) {
    node->left = insert(node->left, data);
  } else if (data > node->data) {
    node->right = insert(node->right, data);
  } else {
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalance(node);

  if (balance > 1 && data < node->left->data) {
    return rightRotate(node);
  }
  if (balance < -1 && data > node->right->data) {
    return leftRotate(node);
  }
  if (balance > 1 && data > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  if (balance < -1 && data < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

Node* minValueNode(Node* node) {
  Node* current = node;
  while (current->left != NULL) {
    current = current->left;
  }
  return current;
}

Node* deleteNode(Node* root, int data) {
  if (root == NULL) return NULL;

  if (data < root->data) {
    root->left = deleteNode(root->left, data);
  } else if (data > root->data) {
    root->right = deleteNode(root->right, data);
  } else {
    if (root->left == NULL) {
      Node* temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      Node* temp = root->left;
      free(root);
      return temp;
    }
    Node* succ = minValueNode(root->right);
    root->data = succ->data;
    root->right = deleteNode(root->right, succ->data);
  }

  root->height = 1 + max(height(root->left), height(root->right));
  int balance = getBalance(root);

  if (balance > 1 && getBalance(root->left) >= 0) {
    return rightRotate(root);
  }
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  if (balance < -1 && getBalance(root->right) <= 0) {
    return leftRotate(root);
  }
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

void inorder(Node* node) {
  if (node == NULL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  int values[7] = {10, 20, 30, 40, 50, 60, 70};

  Node* root = NULL;
  for (int i = 0; i < 7; i++) {
    root = insert(root, values[i]);
  }

  inorder(root);
  printf("\\n");

  root = deleteNode(root, 60);
  root = deleteNode(root, 50);

  inorder(root);
  printf("\\n");

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  trace_line(21);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(22);
  n->data = data;
  trace_line(23);
  n->left = NULL;
  trace_line(24);
  n->right = NULL;
  trace_line(25);
  n->height = 1;
  trace_btree_node("T", n, n->data);
  trace_line(26);
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  trace_line(35);
  Node* x = y->left;
  trace_line(36);
  Node* T2 = x->right;
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", y);
  trace_btree_highlight("T", x);
  trace_line(37);
  x->right = y;
  trace_btree_right("T", x, x->right);
  trace_line(38);
  y->left = T2;
  trace_btree_left("T", y, y->left);
  trace_line(39);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(40);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(41);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return x;
}

Node* leftRotate(Node* x) {
  trace_line(45);
  Node* y = x->right;
  trace_line(46);
  Node* T2 = y->left;
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "T2", T2);
  trace_btree_highlight("T", x);
  trace_btree_highlight("T", y);
  trace_line(47);
  y->left = x;
  trace_btree_left("T", y, y->left);
  trace_line(48);
  x->right = T2;
  trace_btree_right("T", x, x->right);
  trace_line(49);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(50);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(51);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return y;
}

Node* insert(Node* node, int data) {
  trace_line(55);
  if (node == NULL) return createNode(data);
  trace_btree_highlight("T", node);
  trace_line(57);
  if (data < node->data) {
    trace_line(58);
    node->left = insert(node->left, data);
    trace_btree_left("T", node, node->left);
  } else if (data > node->data) {
    trace_line(60);
    node->right = insert(node->right, data);
    trace_btree_right("T", node, node->right);
  } else {
    trace_line(62);
    return node;
  }
  trace_line(65);
  node->height = 1 + max(height(node->left), height(node->right));
  trace_line(66);
  int balance = getBalance(node);
  trace_line(68);
  if (balance > 1 && data < node->left->data) {
    trace_line(69);
    return rightRotate(node);
  }
  trace_line(71);
  if (balance < -1 && data > node->right->data) {
    trace_line(72);
    return leftRotate(node);
  }
  trace_line(74);
  if (balance > 1 && data > node->left->data) {
    trace_line(75);
    node->left = leftRotate(node->left);
    trace_btree_left("T", node, node->left);
    trace_line(76);
    return rightRotate(node);
  }
  trace_line(78);
  if (balance < -1 && data < node->right->data) {
    trace_line(79);
    node->right = rightRotate(node->right);
    trace_btree_right("T", node, node->right);
    trace_line(80);
    return leftRotate(node);
  }
  trace_line(83);
  return node;
}

Node* minValueNode(Node* node) {
  trace_line(87);
  Node* current = node;
  trace_btree_highlight("T", current);
  trace_line(88);
  while (current->left != NULL) {
    trace_line(89);
    current = current->left;
    trace_btree_highlight("T", current);
  }
  trace_line(91);
  return current;
}

Node* deleteNode(Node* root, int data) {
  trace_line(95);
  if (root == NULL) return NULL;
  trace_btree_highlight("T", root);
  trace_line(97);
  if (data < root->data) {
    trace_line(98);
    root->left = deleteNode(root->left, data);
    trace_btree_left("T", root, root->left);
  } else if (data > root->data) {
    trace_line(100);
    root->right = deleteNode(root->right, data);
    trace_btree_right("T", root, root->right);
  } else {
    trace_line(102);
    if (root->left == NULL) {
      trace_line(103);
      Node* temp = root->right;
      trace_btree_delete("T", root);
      trace_line(104);
      free(root);
      trace_line(105);
      return temp;
    } else if (root->right == NULL) {
      trace_line(107);
      Node* temp = root->left;
      trace_btree_delete("T", root);
      trace_line(108);
      free(root);
      trace_line(109);
      return temp;
    }
    trace_line(111);
    Node* succ = minValueNode(root->right);
    trace_line(112);
    root->data = succ->data;
    trace_btree_update("T", root, root->data);
    trace_line(113);
    root->right = deleteNode(root->right, succ->data);
    trace_btree_right("T", root, root->right);
  }
  trace_line(116);
  root->height = 1 + max(height(root->left), height(root->right));
  trace_line(117);
  int balance = getBalance(root);
  trace_line(119);
  if (balance > 1 && getBalance(root->left) >= 0) {
    trace_line(120);
    return rightRotate(root);
  }
  trace_line(122);
  if (balance > 1 && getBalance(root->left) < 0) {
    trace_line(123);
    root->left = leftRotate(root->left);
    trace_btree_left("T", root, root->left);
    trace_line(124);
    return rightRotate(root);
  }
  trace_line(126);
  if (balance < -1 && getBalance(root->right) <= 0) {
    trace_line(127);
    return leftRotate(root);
  }
  trace_line(129);
  if (balance < -1 && getBalance(root->right) > 0) {
    trace_line(130);
    root->right = rightRotate(root->right);
    trace_btree_right("T", root, root->right);
    trace_line(131);
    return leftRotate(root);
  }
  trace_line(134);
  return root;
}

void inorder(Node* node) {
  trace_line(138);
  if (node == NULL) return;
  trace_line(139);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(140);
  printf("%d ", node->data);
  trace_line(141);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(145);
  int values[7] = {10, 20, 30, 40, 50, 60, 70};

  trace_line(147);
  Node* root = NULL;
  trace_line(148);
  for (int i = 0; i < 7; i++) {
    trace_line(148);
    trace_line(149);
    root = insert(root, values[i]);
  }

  trace_line(152);
  inorder(root);
  trace_line(153);
  printf("\\n");

  trace_line(155);
  root = deleteNode(root, 60);
  trace_line(156);
  root = deleteNode(root, 50);

  trace_line(158);
  inorder(root);
  trace_line(159);
  printf("\\n");

  trace_line(161);
  return 0;
}
`,
      },
      {
        name: "Red-Black Left Rotation",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  char color;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

Node nil;
Node* NIL = &nil;

Node* createNode(int data, char color) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->color = color;
  n->left = NIL;
  n->right = NIL;
  n->parent = NIL;
  return n;
}

void leftRotate(Node** root, Node* x) {
  Node* y = x->right;
  x->right = y->left;
  if (y->left != NIL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NIL) {
    *root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void inorder(Node* node) {
  if (node == NIL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  NIL->color = 'B';

  Node* root = createNode(10, 'B');
  Node* a = createNode(5, 'B');
  Node* y = createNode(20, 'R');
  Node* b = createNode(15, 'B');
  Node* c = createNode(25, 'B');

  root->left = a;
  a->parent = root;
  root->right = y;
  y->parent = root;
  y->left = b;
  b->parent = y;
  y->right = c;
  c->parent = y;

  inorder(root);
  printf("\\n");

  leftRotate(&root, root);

  root->color = 'B';
  root->left->color = 'R';

  inorder(root);
  printf("\\n");

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  char color;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

Node nil;
Node* NIL = &nil;

Node* createNode(int data, char color) {
  trace_line(16);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(17);
  n->data = data;
  trace_line(18);
  n->color = color;
  trace_line(19);
  n->left = NIL;
  trace_line(20);
  n->right = NIL;
  trace_line(21);
  n->parent = NIL;
  trace_btree_node("T", n, n->data);
  trace_btree_color("T", n, color == 'R' ? "R" : "B");
  trace_line(22);
  return n;
}

void leftRotate(Node** root, Node* x) {
  trace_line(26);
  Node* y = x->right;
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "y", y == NIL ? NULL : y);
  trace_btree_highlight("T", x);
  trace_line(27);
  x->right = y->left;
  trace_btree_right("T", x, x->right == NIL ? NULL : x->right);
  trace_line(28);
  if (y->left != NIL) {
    trace_line(29);
    y->left->parent = x;
  }
  trace_line(31);
  y->parent = x->parent;
  trace_line(32);
  if (x->parent == NIL) {
    trace_line(33);
    *root = y;
  } else if (x == x->parent->left) {
    trace_line(35);
    x->parent->left = y;
    trace_btree_left("T", x->parent, y);
  } else {
    trace_line(37);
    x->parent->right = y;
    trace_btree_right("T", x->parent, y);
  }
  trace_line(39);
  y->left = x;
  trace_btree_left("T", y, x);
  trace_line(40);
  x->parent = y;
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
}

void inorder(Node* node) {
  trace_line(44);
  if (node == NIL) return;
  trace_line(45);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(46);
  printf("%d ", node->data);
  trace_line(47);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");
  trace_line(51);
  NIL->color = 'B';

  trace_line(53);
  Node* root = createNode(10, 'B');
  trace_line(54);
  Node* a = createNode(5, 'B');
  trace_line(55);
  Node* y = createNode(20, 'R');
  trace_line(56);
  Node* b = createNode(15, 'B');
  trace_line(57);
  Node* c = createNode(25, 'B');

  trace_line(59);
  root->left = a;
  trace_btree_left("T", root, a);
  trace_line(60);
  a->parent = root;
  trace_line(61);
  root->right = y;
  trace_btree_right("T", root, y);
  trace_line(62);
  y->parent = root;
  trace_line(63);
  y->left = b;
  trace_btree_left("T", y, b);
  trace_line(64);
  b->parent = y;
  trace_line(65);
  y->right = c;
  trace_btree_right("T", y, c);
  trace_line(66);
  c->parent = y;

  trace_line(68);
  inorder(root);
  trace_line(69);
  printf("\\n");

  trace_line(71);
  leftRotate(&root, root);

  trace_line(73);
  root->color = 'B';
  trace_btree_color("T", root, "B");
  trace_line(74);
  root->left->color = 'R';
  trace_btree_color("T", root->left, "R");

  trace_line(76);
  inorder(root);
  trace_line(77);
  printf("\\n");

  trace_line(79);
  return 0;
}
`,
      },
      {
        name: "Red-Black Right Rotation",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  char color;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

Node nil;
Node* NIL = &nil;

Node* createNode(int data, char color) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->color = color;
  n->left = NIL;
  n->right = NIL;
  n->parent = NIL;
  return n;
}

void rightRotate(Node** root, Node* y) {
  Node* x = y->left;
  y->left = x->right;
  if (x->right != NIL) {
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == NIL) {
    *root = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }
  x->right = y;
  y->parent = x;
}

void inorder(Node* node) {
  if (node == NIL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  NIL->color = 'B';

  Node* root = createNode(20, 'B');
  Node* x = createNode(10, 'R');
  Node* a = createNode(5, 'B');
  Node* b = createNode(15, 'B');
  Node* c = createNode(25, 'B');

  root->left = x;
  x->parent = root;
  root->right = c;
  c->parent = root;
  x->left = a;
  a->parent = x;
  x->right = b;
  b->parent = x;

  inorder(root);
  printf("\\n");

  rightRotate(&root, root);

  root->color = 'B';
  root->right->color = 'R';

  inorder(root);
  printf("\\n");

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  char color;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

Node nil;
Node* NIL = &nil;

Node* createNode(int data, char color) {
  trace_line(16);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(17);
  n->data = data;
  trace_line(18);
  n->color = color;
  trace_line(19);
  n->left = NIL;
  trace_line(20);
  n->right = NIL;
  trace_line(21);
  n->parent = NIL;
  trace_btree_node("T", n, n->data);
  trace_btree_color("T", n, color == 'R' ? "R" : "B");
  trace_line(22);
  return n;
}

void rightRotate(Node** root, Node* y) {
  trace_line(26);
  Node* x = y->left;
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "x", x == NIL ? NULL : x);
  trace_btree_highlight("T", y);
  trace_line(27);
  y->left = x->right;
  trace_btree_left("T", y, y->left == NIL ? NULL : y->left);
  trace_line(28);
  if (x->right != NIL) {
    trace_line(29);
    x->right->parent = y;
  }
  trace_line(31);
  x->parent = y->parent;
  trace_line(32);
  if (y->parent == NIL) {
    trace_line(33);
    *root = x;
  } else if (y == y->parent->left) {
    trace_line(35);
    y->parent->left = x;
    trace_btree_left("T", y->parent, x);
  } else {
    trace_line(37);
    y->parent->right = x;
    trace_btree_right("T", y->parent, x);
  }
  trace_line(39);
  x->right = y;
  trace_btree_right("T", x, y);
  trace_line(40);
  y->parent = x;
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
}

void inorder(Node* node) {
  trace_line(44);
  if (node == NIL) return;
  trace_line(45);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(46);
  printf("%d ", node->data);
  trace_line(47);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");
  trace_line(51);
  NIL->color = 'B';

  trace_line(53);
  Node* root = createNode(20, 'B');
  trace_line(54);
  Node* x = createNode(10, 'R');
  trace_line(55);
  Node* a = createNode(5, 'B');
  trace_line(56);
  Node* b = createNode(15, 'B');
  trace_line(57);
  Node* c = createNode(25, 'B');

  trace_line(59);
  root->left = x;
  trace_btree_left("T", root, x);
  trace_line(60);
  x->parent = root;
  trace_line(61);
  root->right = c;
  trace_btree_right("T", root, c);
  trace_line(62);
  c->parent = root;
  trace_line(63);
  x->left = a;
  trace_btree_left("T", x, a);
  trace_line(64);
  a->parent = x;
  trace_line(65);
  x->right = b;
  trace_btree_right("T", x, b);
  trace_line(66);
  b->parent = x;

  trace_line(68);
  inorder(root);
  trace_line(69);
  printf("\\n");

  trace_line(71);
  rightRotate(&root, root);

  trace_line(73);
  root->color = 'B';
  trace_btree_color("T", root, "B");
  trace_line(74);
  root->right->color = 'R';
  trace_btree_color("T", root->right, "R");

  trace_line(76);
  inorder(root);
  trace_line(77);
  printf("\\n");

  trace_line(79);
  return 0;
}
`,
      },
      {
        name: "Red-Black Insert",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  char color;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

Node nil;
Node* NIL = &nil;

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->color = 'R';
  n->left = NIL;
  n->right = NIL;
  n->parent = NIL;
  return n;
}

void leftRotate(Node** root, Node* x) {
  Node* y = x->right;
  x->right = y->left;
  if (y->left != NIL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NIL) {
    *root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void rightRotate(Node** root, Node* y) {
  Node* x = y->left;
  y->left = x->right;
  if (x->right != NIL) {
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == NIL) {
    *root = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }
  x->right = y;
  y->parent = x;
}

void insertFixup(Node** root, Node* z) {
  while (z->parent->color == 'R') {
    if (z->parent == z->parent->parent->left) {
      Node* u = z->parent->parent->right;
      if (u->color == 'R') {
        z->parent->color = 'B';
        u->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          leftRotate(root, z);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        rightRotate(root, z->parent->parent);
      }
    } else {
      Node* u = z->parent->parent->left;
      if (u->color == 'R') {
        z->parent->color = 'B';
        u->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rightRotate(root, z);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        leftRotate(root, z->parent->parent);
      }
    }
  }
  (*root)->color = 'B';
}

void insert(Node** root, int data) {
  Node* z = createNode(data);
  Node* y = NIL;
  Node* x = *root;
  while (x != NIL) {
    y = x;
    if (z->data < x->data) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->parent = y;
  if (y == NIL) {
    *root = z;
  } else if (z->data < y->data) {
    y->left = z;
  } else {
    y->right = z;
  }
  insertFixup(root, z);
}

void inorder(Node* node) {
  if (node == NIL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  NIL->color = 'B';

  int values[8] = {10, 20, 30, 15, 25, 5, 1, 2};

  Node* root = NIL;
  for (int i = 0; i < 8; i++) {
    insert(&root, values[i]);
  }

  inorder(root);
  printf("\\n");

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  char color;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

Node nil;
Node* NIL = &nil;

Node* createNode(int data) {
  trace_line(16);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(17);
  n->data = data;
  trace_line(18);
  n->color = 'R';
  trace_line(19);
  n->left = NIL;
  trace_line(20);
  n->right = NIL;
  trace_line(21);
  n->parent = NIL;
  trace_btree_node("T", n, n->data);
  trace_btree_color("T", n, "R");
  trace_line(22);
  return n;
}

void leftRotate(Node** root, Node* x) {
  trace_line(26);
  Node* y = x->right;
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "y", y == NIL ? NULL : y);
  trace_line(27);
  x->right = y->left;
  trace_btree_right("T", x, x->right == NIL ? NULL : x->right);
  trace_line(28);
  if (y->left != NIL) {
    trace_line(29);
    y->left->parent = x;
  }
  trace_line(31);
  y->parent = x->parent;
  trace_line(32);
  if (x->parent == NIL) {
    trace_line(33);
    *root = y;
  } else if (x == x->parent->left) {
    trace_line(35);
    x->parent->left = y;
    trace_btree_left("T", x->parent, y);
  } else {
    trace_line(37);
    x->parent->right = y;
    trace_btree_right("T", x->parent, y);
  }
  trace_line(39);
  y->left = x;
  trace_btree_left("T", y, x);
  trace_line(40);
  x->parent = y;
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
}

void rightRotate(Node** root, Node* y) {
  trace_line(44);
  Node* x = y->left;
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "x", x == NIL ? NULL : x);
  trace_line(45);
  y->left = x->right;
  trace_btree_left("T", y, y->left == NIL ? NULL : y->left);
  trace_line(46);
  if (x->right != NIL) {
    trace_line(47);
    x->right->parent = y;
  }
  trace_line(49);
  x->parent = y->parent;
  trace_line(50);
  if (y->parent == NIL) {
    trace_line(51);
    *root = x;
  } else if (y == y->parent->left) {
    trace_line(53);
    y->parent->left = x;
    trace_btree_left("T", y->parent, x);
  } else {
    trace_line(55);
    y->parent->right = x;
    trace_btree_right("T", y->parent, x);
  }
  trace_line(57);
  x->right = y;
  trace_btree_right("T", x, y);
  trace_line(58);
  y->parent = x;
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
}

void insertFixup(Node** root, Node* z) {
  trace_line(62);
  while (z->parent->color == 'R') {
    trace_line(62);
    trace_btree_pointer("T", "z", z);
    trace_btree_highlight("T", z);
    trace_line(63);
    if (z->parent == z->parent->parent->left) {
      trace_line(64);
      Node* u = z->parent->parent->right;
      trace_btree_pointer("T", "u", u == NIL ? NULL : u);
      trace_line(65);
      if (u->color == 'R') {
        trace_line(66);
        z->parent->color = 'B';
        trace_btree_color("T", z->parent, "B");
        trace_line(67);
        u->color = 'B';
        trace_btree_color("T", u, "B");
        trace_line(68);
        z->parent->parent->color = 'R';
        trace_btree_color("T", z->parent->parent, "R");
        trace_line(69);
        z = z->parent->parent;
        trace_btree_pointer("T", "z", z);
      } else {
        trace_line(71);
        if (z == z->parent->right) {
          trace_line(72);
          z = z->parent;
          trace_btree_pointer("T", "z", z);
          trace_line(73);
          leftRotate(root, z);
        }
        trace_line(75);
        z->parent->color = 'B';
        trace_btree_color("T", z->parent, "B");
        trace_line(76);
        z->parent->parent->color = 'R';
        trace_btree_color("T", z->parent->parent, "R");
        trace_line(77);
        rightRotate(root, z->parent->parent);
      }
    } else {
      trace_line(80);
      Node* u = z->parent->parent->left;
      trace_btree_pointer("T", "u", u == NIL ? NULL : u);
      trace_line(81);
      if (u->color == 'R') {
        trace_line(82);
        z->parent->color = 'B';
        trace_btree_color("T", z->parent, "B");
        trace_line(83);
        u->color = 'B';
        trace_btree_color("T", u, "B");
        trace_line(84);
        z->parent->parent->color = 'R';
        trace_btree_color("T", z->parent->parent, "R");
        trace_line(85);
        z = z->parent->parent;
        trace_btree_pointer("T", "z", z);
      } else {
        trace_line(87);
        if (z == z->parent->left) {
          trace_line(88);
          z = z->parent;
          trace_btree_pointer("T", "z", z);
          trace_line(89);
          rightRotate(root, z);
        }
        trace_line(91);
        z->parent->color = 'B';
        trace_btree_color("T", z->parent, "B");
        trace_line(92);
        z->parent->parent->color = 'R';
        trace_btree_color("T", z->parent->parent, "R");
        trace_line(93);
        leftRotate(root, z->parent->parent);
      }
    }
  }
  trace_btree_pointer("T", "z", NULL);
  trace_btree_pointer("T", "u", NULL);
  trace_line(97);
  (*root)->color = 'B';
  trace_btree_color("T", *root, "B");
}

void insert(Node** root, int data) {
  trace_line(101);
  Node* z = createNode(data);
  trace_line(102);
  Node* y = NIL;
  trace_line(103);
  Node* x = *root;
  trace_line(104);
  while (x != NIL) {
    trace_line(104);
    trace_btree_highlight("T", x);
    trace_line(105);
    y = x;
    trace_line(106);
    if (z->data < x->data) {
      trace_line(107);
      x = x->left;
    } else {
      trace_line(109);
      x = x->right;
    }
  }
  trace_line(112);
  z->parent = y;
  trace_line(113);
  if (y == NIL) {
    trace_line(114);
    *root = z;
  } else if (z->data < y->data) {
    trace_line(116);
    y->left = z;
    trace_btree_left("T", y, z);
  } else {
    trace_line(118);
    y->right = z;
    trace_btree_right("T", y, z);
  }
  trace_line(120);
  insertFixup(root, z);
}

void inorder(Node* node) {
  trace_line(124);
  if (node == NIL) return;
  trace_line(125);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(126);
  printf("%d ", node->data);
  trace_line(127);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");
  trace_line(131);
  NIL->color = 'B';

  trace_line(133);
  int values[8] = {10, 20, 30, 15, 25, 5, 1, 2};

  trace_line(135);
  Node* root = NIL;
  trace_line(136);
  for (int i = 0; i < 8; i++) {
    trace_line(136);
    trace_line(137);
    insert(&root, values[i]);
  }

  trace_line(140);
  inorder(root);
  trace_line(141);
  printf("\\n");

  trace_line(143);
  return 0;
}
`,
      },
      {
        name: "Red-Black Search",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  char color;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

Node nil;
Node* NIL = &nil;

Node* createNode(int data, char color) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->color = color;
  n->left = NIL;
  n->right = NIL;
  n->parent = NIL;
  return n;
}

Node* search(Node* root, int key) {
  Node* cur = root;
  while (cur != NIL && cur->data != key) {
    if (key < cur->data) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return cur;
}

int main() {
  NIL->color = 'B';

  Node* root = createNode(15, 'B');
  Node* l = createNode(10, 'R');
  Node* r = createNode(20, 'R');
  Node* a = createNode(5, 'B');
  Node* b = createNode(12, 'B');
  Node* c = createNode(17, 'B');
  Node* d = createNode(25, 'B');

  root->left = l;
  l->parent = root;
  root->right = r;
  r->parent = root;
  l->left = a;
  a->parent = l;
  l->right = b;
  b->parent = l;
  r->left = c;
  c->parent = r;
  r->right = d;
  d->parent = r;

  Node* found = search(root, 12);
  if (found != NIL) {
    printf("Found %d (%c)\\n", found->data, found->color);
  } else {
    printf("12 not found\\n");
  }

  found = search(root, 19);
  if (found != NIL) {
    printf("Found %d (%c)\\n", found->data, found->color);
  } else {
    printf("19 not found\\n");
  }

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  char color;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

Node nil;
Node* NIL = &nil;

Node* createNode(int data, char color) {
  trace_line(16);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(17);
  n->data = data;
  trace_line(18);
  n->color = color;
  trace_line(19);
  n->left = NIL;
  trace_line(20);
  n->right = NIL;
  trace_line(21);
  n->parent = NIL;
  trace_btree_node("T", n, n->data);
  trace_btree_color("T", n, color == 'R' ? "R" : "B");
  trace_line(22);
  return n;
}

Node* search(Node* root, int key) {
  trace_line(26);
  Node* cur = root;
  trace_btree_pointer("T", "cur", cur == NIL ? NULL : cur);
  trace_line(27);
  while (cur != NIL && cur->data != key) {
    trace_line(27);
    trace_btree_highlight("T", cur);
    trace_line(28);
    if (key < cur->data) {
      trace_line(29);
      cur = cur->left;
    } else {
      trace_line(31);
      cur = cur->right;
    }
    trace_btree_pointer("T", "cur", cur == NIL ? NULL : cur);
  }
  trace_btree_highlight("T", cur == NIL ? NULL : cur);
  trace_btree_pointer("T", "cur", NULL);
  trace_line(34);
  return cur;
}

int main() {
  trace_btree_init("T");
  trace_line(38);
  NIL->color = 'B';

  trace_line(40);
  Node* root = createNode(15, 'B');
  trace_line(41);
  Node* l = createNode(10, 'R');
  trace_line(42);
  Node* r = createNode(20, 'R');
  trace_line(43);
  Node* a = createNode(5, 'B');
  trace_line(44);
  Node* b = createNode(12, 'B');
  trace_line(45);
  Node* c = createNode(17, 'B');
  trace_line(46);
  Node* d = createNode(25, 'B');

  trace_line(48);
  root->left = l;
  trace_btree_left("T", root, l);
  trace_line(49);
  l->parent = root;
  trace_line(50);
  root->right = r;
  trace_btree_right("T", root, r);
  trace_line(51);
  r->parent = root;
  trace_line(52);
  l->left = a;
  trace_btree_left("T", l, a);
  trace_line(53);
  a->parent = l;
  trace_line(54);
  l->right = b;
  trace_btree_right("T", l, b);
  trace_line(55);
  b->parent = l;
  trace_line(56);
  r->left = c;
  trace_btree_left("T", r, c);
  trace_line(57);
  c->parent = r;
  trace_line(58);
  r->right = d;
  trace_btree_right("T", r, d);
  trace_line(59);
  d->parent = r;

  trace_line(61);
  Node* found = search(root, 12);
  trace_btree_pointer("T", "found", found == NIL ? NULL : found);
  trace_line(62);
  if (found != NIL) {
    trace_line(63);
    printf("Found %d (%c)\\n", found->data, found->color);
  } else {
    trace_line(65);
    printf("12 not found\\n");
  }

  trace_line(68);
  found = search(root, 19);
  trace_btree_pointer("T", "found", found == NIL ? NULL : found);
  trace_line(69);
  if (found != NIL) {
    trace_line(70);
    printf("Found %d (%c)\\n", found->data, found->color);
  } else {
    trace_line(72);
    printf("19 not found\\n");
  }

  trace_line(75);
  return 0;
}
`,
      },
      {
        name: "Red-Black Delete",
        code: `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  char color;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

Node nil;
Node* NIL = &nil;

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->color = 'R';
  n->left = NIL;
  n->right = NIL;
  n->parent = NIL;
  return n;
}

void leftRotate(Node** root, Node* x) {
  Node* y = x->right;
  x->right = y->left;
  if (y->left != NIL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NIL) {
    *root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void rightRotate(Node** root, Node* y) {
  Node* x = y->left;
  y->left = x->right;
  if (x->right != NIL) {
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == NIL) {
    *root = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }
  x->right = y;
  y->parent = x;
}

void insertFixup(Node** root, Node* z) {
  while (z->parent->color == 'R') {
    if (z->parent == z->parent->parent->left) {
      Node* u = z->parent->parent->right;
      if (u->color == 'R') {
        z->parent->color = 'B';
        u->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          leftRotate(root, z);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        rightRotate(root, z->parent->parent);
      }
    } else {
      Node* u = z->parent->parent->left;
      if (u->color == 'R') {
        z->parent->color = 'B';
        u->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rightRotate(root, z);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        leftRotate(root, z->parent->parent);
      }
    }
  }
  (*root)->color = 'B';
}

void insert(Node** root, int data) {
  Node* z = createNode(data);
  Node* y = NIL;
  Node* x = *root;
  while (x != NIL) {
    y = x;
    if (z->data < x->data) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->parent = y;
  if (y == NIL) {
    *root = z;
  } else if (z->data < y->data) {
    y->left = z;
  } else {
    y->right = z;
  }
  insertFixup(root, z);
}

Node* search(Node* root, int key) {
  Node* cur = root;
  while (cur != NIL && cur->data != key) {
    if (key < cur->data) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return cur;
}

Node* minimum(Node* x) {
  while (x->left != NIL) {
    x = x->left;
  }
  return x;
}

void transplant(Node** root, Node* u, Node* v) {
  if (u->parent == NIL) {
    *root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void deleteFixup(Node** root, Node* x) {
  while (x != *root && x->color == 'B') {
    if (x == x->parent->left) {
      Node* w = x->parent->right;
      if (w->color == 'R') {
        w->color = 'B';
        x->parent->color = 'R';
        leftRotate(root, x->parent);
        w = x->parent->right;
      }
      if (w->left->color == 'B' && w->right->color == 'B') {
        w->color = 'R';
        x = x->parent;
      } else {
        if (w->right->color == 'B') {
          w->left->color = 'B';
          w->color = 'R';
          rightRotate(root, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->right->color = 'B';
        leftRotate(root, x->parent);
        x = *root;
      }
    } else {
      Node* w = x->parent->left;
      if (w->color == 'R') {
        w->color = 'B';
        x->parent->color = 'R';
        rightRotate(root, x->parent);
        w = x->parent->left;
      }
      if (w->right->color == 'B' && w->left->color == 'B') {
        w->color = 'R';
        x = x->parent;
      } else {
        if (w->left->color == 'B') {
          w->right->color = 'B';
          w->color = 'R';
          leftRotate(root, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->left->color = 'B';
        rightRotate(root, x->parent);
        x = *root;
      }
    }
  }
  x->color = 'B';
}

void deleteNode(Node** root, Node* z) {
  Node* y = z;
  Node* x;
  char yColor = y->color;
  if (z->left == NIL) {
    x = z->right;
    transplant(root, z, z->right);
  } else if (z->right == NIL) {
    x = z->left;
    transplant(root, z, z->left);
  } else {
    y = minimum(z->right);
    yColor = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      transplant(root, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(root, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  free(z);
  if (yColor == 'B') {
    deleteFixup(root, x);
  }
}

void deleteValue(Node** root, int key) {
  Node* z = search(*root, key);
  if (z != NIL) {
    deleteNode(root, z);
  }
}

void inorder(Node* node) {
  if (node == NIL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  NIL->color = 'B';

  int values[7] = {10, 5, 15, 3, 7, 12, 20};
  Node* root = NIL;
  for (int i = 0; i < 7; i++) {
    insert(&root, values[i]);
  }
  inorder(root);
  printf("\\n");

  int keys[5] = {3, 5, 15, 10, 7};
  for (int i = 0; i < 5; i++) {
    deleteValue(&root, keys[i]);
    inorder(root);
    printf("\\n");
  }

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  char color;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

Node nil;
Node* NIL = &nil;

Node* createNode(int data) {
  trace_line(16);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(17);
  n->data = data;
  trace_line(18);
  n->color = 'R';
  trace_line(19);
  n->left = NIL;
  trace_line(20);
  n->right = NIL;
  trace_line(21);
  n->parent = NIL;
  trace_btree_node("T", n, n->data);
  trace_btree_color("T", n, "R");
  trace_line(22);
  return n;
}

void leftRotate(Node** root, Node* x) {
  trace_line(26);
  Node* y = x->right;
  trace_line(27);
  x->right = y->left;
  trace_btree_right("T", x, x->right == NIL ? NULL : x->right);
  trace_line(28);
  if (y->left != NIL) {
    trace_line(29);
    y->left->parent = x;
  }
  trace_line(31);
  y->parent = x->parent;
  trace_line(32);
  if (x->parent == NIL) {
    trace_line(33);
    *root = y;
  } else if (x == x->parent->left) {
    trace_line(35);
    x->parent->left = y;
    trace_btree_left("T", x->parent, y);
  } else {
    trace_line(37);
    x->parent->right = y;
    trace_btree_right("T", x->parent, y);
  }
  trace_line(39);
  y->left = x;
  trace_btree_left("T", y, x);
  trace_line(40);
  x->parent = y;
}

void rightRotate(Node** root, Node* y) {
  trace_line(44);
  Node* x = y->left;
  trace_line(45);
  y->left = x->right;
  trace_btree_left("T", y, y->left == NIL ? NULL : y->left);
  trace_line(46);
  if (x->right != NIL) {
    trace_line(47);
    x->right->parent = y;
  }
  trace_line(49);
  x->parent = y->parent;
  trace_line(50);
  if (y->parent == NIL) {
    trace_line(51);
    *root = x;
  } else if (y == y->parent->left) {
    trace_line(53);
    y->parent->left = x;
    trace_btree_left("T", y->parent, x);
  } else {
    trace_line(55);
    y->parent->right = x;
    trace_btree_right("T", y->parent, x);
  }
  trace_line(57);
  x->right = y;
  trace_btree_right("T", x, y);
  trace_line(58);
  y->parent = x;
}

void insertFixup(Node** root, Node* z) {
  trace_line(62);
  while (z->parent->color == 'R') {
    trace_line(62);
    trace_btree_highlight("T", z);
    trace_line(63);
    if (z->parent == z->parent->parent->left) {
      trace_line(64);
      Node* u = z->parent->parent->right;
      trace_line(65);
      if (u->color == 'R') {
        trace_line(66);
        z->parent->color = 'B';
        trace_btree_color("T", z->parent, "B");
        trace_line(67);
        u->color = 'B';
        trace_btree_color("T", u, "B");
        trace_line(68);
        z->parent->parent->color = 'R';
        trace_btree_color("T", z->parent->parent, "R");
        trace_line(69);
        z = z->parent->parent;
      } else {
        trace_line(71);
        if (z == z->parent->right) {
          trace_line(72);
          z = z->parent;
          trace_line(73);
          leftRotate(root, z);
        }
        trace_line(75);
        z->parent->color = 'B';
        trace_btree_color("T", z->parent, "B");
        trace_line(76);
        z->parent->parent->color = 'R';
        trace_btree_color("T", z->parent->parent, "R");
        trace_line(77);
        rightRotate(root, z->parent->parent);
      }
    } else {
      trace_line(80);
      Node* u = z->parent->parent->left;
      trace_line(81);
      if (u->color == 'R') {
        trace_line(82);
        z->parent->color = 'B';
        trace_btree_color("T", z->parent, "B");
        trace_line(83);
        u->color = 'B';
        trace_btree_color("T", u, "B");
        trace_line(84);
        z->parent->parent->color = 'R';
        trace_btree_color("T", z->parent->parent, "R");
        trace_line(85);
        z = z->parent->parent;
      } else {
        trace_line(87);
        if (z == z->parent->left) {
          trace_line(88);
          z = z->parent;
          trace_line(89);
          rightRotate(root, z);
        }
        trace_line(91);
        z->parent->color = 'B';
        trace_btree_color("T", z->parent, "B");
        trace_line(92);
        z->parent->parent->color = 'R';
        trace_btree_color("T", z->parent->parent, "R");
        trace_line(93);
        leftRotate(root, z->parent->parent);
      }
    }
  }
  trace_line(97);
  (*root)->color = 'B';
  trace_btree_color("T", *root, "B");
}

void insert(Node** root, int data) {
  trace_line(101);
  Node* z = createNode(data);
  trace_line(102);
  Node* y = NIL;
  trace_line(103);
  Node* x = *root;
  trace_line(104);
  while (x != NIL) {
    trace_line(104);
    trace_btree_highlight("T", x);
    trace_line(105);
    y = x;
    trace_line(106);
    if (z->data < x->data) {
      trace_line(107);
      x = x->left;
    } else {
      trace_line(109);
      x = x->right;
    }
  }
  trace_line(112);
  z->parent = y;
  trace_line(113);
  if (y == NIL) {
    trace_line(114);
    *root = z;
  } else if (z->data < y->data) {
    trace_line(116);
    y->left = z;
    trace_btree_left("T", y, z);
  } else {
    trace_line(118);
    y->right = z;
    trace_btree_right("T", y, z);
  }
  trace_line(120);
  insertFixup(root, z);
}

Node* search(Node* root, int key) {
  trace_line(124);
  Node* cur = root;
  trace_btree_pointer("T", "cur", cur == NIL ? NULL : cur);
  trace_line(125);
  while (cur != NIL && cur->data != key) {
    trace_line(125);
    trace_btree_highlight("T", cur);
    trace_line(126);
    if (key < cur->data) {
      trace_line(127);
      cur = cur->left;
    } else {
      trace_line(129);
      cur = cur->right;
    }
    trace_btree_pointer("T", "cur", cur == NIL ? NULL : cur);
  }
  trace_btree_pointer("T", "cur", NULL);
  trace_line(132);
  return cur;
}

Node* minimum(Node* x) {
  trace_line(136);
  while (x->left != NIL) {
    trace_line(136);
    trace_btree_highlight("T", x);
    trace_line(137);
    x = x->left;
  }
  trace_btree_highlight("T", x);
  trace_line(139);
  return x;
}

void transplant(Node** root, Node* u, Node* v) {
  trace_line(143);
  if (u->parent == NIL) {
    trace_line(144);
    *root = v;
  } else if (u == u->parent->left) {
    trace_line(146);
    u->parent->left = v;
    trace_btree_left("T", u->parent, v == NIL ? NULL : v);
  } else {
    trace_line(148);
    u->parent->right = v;
    trace_btree_right("T", u->parent, v == NIL ? NULL : v);
  }
  trace_line(150);
  v->parent = u->parent;
}

void deleteFixup(Node** root, Node* x) {
  trace_line(154);
  while (x != *root && x->color == 'B') {
    trace_line(154);
    trace_btree_highlight("T", x == NIL ? NULL : x);
    trace_line(155);
    if (x == x->parent->left) {
      trace_line(156);
      Node* w = x->parent->right;
      trace_btree_pointer("T", "w", w == NIL ? NULL : w);
      trace_line(157);
      if (w->color == 'R') {
        trace_line(158);
        w->color = 'B';
        trace_btree_color("T", w, "B");
        trace_line(159);
        x->parent->color = 'R';
        trace_btree_color("T", x->parent, "R");
        trace_line(160);
        leftRotate(root, x->parent);
        trace_line(161);
        w = x->parent->right;
        trace_btree_pointer("T", "w", w == NIL ? NULL : w);
      }
      trace_line(163);
      if (w->left->color == 'B' && w->right->color == 'B') {
        trace_line(164);
        w->color = 'R';
        trace_btree_color("T", w, "R");
        trace_line(165);
        x = x->parent;
      } else {
        trace_line(167);
        if (w->right->color == 'B') {
          trace_line(168);
          w->left->color = 'B';
          trace_btree_color("T", w->left == NIL ? NULL : w->left, "B");
          trace_line(169);
          w->color = 'R';
          trace_btree_color("T", w, "R");
          trace_line(170);
          rightRotate(root, w);
          trace_line(171);
          w = x->parent->right;
          trace_btree_pointer("T", "w", w == NIL ? NULL : w);
        }
        trace_line(173);
        w->color = x->parent->color;
        trace_btree_color("T", w, w->color == 'R' ? "R" : "B");
        trace_line(174);
        x->parent->color = 'B';
        trace_btree_color("T", x->parent, "B");
        trace_line(175);
        w->right->color = 'B';
        trace_btree_color("T", w->right == NIL ? NULL : w->right, "B");
        trace_line(176);
        leftRotate(root, x->parent);
        trace_line(177);
        x = *root;
      }
    } else {
      trace_line(180);
      Node* w = x->parent->left;
      trace_btree_pointer("T", "w", w == NIL ? NULL : w);
      trace_line(181);
      if (w->color == 'R') {
        trace_line(182);
        w->color = 'B';
        trace_btree_color("T", w, "B");
        trace_line(183);
        x->parent->color = 'R';
        trace_btree_color("T", x->parent, "R");
        trace_line(184);
        rightRotate(root, x->parent);
        trace_line(185);
        w = x->parent->left;
        trace_btree_pointer("T", "w", w == NIL ? NULL : w);
      }
      trace_line(187);
      if (w->right->color == 'B' && w->left->color == 'B') {
        trace_line(188);
        w->color = 'R';
        trace_btree_color("T", w, "R");
        trace_line(189);
        x = x->parent;
      } else {
        trace_line(191);
        if (w->left->color == 'B') {
          trace_line(192);
          w->right->color = 'B';
          trace_btree_color("T", w->right == NIL ? NULL : w->right, "B");
          trace_line(193);
          w->color = 'R';
          trace_btree_color("T", w, "R");
          trace_line(194);
          leftRotate(root, w);
          trace_line(195);
          w = x->parent->left;
          trace_btree_pointer("T", "w", w == NIL ? NULL : w);
        }
        trace_line(197);
        w->color = x->parent->color;
        trace_btree_color("T", w, w->color == 'R' ? "R" : "B");
        trace_line(198);
        x->parent->color = 'B';
        trace_btree_color("T", x->parent, "B");
        trace_line(199);
        w->left->color = 'B';
        trace_btree_color("T", w->left == NIL ? NULL : w->left, "B");
        trace_line(200);
        rightRotate(root, x->parent);
        trace_line(201);
        x = *root;
      }
    }
  }
  trace_btree_pointer("T", "w", NULL);
  trace_line(205);
  x->color = 'B';
  trace_btree_color("T", x == NIL ? NULL : x, "B");
}

void deleteNode(Node** root, Node* z) {
  trace_btree_highlight("T", z);
  trace_line(209);
  Node* y = z;
  trace_line(210);
  Node* x;
  trace_line(211);
  char yColor = y->color;
  trace_line(212);
  if (z->left == NIL) {
    trace_line(213);
    x = z->right;
    trace_line(214);
    transplant(root, z, z->right);
  } else if (z->right == NIL) {
    trace_line(216);
    x = z->left;
    trace_line(217);
    transplant(root, z, z->left);
  } else {
    trace_line(219);
    y = minimum(z->right);
    trace_btree_pointer("T", "y", y);
    trace_line(220);
    yColor = y->color;
    trace_line(221);
    x = y->right;
    trace_line(222);
    if (y->parent == z) {
      trace_line(223);
      x->parent = y;
    } else {
      trace_line(225);
      transplant(root, y, y->right);
      trace_line(226);
      y->right = z->right;
      trace_btree_right("T", y, y->right == NIL ? NULL : y->right);
      trace_line(227);
      y->right->parent = y;
    }
    trace_line(229);
    transplant(root, z, y);
    trace_line(230);
    y->left = z->left;
    trace_btree_left("T", y, y->left == NIL ? NULL : y->left);
    trace_line(231);
    y->left->parent = y;
    trace_line(232);
    y->color = z->color;
    trace_btree_color("T", y, y->color == 'R' ? "R" : "B");
    trace_btree_pointer("T", "y", NULL);
  }
  trace_btree_delete("T", z);
  trace_line(234);
  free(z);
  trace_line(235);
  if (yColor == 'B') {
    trace_line(236);
    deleteFixup(root, x);
  }
}

void deleteValue(Node** root, int key) {
  trace_line(241);
  Node* z = search(*root, key);
  trace_line(242);
  if (z != NIL) {
    trace_line(243);
    deleteNode(root, z);
  }
}

void inorder(Node* node) {
  trace_line(248);
  if (node == NIL) return;
  trace_line(249);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(250);
  printf("%d ", node->data);
  trace_line(251);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");
  trace_line(255);
  NIL->color = 'B';

  trace_line(257);
  int values[7] = {10, 5, 15, 3, 7, 12, 20};
  trace_line(258);
  Node* root = NIL;
  trace_line(259);
  for (int i = 0; i < 7; i++) {
    trace_line(259);
    trace_line(260);
    insert(&root, values[i]);
  }
  trace_line(262);
  inorder(root);
  trace_line(263);
  printf("\\n");

  trace_line(265);
  int keys[5] = {3, 5, 15, 10, 7};
  trace_line(266);
  for (int i = 0; i < 5; i++) {
    trace_line(266);
    trace_line(267);
    deleteValue(&root, keys[i]);
    trace_line(268);
    inorder(root);
    trace_line(269);
    printf("\\n");
  }

  trace_line(272);
  return 0;
}
`,
      },
      {
        name: "N-ary Tree",
        code: `#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10

typedef struct Node {
  char id[10];
  char value[10];
  struct Node* children[MAX_CHILDREN];
  int childCount;
} Node;

Node* createNode(const char* id, const char* value) {
  Node* n = (Node*)malloc(sizeof(Node));
  strcpy(n->id, id);
  strcpy(n->value, value);
  n->childCount = 0;
  return n;
}

void addChild(Node* parent, Node* child) {
  parent->children[parent->childCount++] = child;
}

void preorder(Node* node) {
  if (node == NULL) return;
  printf("%s ", node->value);
  for (int i = 0; i < node->childCount; i++) {
    preorder(node->children[i]);
  }
}

int main() {
  Node* R = createNode("R", "R");

  Node* n1 = createNode("n1", "1");
  Node* n2 = createNode("n2", "2");
  Node* n3 = createNode("n3", "3");
  addChild(R, n1);
  addChild(R, n2);
  addChild(R, n3);

  Node* n4 = createNode("n4", "4");
  Node* n5 = createNode("n5", "5");
  addChild(n1, n4);
  addChild(n1, n5);

  Node* n6 = createNode("n6", "6");
  addChild(n2, n6);

  Node* n7 = createNode("n7", "7");
  Node* n8 = createNode("n8", "8");
  addChild(n3, n7);
  addChild(n3, n8);

  Node* n9 = createNode("n9", "9");
  addChild(n4, n9);

  preorder(R);

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tracer.h"

#define MAX_CHILDREN 10

typedef struct Node {
  char id[10];
  char value[10];
  struct Node* children[MAX_CHILDREN];
  int childCount;
} Node;

Node* createNode(const char* id, const char* value) {
  trace_line(15);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(16);
  strcpy(n->id, id);
  trace_line(17);
  strcpy(n->value, value);
  trace_line(18);
  n->childCount = 0;
  trace_line(19);
  return n;
}

void addChild(Node* parent, Node* child) {
  trace_line(23);
  parent->children[parent->childCount++] = child;
}

void preorder(Node* node) {
  trace_line(27);
  if (node == NULL) return;
  trace_tree_highlight("T", node->id);
  trace_line(28);
  printf("%s ", node->value);
  trace_line(29);
  for (int i = 0; i < node->childCount; i++) {
    trace_line(29);
    trace_line(30);
    preorder(node->children[i]);
  }
}

int main() {
  trace_tree_init("T");

  trace_line(35);
  Node* R = createNode("R", "R");
  trace_tree_node("T", R->id, R->value);

  trace_line(37);
  Node* n1 = createNode("n1", "1");
  trace_tree_node("T", n1->id, n1->value);
  trace_line(38);
  Node* n2 = createNode("n2", "2");
  trace_tree_node("T", n2->id, n2->value);
  trace_line(39);
  Node* n3 = createNode("n3", "3");
  trace_tree_node("T", n3->id, n3->value);
  trace_line(40);
  addChild(R, n1);
  trace_tree_edge("T", R->id, n1->id);
  trace_line(41);
  addChild(R, n2);
  trace_tree_edge("T", R->id, n2->id);
  trace_line(42);
  addChild(R, n3);
  trace_tree_edge("T", R->id, n3->id);

  trace_line(44);
  Node* n4 = createNode("n4", "4");
  trace_tree_node("T", n4->id, n4->value);
  trace_line(45);
  Node* n5 = createNode("n5", "5");
  trace_tree_node("T", n5->id, n5->value);
  trace_line(46);
  addChild(n1, n4);
  trace_tree_edge("T", n1->id, n4->id);
  trace_line(47);
  addChild(n1, n5);
  trace_tree_edge("T", n1->id, n5->id);

  trace_line(49);
  Node* n6 = createNode("n6", "6");
  trace_tree_node("T", n6->id, n6->value);
  trace_line(50);
  addChild(n2, n6);
  trace_tree_edge("T", n2->id, n6->id);

  trace_line(52);
  Node* n7 = createNode("n7", "7");
  trace_tree_node("T", n7->id, n7->value);
  trace_line(53);
  Node* n8 = createNode("n8", "8");
  trace_tree_node("T", n8->id, n8->value);
  trace_line(54);
  addChild(n3, n7);
  trace_tree_edge("T", n3->id, n7->id);
  trace_line(55);
  addChild(n3, n8);
  trace_tree_edge("T", n3->id, n8->id);

  trace_line(57);
  Node* n9 = createNode("n9", "9");
  trace_tree_node("T", n9->id, n9->value);
  trace_line(58);
  addChild(n4, n9);
  trace_tree_edge("T", n4->id, n9->id);

  trace_line(60);
  preorder(R);

  trace_line(62);
  return 0;
}
`,
      },
    ],
  },
  {
    name: "Graphs",
    samples: [
      {
        name: "Graph (BFS)",
        code: `#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct AdjNode {
  int index;
  struct AdjNode* next;
} AdjNode;

typedef struct {
  char id[20];
  AdjNode* head;
} Vertex;

typedef struct {
  Vertex vertices[MAX];
  int size;
} Graph;

void initGraph(Graph* g) { g->size = 0; }

int addVertex(Graph* g, char* id) {
  strcpy(g->vertices[g->size].id, id);
  g->vertices[g->size].head = NULL;
  g->size++;
  return g->size - 1;
}

void addEdge(Graph* g, int from, int to) {
  AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
  newNode->index = to;
  newNode->next = g->vertices[from].head;
  g->vertices[from].head = newNode;
}

void bfs(Graph* g, int start) {
  int visited[MAX] = {0};
  int queue[MAX];
  int front = 0, rear = 0;

  visited[start] = 1;
  queue[rear++] = start;

  while (front < rear) {
    int current = queue[front++];

    AdjNode* temp = g->vertices[current].head;
    while (temp != NULL) {
      if (!visited[temp->index]) {
        visited[temp->index] = 1;
        queue[rear++] = temp->index;
      }
      temp = temp->next;
    }
  }
}

int main() {
  Graph g;
  initGraph(&g);

  int A = addVertex(&g, "A");
  int B = addVertex(&g, "B");
  int C = addVertex(&g, "C");
  int D = addVertex(&g, "D");
  int E = addVertex(&g, "E");

  addEdge(&g, A, B);
  addEdge(&g, A, C);
  addEdge(&g, B, D);
  addEdge(&g, C, D);
  addEdge(&g, D, E);

  bfs(&g, A);

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tracer.h"

#define MAX 10

typedef struct AdjNode {
  int index;
  struct AdjNode* next;
} AdjNode;

typedef struct {
  char id[20];
  AdjNode* head;
} Vertex;

typedef struct {
  Vertex vertices[MAX];
  int size;
} Graph;

void initGraph(Graph* g) {
  trace_line(22);
  g->size = 0;
}

int addVertex(Graph* g, char* id) {
  trace_line(25);
  strcpy(g->vertices[g->size].id, id);
  trace_line(26);
  g->vertices[g->size].head = NULL;
  trace_graph_node("G", id);
  trace_line(27);
  g->size++;
  trace_line(28);
  return g->size - 1;
}

void addEdge(Graph* g, int from, int to) {
  trace_line(32);
  AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
  trace_line(33);
  newNode->index = to;
  trace_line(34);
  newNode->next = g->vertices[from].head;
  trace_line(35);
  g->vertices[from].head = newNode;
  trace_graph_edge("G", g->vertices[from].id, g->vertices[to].id);
}

void bfs(Graph* g, int start) {
  int visited[MAX] = {0};
  trace_line(39);
  trace_array_init("visited", MAX);
  for (int _i = 0; _i < MAX; _i++) { trace_array("visited", _i, visited[_i]); }

  trace_queue_init("Q");

  int queue[MAX];
  trace_line(40);

  int front = 0, rear = 0;
  trace_line(41);
  trace_var_init("front", front);
  trace_var_init("rear", rear);

  trace_line(43);
  visited[start] = 1;
  trace_array("visited", start, visited[start]);
  trace_line(44);
  queue[rear++] = start;
  trace_var("rear", rear);
  trace_queue_enqueue("Q", start);

  trace_line(46);
  while (front < rear) {
    trace_line(46);
    trace_line(47);
    int current = queue[front++];
    trace_var_init("current", current);
    trace_var("front", front);
    trace_queue_dequeue("Q");
    trace_graph_highlight("G", g->vertices[current].id);

    trace_line(49);
    AdjNode* temp = g->vertices[current].head;
    trace_line(50);
    while (temp != NULL) {
      trace_line(50);
      trace_line(51);
      if (!visited[temp->index]) {
        trace_line(52);
        visited[temp->index] = 1;
        trace_array("visited", temp->index, visited[temp->index]);
        trace_line(53);
        queue[rear++] = temp->index;
        trace_var("rear", rear);
        trace_queue_enqueue("Q", temp->index);
      }
      trace_line(55);
      temp = temp->next;
    }
  }
}

int main() {
  trace_graph_init("G");

  trace_line(61);
  Graph g;
  trace_line(62);
  initGraph(&g);

  trace_line(64);
  int A = addVertex(&g, "A");
  trace_line(65);
  int B = addVertex(&g, "B");
  trace_line(66);
  int C = addVertex(&g, "C");
  trace_line(67);
  int D = addVertex(&g, "D");
  trace_line(68);
  int E = addVertex(&g, "E");

  trace_line(70);
  addEdge(&g, A, B);
  trace_line(71);
  addEdge(&g, A, C);
  trace_line(72);
  addEdge(&g, B, D);
  trace_line(73);
  addEdge(&g, C, D);
  trace_line(74);
  addEdge(&g, D, E);

  trace_line(76);
  bfs(&g, A);

  trace_line(78);
  return 0;
}
`,
      },
      {
        name: "Graph (DFS)",
        code: `#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct AdjNode {
  int index;
  struct AdjNode* next;
} AdjNode;

typedef struct {
  char id[20];
  AdjNode* head;
} Vertex;

typedef struct {
  Vertex vertices[MAX];
  int size;
} Graph;

void initGraph(Graph* g) { g->size = 0; }

int addVertex(Graph* g, char* id) {
  strcpy(g->vertices[g->size].id, id);
  g->vertices[g->size].head = NULL;
  g->size++;
  return g->size - 1;
}

void addEdge(Graph* g, int from, int to) {
  AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
  newNode->index = to;
  newNode->next = g->vertices[from].head;
  g->vertices[from].head = newNode;
}

int visited[MAX];

void dfs(Graph* g, int v) {
  visited[v] = 1;

  AdjNode* temp = g->vertices[v].head;
  while (temp != NULL) {
    if (!visited[temp->index]) {
      dfs(g, temp->index);
    }
    temp = temp->next;
  }
}

int main() {
  Graph g;
  initGraph(&g);

  int A = addVertex(&g, "A");
  int B = addVertex(&g, "B");
  int C = addVertex(&g, "C");
  int D = addVertex(&g, "D");
  int E = addVertex(&g, "E");

  addEdge(&g, A, B);
  addEdge(&g, A, C);
  addEdge(&g, B, D);
  addEdge(&g, C, D);
  addEdge(&g, D, E);

  for (int i = 0; i < MAX; i++) {
    visited[i] = 0;
  }

  dfs(&g, A);

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tracer.h"

#define MAX 10

typedef struct AdjNode {
  int index;
  struct AdjNode* next;
} AdjNode;

typedef struct {
  char id[20];
  AdjNode* head;
} Vertex;

typedef struct {
  Vertex vertices[MAX];
  int size;
} Graph;

void initGraph(Graph* g) {
  trace_line(22);
  g->size = 0;
}

int addVertex(Graph* g, char* id) {
  trace_line(25);
  strcpy(g->vertices[g->size].id, id);
  trace_line(26);
  g->vertices[g->size].head = NULL;
  trace_graph_node("G", id);
  trace_line(27);
  g->size++;
  trace_line(28);
  return g->size - 1;
}

void addEdge(Graph* g, int from, int to) {
  trace_line(32);
  AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
  trace_line(33);
  newNode->index = to;
  trace_line(34);
  newNode->next = g->vertices[from].head;
  trace_line(35);
  g->vertices[from].head = newNode;
  trace_graph_edge("G", g->vertices[from].id, g->vertices[to].id);
}

int visited[MAX];

void dfs(Graph* g, int v) {
  trace_stack_push("CallStack", v);
  trace_line(41);
  visited[v] = 1;
  trace_array("visited", v, visited[v]);
  trace_var_init("v", v);
  trace_graph_highlight("G", g->vertices[v].id);

  trace_line(43);
  AdjNode* temp = g->vertices[v].head;
  trace_line(44);
  while (temp != NULL) {
    trace_line(44);
    trace_line(45);
    if (!visited[temp->index]) {
      trace_line(46);
      dfs(g, temp->index);
    }
    trace_line(48);
    temp = temp->next;
  }
  trace_stack_pop("CallStack");
}

int main() {
  trace_graph_init("G");

  trace_line(53);
  Graph g;
  trace_line(54);
  initGraph(&g);

  trace_line(56);
  int A = addVertex(&g, "A");
  trace_line(57);
  int B = addVertex(&g, "B");
  trace_line(58);
  int C = addVertex(&g, "C");
  trace_line(59);
  int D = addVertex(&g, "D");
  trace_line(60);
  int E = addVertex(&g, "E");

  trace_line(62);
  addEdge(&g, A, B);
  trace_line(63);
  addEdge(&g, A, C);
  trace_line(64);
  addEdge(&g, B, D);
  trace_line(65);
  addEdge(&g, C, D);
  trace_line(66);
  addEdge(&g, D, E);

  trace_array_init("visited", MAX);
  trace_stack_init("CallStack");
  trace_line(68);
  for (int i = 0; i < MAX; i++) {
    trace_line(68);
    trace_line(69);
    visited[i] = 0;
    trace_array("visited", i, visited[i]);
  }

  trace_line(72);
  dfs(&g, A);

  trace_line(74);
  return 0;
}
`,
      },
    ],
  },
  {
    name: "Recursion",
    samples: [
      {
        name: "Fibonacci",
        code: `#include <stdio.h>

int fib(int n) {
  if (n < 2) {
    return n;
  }
  int result = fib(n - 1) + fib(n - 2);
  return result;
}

int main() {
  int n = 5;
  int answer = fib(n);
  printf("fib(%d) = %d\\n", n, answer);
  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

int fib(int n) {
  trace_rec_enter("calls", "fib");
  trace_rec_param("calls", "n", n);
  trace_line(4);
  if (n < 2) {
    trace_line(5);
    trace_rec_return("calls", n);
    return n;
  }
  trace_line(7);
  int result = fib(n - 1) + fib(n - 2);
  trace_line(8);
  trace_rec_return("calls", result);
  return result;
}

int main() {
  trace_rec_init("calls");

  trace_line(12);
  int n = 5;
  trace_var_init("n", n);
  trace_line(13);
  int answer = fib(n);
  trace_var_init("answer", answer);
  trace_line(14);
  printf("fib(%d) = %d\\n", n, answer);
  trace_line(15);
  return 0;
}
`,
      },
      {
        name: "Quicksort",
        code: `#include <stdio.h>

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = low - 1;
  for (int j = low; j < high; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return i + 1;
}

void quicksort(int arr[], int low, int high) {
  if (low < high) {
    int p = partition(arr, low, high);
    quicksort(arr, low, p - 1);
    quicksort(arr, p + 1, high);
  }
}

int main() {
  int arr[6] = {5, 2, 8, 1, 9, 3};
  int n = 6;
  quicksort(arr, 0, n - 1);
  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

void swap(int* a, int* b) {
  trace_line(4);
  int t = *a;
  trace_line(5);
  *a = *b;
  trace_line(6);
  *b = t;
}

int partition(int arr[], int low, int high) {
  trace_line(10);
  int pivot = arr[high];
  trace_var_init("pivot", pivot);
  trace_array_highlight("arr", high);
  trace_line(11);
  int i = low - 1;
  trace_var_init("i", i);
  trace_line(12);
  for (int j = low; j < high; j++) {
    trace_line(12);
    trace_var_init("j", j);
    trace_line(13);
    if (arr[j] < pivot) {
      trace_line(14);
      i++;
      trace_var("i", i);
      trace_line(15);
      swap(&arr[i], &arr[j]);
      trace_array("arr", i, arr[i]);
      trace_array("arr", j, arr[j]);
    }
  }
  trace_line(18);
  swap(&arr[i + 1], &arr[high]);
  trace_array("arr", i + 1, arr[i + 1]);
  trace_array("arr", high, arr[high]);
  trace_line(19);
  return i + 1;
}

void quicksort(int arr[], int low, int high) {
  trace_rec_enter("calls", "quicksort");
  trace_rec_param("calls", "low", low);
  trace_rec_param("calls", "high", high);
  trace_line(23);
  if (low < high) {
    trace_line(24);
    int p = partition(arr, low, high);
    trace_var_init("p", p);
    trace_array_highlight("arr", p);
    trace_line(25);
    quicksort(arr, low, p - 1);
    trace_line(26);
    quicksort(arr, p + 1, high);
  }
  trace_rec_exit("calls");
}

int main() {
  trace_rec_init("calls");
  trace_array_init("arr", 6);

  trace_line(31);
  int arr[6] = {5, 2, 8, 1, 9, 3};
  trace_array("arr", 0, arr[0]);
  trace_array("arr", 1, arr[1]);
  trace_array("arr", 2, arr[2]);
  trace_array("arr", 3, arr[3]);
  trace_array("arr", 4, arr[4]);
  trace_array("arr", 5, arr[5]);
  trace_line(32);
  int n = 6;
  trace_var_init("n", n);
  trace_line(33);
  quicksort(arr, 0, n - 1);
  trace_line(34);
  return 0;
}
`,
      },
    ],
  },
  {
    name: "Sorting Algorithms",
    samples: [
      {
        name: "Bubble Sort",
        stdin: "5 3 7 1 9 4",
        code: `#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);

  int arr[20];
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  // Bubble Sort
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

int main() {
  int n;
  trace_line(5);
  scanf("%d", &n);
  trace_var_init("n", n);

  int arr[20];
  trace_line(7);
  trace_array_init_bars("arr", n);
  trace_line(8);
  for (int i = 0; i < n; i++) {
    trace_line(8);
    trace_var_init("i", i);
    trace_line(9);
    scanf("%d", &arr[i]);
    trace_array("arr", i, arr[i]);
  }

  // Bubble Sort
  trace_line(13);
  for (int i = 0; i < n - 1; i++) {
    trace_line(13);
    trace_var_init("i", i);
    trace_array_cell("arr", "i", i);
    trace_line(14);
    for (int j = 0; j < n - 1 - i; j++) {
      trace_line(14);
      trace_var_init("j", j);
      trace_array_cell("arr", "j", j);
      trace_array_highlight("arr", j);
      trace_line(15);
      if (arr[j] > arr[j + 1]) {
        trace_line(16);
        int temp = arr[j];
        trace_var_init("temp", temp);
        trace_line(17);
        arr[j] = arr[j + 1];
        trace_array("arr", j, arr[j]);
        trace_line(18);
        arr[j + 1] = temp;
        trace_array("arr", j + 1, arr[j + 1]);
      }
    }
  }

  trace_line(23);
  return 0;
}
`,
      },
      {
        name: "Selection Sort",
        stdin: "5 8 3 6 1 4",
        code: `#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);

  int arr[20];
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  // Selection Sort
  for (int i = 0; i < n - 1; i++) {
    int minIdx = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[minIdx]) {
        minIdx = j;
      }
    }
    int temp = arr[i];
    arr[i] = arr[minIdx];
    arr[minIdx] = temp;
  }

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

int main() {
  int n;
  trace_line(5);
  scanf("%d", &n);
  trace_var_init("n", n);

  int arr[20];
  trace_line(7);
  trace_array_init_bars("arr", n);
  trace_line(8);
  for (int i = 0; i < n; i++) {
    trace_line(8);
    trace_var_init("i", i);
    trace_line(9);
    scanf("%d", &arr[i]);
    trace_array("arr", i, arr[i]);
  }

  // Selection Sort
  trace_line(14);
  for (int i = 0; i < n - 1; i++) {
    trace_line(14);
    trace_var_init("i", i);
    trace_array_cell("arr", "i", i);
    trace_line(15);
    int minIdx = i;
    trace_var_init("minIdx", minIdx);
    trace_array_cell("arr", "min", minIdx);
    trace_line(16);
    for (int j = i + 1; j < n; j++) {
      trace_line(16);
      trace_var_init("j", j);
      trace_array_cell("arr", "j", j);
      trace_array_highlight("arr", j);
      trace_line(17);
      if (arr[j] < arr[minIdx]) {
        trace_line(18);
        minIdx = j;
        trace_var("minIdx", minIdx);
        trace_array_cell("arr", "min", minIdx);
      }
    }
    trace_line(21);
    int temp = arr[i];
    trace_var_init("temp", temp);
    trace_array_highlight("arr", i);
    trace_line(22);
    arr[i] = arr[minIdx];
    trace_array("arr", i, arr[i]);
    trace_line(23);
    arr[minIdx] = temp;
    trace_array("arr", minIdx, arr[minIdx]);
  }

  trace_line(26);
  return 0;
}
`,
      },
      {
        name: "Insertion Sort",
        stdin: "5 12 4 7 2 9",
        code: `#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);

  int arr[20];
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  // Insertion Sort
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

int main() {
  int n;
  trace_line(5);
  scanf("%d", &n);
  trace_var_init("n", n);

  int arr[20];
  trace_line(7);
  trace_array_init_bars("arr", n);
  trace_line(8);
  for (int i = 0; i < n; i++) {
    trace_line(8);
    trace_var_init("i", i);
    trace_line(9);
    scanf("%d", &arr[i]);
    trace_array("arr", i, arr[i]);
  }

  // Insertion Sort
  trace_line(13);
  for (int i = 1; i < n; i++) {
    trace_line(13);
    trace_var_init("i", i);
    trace_array_cell("arr", "i", i);
    trace_line(14);
    int key = arr[i];
    trace_var_init("key", key);
    trace_array_highlight("arr", i);
    trace_line(15);
    int j = i - 1;
    trace_var_init("j", j);
    trace_array_cell("arr", "j", j);
    trace_line(16);
    while (j >= 0 && arr[j] > key) {
      trace_line(16);
      trace_var("j", j);
      trace_array_cell("arr", "j", j);
      trace_array_highlight("arr", j);
      trace_line(17);
      arr[j + 1] = arr[j];
      trace_array("arr", j + 1, arr[j + 1]);
      trace_line(18);
      j--;
      trace_var("j", j);
    }
    trace_line(20);
    arr[j + 1] = key;
    trace_array("arr", j + 1, arr[j + 1]);
  }

  trace_line(23);
  return 0;
}
`,
      },
      {
        name: "Merge Sort",
        stdin: "6 5 2 8 1 9 3",
        code: `#include <stdio.h>

int arr[20];
int n;

void merge(int l, int m, int r) {
  int temp[20];
  int i = l, j = m + 1, k = l;

  while (i <= m && j <= r) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }
  while (i <= m) temp[k++] = arr[i++];
  while (j <= r) temp[k++] = arr[j++];

  for (int x = l; x <= r; x++) {
    arr[x] = temp[x];
  }
}

void mergeSort(int l, int r) {
  if (l >= r) return;
  int m = (l + r) / 2;
  mergeSort(l, m);
  mergeSort(m + 1, r);
  merge(l, m, r);
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  mergeSort(0, n - 1);

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

int arr[20];
int n;

void merge(int l, int m, int r) {
  trace_var_init("l", l);
  trace_var_init("m", m);
  trace_var_init("r", r);
  int temp[20];
  int i = l, j = m + 1, k = l;
  trace_line(8);
  trace_var_init("i", i);
  trace_array_cell("arr", "i", i);
  trace_var_init("j", j);
  trace_array_cell("arr", "j", j);
  trace_var_init("k", k);

  trace_line(10);
  while (i <= m && j <= r) {
    trace_line(10);
    trace_array_highlight("arr", i);
    trace_array_highlight("arr", j);
    trace_line(11);
    if (arr[i] <= arr[j]) {
      trace_line(12);
      temp[k++] = arr[i++];
      trace_var("i", i);
      trace_array_cell("arr", "i", i);
      trace_var("k", k);
    } else {
      trace_line(14);
      temp[k++] = arr[j++];
      trace_var("j", j);
      trace_array_cell("arr", "j", j);
      trace_var("k", k);
    }
  }
  trace_line(17);
  while (i <= m) {
    trace_line(17);
    temp[k++] = arr[i++];
    trace_var("i", i);
    trace_array_cell("arr", "i", i);
    trace_var("k", k);
  }
  trace_line(18);
  while (j <= r) {
    trace_line(18);
    temp[k++] = arr[j++];
    trace_var("j", j);
    trace_array_cell("arr", "j", j);
    trace_var("k", k);
  }

  trace_line(20);
  for (int x = l; x <= r; x++) {
    trace_line(20);
    trace_var_init("x", x);
    trace_array_cell("arr", "x", x);
    trace_line(21);
    arr[x] = temp[x];
    trace_array("arr", x, arr[x]);
  }
}

void mergeSort(int l, int r) {
  trace_var_init("l", l);
  trace_var_init("r", r);
  trace_line(26);
  if (l >= r) return;
  trace_line(27);
  int m = (l + r) / 2;
  trace_var_init("m", m);
  trace_line(28);
  mergeSort(l, m);
  trace_line(29);
  mergeSort(m + 1, r);
  trace_line(30);
  merge(l, m, r);
}

int main() {
  trace_line(34);
  scanf("%d", &n);
  trace_var_init("n", n);
  trace_array_init_bars("arr", n);
  trace_line(35);
  for (int i = 0; i < n; i++) {
    trace_line(35);
    trace_var_init("i", i);
    trace_line(36);
    scanf("%d", &arr[i]);
    trace_array("arr", i, arr[i]);
  }

  trace_line(39);
  mergeSort(0, n - 1);

  trace_line(41);
  return 0;
}
`,
      },
      {
        name: "Quick Sort",
        stdin: "6 7 2 9 1 6 3",
        code: `#include <stdio.h>

int arr[20];
int n;

void swap(int i, int j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

int partition(int low, int high) {
  int pivot = arr[high];
  int i = low - 1;
  for (int j = low; j < high; j++) {
    if (arr[j] <= pivot) {
      i++;
      swap(i, j);
    }
  }
  swap(i + 1, high);
  return i + 1;
}

void quickSort(int low, int high) {
  if (low < high) {
    int pi = partition(low, high);
    quickSort(low, pi - 1);
    quickSort(pi + 1, high);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  quickSort(0, n - 1);

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

int arr[20];
int n;

void swap(int i, int j) {
  trace_var_init("i", i);
  trace_var_init("j", j);
  trace_line(7);
  int temp = arr[i];
  trace_var_init("temp", temp);
  trace_line(8);
  arr[i] = arr[j];
  trace_array("arr", i, arr[i]);
  trace_line(9);
  arr[j] = temp;
  trace_array("arr", j, arr[j]);
}

int partition(int low, int high) {
  trace_var_init("low", low);
  trace_array_cell("arr", "low", low);
  trace_var_init("high", high);
  trace_array_cell("arr", "high", high);
  trace_line(13);
  int pivot = arr[high];
  trace_var_init("pivot", pivot);
  trace_array_highlight("arr", high);
  trace_line(14);
  int i = low - 1;
  trace_var_init("i", i);
  trace_line(15);
  for (int j = low; j < high; j++) {
    trace_line(15);
    trace_var_init("j", j);
    trace_array_cell("arr", "j", j);
    trace_array_highlight("arr", j);
    trace_line(16);
    if (arr[j] <= pivot) {
      trace_line(17);
      i++;
      trace_var("i", i);
      trace_array_cell("arr", "i", i);
      trace_line(18);
      swap(i, j);
    }
  }
  trace_line(21);
  swap(i + 1, high);
  trace_line(22);
  return i + 1;
}

void quickSort(int low, int high) {
  trace_var_init("low", low);
  trace_array_cell("arr", "low", low);
  trace_var_init("high", high);
  trace_array_cell("arr", "high", high);
  trace_line(26);
  if (low < high) {
    trace_line(27);
    int pi = partition(low, high);
    trace_var_init("pi", pi);
    trace_line(28);
    quickSort(low, pi - 1);
    trace_line(29);
    quickSort(pi + 1, high);
  }
}

int main() {
  trace_line(34);
  scanf("%d", &n);
  trace_var_init("n", n);
  trace_array_init_bars("arr", n);
  trace_line(35);
  for (int i = 0; i < n; i++) {
    trace_line(35);
    trace_var_init("i", i);
    trace_line(36);
    scanf("%d", &arr[i]);
    trace_array("arr", i, arr[i]);
  }

  trace_line(39);
  quickSort(0, n - 1);

  trace_line(41);
  return 0;
}
`,
      },
    ],
  },
  {
    name: "Search Algorithms",
    samples: [
      {
        name: "Linear Search",
        stdin: "5 3 7 1 9 4 9",
        code: `#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);

  int arr[20];
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  int target;
  scanf("%d", &target);

  // Linear Search
  int found = -1;
  for (int i = 0; i < n; i++) {
    if (arr[i] == target) {
      found = i;
      break;
    }
  }

  if (found >= 0) {
    printf("Found %d at index %d\\n", target, found);
  } else {
    printf("%d not found\\n", target);
  }

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

int main() {
  int n;
  trace_line(5);
  scanf("%d", &n);
  trace_var_init("n", n);

  int arr[20];
  trace_line(7);
  trace_array_init("arr", n);
  trace_line(8);
  for (int i = 0; i < n; i++) {
    trace_line(8);
    trace_var_init("i", i);
    trace_line(9);
    scanf("%d", &arr[i]);
    trace_array("arr", i, arr[i]);
  }

  int target;
  trace_line(13);
  scanf("%d", &target);
  trace_var_init("target", target);

  // Linear Search
  int found = -1;
  trace_line(16);
  trace_var_init("found", found);
  trace_line(17);
  for (int i = 0; i < n; i++) {
    trace_line(17);
    trace_var_init("i", i);
    trace_array_cell("arr", "i", i);
    trace_array_highlight("arr", i);
    trace_line(18);
    if (arr[i] == target) {
      trace_line(19);
      found = i;
      trace_var("found", found);
      trace_line(20);
      break;
    }
  }

  trace_line(24);
  if (found >= 0) {
    trace_line(25);
    printf("Found %d at index %d\\n", target, found);
  } else {
    trace_line(27);
    printf("%d not found\\n", target);
  }

  trace_line(30);
  return 0;
}
`,
      },
      {
        name: "Binary Search",
        stdin: "7 1 3 5 7 9 11 13 7",
        code: `#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);

  int arr[20];
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  int target;
  scanf("%d", &target);

  // Binary Search (array must be sorted)
  int low = 0, high = n - 1;
  int found = -1;

  while (low <= high) {
    int mid = (low + high) / 2;
    if (arr[mid] == target) {
      found = mid;
      break;
    } else if (arr[mid] < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  if (found >= 0) {
    printf("Found %d at index %d\\n", target, found);
  } else {
    printf("%d not found\\n", target);
  }

  return 0;
}
`,
        instrumentedCode: `#include <stdio.h>
#include "tracer.h"

int main() {
  int n;
  trace_line(5);
  scanf("%d", &n);
  trace_var_init("n", n);

  int arr[20];
  trace_line(7);
  trace_array_init("arr", n);
  trace_line(8);
  for (int i = 0; i < n; i++) {
    trace_line(8);
    trace_var_init("i", i);
    trace_line(9);
    scanf("%d", &arr[i]);
    trace_array("arr", i, arr[i]);
  }

  int target;
  trace_line(13);
  scanf("%d", &target);
  trace_var_init("target", target);

  // Binary Search (array must be sorted)
  int low = 0, high = n - 1;
  trace_line(16);
  trace_var_init("low", low);
  trace_array_cell("arr", "low", low);
  trace_var_init("high", high);
  trace_array_cell("arr", "high", high);
  int found = -1;
  trace_line(17);
  trace_var_init("found", found);

  trace_line(19);
  while (low <= high) {
    trace_line(19);
    trace_var("low", low);
    trace_array_cell("arr", "low", low);
    trace_var("high", high);
    trace_array_cell("arr", "high", high);
    trace_line(20);
    int mid = (low + high) / 2;
    trace_var_init("mid", mid);
    trace_array_cell("arr", "mid", mid);
    trace_array_highlight("arr", mid);
    trace_line(21);
    if (arr[mid] == target) {
      trace_line(22);
      found = mid;
      trace_var("found", found);
      trace_line(23);
      break;
    } else if (arr[mid] < target) {
      trace_line(25);
      low = mid + 1;
      trace_var("low", low);
      trace_array_cell("arr", "low", low);
    } else {
      trace_line(27);
      high = mid - 1;
      trace_var("high", high);
      trace_array_cell("arr", "high", high);
    }
  }

  trace_line(31);
  if (found >= 0) {
    trace_line(32);
    printf("Found %d at index %d\\n", target, found);
  } else {
    trace_line(34);
    printf("%d not found\\n", target);
  }

  trace_line(37);
  return 0;
}
`,
      },
    ],
  },
];

export default SAMPLE_CATEGORIES;
