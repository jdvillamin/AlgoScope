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
    int counter = 0;

    Node* n1 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n1->id, "n%d", counter);
    n1->value = 4;
    n1->next = NULL;
    head = n1;

    Node* n2 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n2->id, "n%d", counter);
    n2->value = 12;
    n2->next = NULL;
    n1->next = n2;

    Node* n3 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n3->id, "n%d", counter);
    n3->value = 18;
    n3->next = NULL;
    n2->next = n3;

    int pos = 2;
    Node* newNode = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(newNode->id, "n%d", counter);
    newNode->value = 8;

    Node* curr = head;
    int i = 1;
    while (i < pos - 1) {
        curr = curr->next;
        i++;
    }
    newNode->next = curr->next;
    curr->next = newNode;

    curr = head;
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");

    return 0;
}
