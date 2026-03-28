#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    char id[10];
    struct Node* next;
} Node;

int main() {
    Node* head = NULL;
    Node* tail = NULL;
    int counter = 0;

    Node* n1 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n1->id, "n%d", counter);
    n1->value = 3;
    n1->next = NULL;
    head = n1;
    tail = n1;

    Node* n2 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n2->id, "n%d", counter);
    n2->value = 7;
    n2->next = NULL;
    tail->next = n2;
    tail = n2;

    Node* n3 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n3->id, "n%d", counter);
    n3->value = 12;
    n3->next = NULL;
    tail->next = n3;
    tail = n3;

    Node* n4 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n4->id, "n%d", counter);
    n4->value = 19;
    n4->next = NULL;
    tail->next = n4;
    tail = n4;

    Node* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");

    return 0;
}
