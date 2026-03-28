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
    n2->value = 9;
    n2->next = NULL;
    n1->next = n2;

    Node* n3 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n3->id, "n%d", counter);
    n3->value = 14;
    n3->next = NULL;
    n2->next = n3;

    Node* temp = head;
    head = head->next;
    free(temp);

    Node* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");

    return 0;
}
