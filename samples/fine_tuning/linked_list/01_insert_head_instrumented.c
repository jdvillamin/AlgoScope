#include "tracer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    char id[10];
    struct Node* next;
} Node;

int main() {
    trace_ll_init("list");
    trace_line(12);
    Node* head = NULL;
    trace_ll_pointer("list", "head", "NULL");
    trace_line(13);
    int counter = 0;
    trace_var_init("counter", 0);

    trace_line(15);
    Node* n1 = (Node*)malloc(sizeof(Node));
    trace_line(16);
    counter++;
    trace_var("counter", counter);
    trace_line(17);
    sprintf(n1->id, "n%d", counter);
    trace_line(18);
    n1->value = 5;
    trace_ll_node("list", n1->id, 5);
    trace_line(19);
    n1->next = head;
    trace_ll_link("list", n1->id, "NULL");
    trace_line(20);
    head = n1;
    trace_ll_pointer("list", "head", n1->id);

    trace_line(22);
    Node* n2 = (Node*)malloc(sizeof(Node));
    trace_line(23);
    counter++;
    trace_var("counter", counter);
    trace_line(24);
    sprintf(n2->id, "n%d", counter);
    trace_line(25);
    n2->value = 10;
    trace_ll_node("list", n2->id, 10);
    trace_line(26);
    n2->next = head;
    trace_ll_link("list", n2->id, n1->id);
    trace_line(27);
    head = n2;
    trace_ll_pointer("list", "head", n2->id);

    trace_line(29);
    Node* n3 = (Node*)malloc(sizeof(Node));
    trace_line(30);
    counter++;
    trace_var("counter", counter);
    trace_line(31);
    sprintf(n3->id, "n%d", counter);
    trace_line(32);
    n3->value = 15;
    trace_ll_node("list", n3->id, 15);
    trace_line(33);
    n3->next = head;
    trace_ll_link("list", n3->id, n2->id);
    trace_line(34);
    head = n3;
    trace_ll_pointer("list", "head", n3->id);

    trace_line(36);
    Node* curr = head;
    trace_ll_pointer("list", "curr", n3->id);
    trace_line(37);
    while (curr != NULL) {
        trace_line(37);
        trace_ll_highlight("list", curr->id);
        trace_line(38);
        printf("%d ", curr->value);
        trace_line(39);
        curr = curr->next;
        trace_ll_pointer("list", "curr", curr ? curr->id : "NULL");
    }
    trace_line(41);
    printf("\n");

    trace_line(43);
    return 0;
}
