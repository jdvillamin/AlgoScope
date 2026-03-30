#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    char id[10];
    struct Node* next;
    struct Node* prev;
} Node;

int main() {
    Node* head = NULL;
    Node* tail = NULL;
    int counter = 0;

    Node* n1 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n1->id, "n%d", counter);
    n1->value = 4;
    n1->next = NULL;
    n1->prev = NULL;
    head = n1;
    tail = n1;

    Node* n2 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n2->id, "n%d", counter);
    n2->value = 9;
    n2->next = NULL;
    n2->prev = tail;
    tail->next = n2;
    tail = n2;

    Node* n3 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n3->id, "n%d", counter);
    n3->value = 14;
    n3->next = NULL;
    n3->prev = tail;
    tail->next = n3;
    tail = n3;

    Node* n4 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n4->id, "n%d", counter);
    n4->value = 19;
    n4->next = NULL;
    n4->prev = tail;
    tail->next = n4;
    tail = n4;

    int target = 14;
    int found = 0;
    Node* curr = head;
    while (curr != NULL) {
        if (curr->value == target) {
            printf("found %d\n", target);
            found = 1;
            break;
        }
        curr = curr->next;
    }

    if (!found) {
        printf("%d not found\n", target);
    }

    return 0;
}
