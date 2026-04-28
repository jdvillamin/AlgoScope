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

  trace_line(5);
  for (i = 0; i < 5; i++) {
    trace_line(5);
    trace_var("i", i);
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
    name: "Hash & Trees",
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
  trace_var_init("j", j);
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
      trace_var("k", k);
    } else {
      trace_line(14);
      temp[k++] = arr[j++];
      trace_var("j", j);
      trace_var("k", k);
    }
  }
  trace_line(17);
  while (i <= m) {
    trace_line(17);
    temp[k++] = arr[i++];
    trace_var("i", i);
    trace_var("k", k);
  }
  trace_line(18);
  while (j <= r) {
    trace_line(18);
    temp[k++] = arr[j++];
    trace_var("j", j);
    trace_var("k", k);
  }

  trace_line(20);
  for (int x = l; x <= r; x++) {
    trace_line(20);
    trace_var_init("x", x);
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
  trace_var_init("high", high);
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
    trace_array_highlight("arr", j);
    trace_line(16);
    if (arr[j] <= pivot) {
      trace_line(17);
      i++;
      trace_var("i", i);
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
  trace_var_init("high", high);
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
