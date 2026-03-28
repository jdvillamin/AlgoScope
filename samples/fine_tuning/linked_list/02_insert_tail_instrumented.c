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
    Node* tail = NULL;
    trace_ll_pointer("list", "tail", "NULL");
    trace_line(14);
    int counter = 0;
    trace_var_init("counter", 0);

    trace_line(16);
    Node* n1 = (Node*)malloc(sizeof(Node));
    trace_line(17);
    counter++;
    trace_var("counter", counter);
    trace_line(18);
    sprintf(n1->id, "n%d", counter);
    trace_line(19);
    n1->value = 3;
    trace_ll_node("list", n1->id, 3);
    trace_line(20);
    n1->next = NULL;
    trace_ll_link("list", n1->id, "NULL");
    trace_line(21);
    head = n1;
    trace_ll_pointer("list", "head", n1->id);
    trace_line(22);
    tail = n1;
    trace_ll_pointer("list", "tail", n1->id);

    trace_line(24);
    Node* n2 = (Node*)malloc(sizeof(Node));
    trace_line(25);
    counter++;
    trace_var("counter", counter);
    trace_line(26);
    sprintf(n2->id, "n%d", counter);
    trace_line(27);
    n2->value = 7;
    trace_ll_node("list", n2->id, 7);
    trace_line(28);
    n2->next = NULL;
    trace_ll_link("list", n2->id, "NULL");
    trace_line(29);
    tail->next = n2;
    trace_ll_link("list", n1->id, n2->id);
    trace_line(30);
    tail = n2;
    trace_ll_pointer("list", "tail", n2->id);

    trace_line(32);
    Node* n3 = (Node*)malloc(sizeof(Node));
    trace_line(33);
    counter++;
    trace_var("counter", counter);
    trace_line(34);
    sprintf(n3->id, "n%d", counter);
    trace_line(35);
    n3->value = 12;
    trace_ll_node("list", n3->id, 12);
    trace_line(36);
    n3->next = NULL;
    trace_ll_link("list", n3->id, "NULL");
    trace_line(37);
    tail->next = n3;
    trace_ll_link("list", n2->id, n3->id);
    trace_line(38);
    tail = n3;
    trace_ll_pointer("list", "tail", n3->id);

    trace_line(40);
    Node* n4 = (Node*)malloc(sizeof(Node));
    trace_line(41);
    counter++;
    trace_var("counter", counter);
    trace_line(42);
    sprintf(n4->id, "n%d", counter);
    trace_line(43);
    n4->value = 19;
    trace_ll_node("list", n4->id, 19);
    trace_line(44);
    n4->next = NULL;
    trace_ll_link("list", n4->id, "NULL");
    trace_line(45);
    tail->next = n4;
    trace_ll_link("list", n3->id, n4->id);
    trace_line(46);
    tail = n4;
    trace_ll_pointer("list", "tail", n4->id);

    trace_line(48);
    Node* curr = head;
    trace_ll_pointer("list", "curr", n1->id);
    trace_line(49);
    while (curr != NULL) {
        trace_line(49);
        trace_ll_highlight("list", curr->id);
        trace_line(50);
        printf("%d ", curr->value);
        trace_line(51);
        curr = curr->next;
        trace_ll_pointer("list", "curr", curr ? curr->id : "NULL");
    }
    trace_line(53);
    printf("\n");

    trace_line(55);
    return 0;
}
