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
    n1->value = 2;
    n1->next = NULL;
    head = n1;

    Node* n2 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n2->id, "n%d", counter);
    n2->value = 7;
    n2->next = NULL;
    n1->next = n2;

    Node* n3 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n3->id, "n%d", counter);
    n3->value = 13;
    n3->next = NULL;
    n2->next = n3;

    Node* n4 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n4->id, "n%d", counter);
    n4->value = 18;
    n4->next = NULL;
    n3->next = n4;

    Node* n5 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n5->id, "n%d", counter);
    n5->value = 20;
    n5->next = NULL;
    n4->next = n5;

    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    printf("Middle: %d\n", slow->value);

    return 0;
}
