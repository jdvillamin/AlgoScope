#include "tracer.h"
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
    trace_dll_init("dll");
    trace_line(13);
    Node* head = NULL;
    trace_dll_pointer("dll", "head", "NULL");
    trace_line(14);
    Node* tail = NULL;
    trace_dll_pointer("dll", "tail", "NULL");
    trace_line(15);
    int counter = 0;
    trace_var_init("counter", 0);

    trace_line(17);
    Node* n1 = (Node*)malloc(sizeof(Node));
    trace_line(18);
    counter++;
    trace_var("counter", counter);
    trace_line(19);
    sprintf(n1->id, "n%d", counter);
    trace_line(20);
    n1->value = 1;
    trace_dll_node("dll", n1->id, 1);
    trace_line(21);
    n1->next = NULL;
    trace_line(22);
    n1->prev = NULL;
    trace_line(23);
    head = n1;
    trace_dll_pointer("dll", "head", n1->id);
    trace_line(24);
    tail = n1;
    trace_dll_pointer("dll", "tail", n1->id);

    trace_line(26);
    Node* n2 = (Node*)malloc(sizeof(Node));
    trace_line(27);
    counter++;
    trace_var("counter", counter);
    trace_line(28);
    sprintf(n2->id, "n%d", counter);
    trace_line(29);
    n2->value = 4;
    trace_dll_node("dll", n2->id, 4);
    trace_line(30);
    n2->next = NULL;
    trace_line(31);
    n2->prev = tail;
    trace_dll_prev_link("dll", n2->id, tail->id);
    trace_line(32);
    tail->next = n2;
    trace_dll_next_link("dll", tail->id, n2->id);
    trace_line(33);
    tail = n2;
    trace_dll_pointer("dll", "tail", n2->id);

    trace_line(35);
    Node* n3 = (Node*)malloc(sizeof(Node));
    trace_line(36);
    counter++;
    trace_var("counter", counter);
    trace_line(37);
    sprintf(n3->id, "n%d", counter);
    trace_line(38);
    n3->value = 7;
    trace_dll_node("dll", n3->id, 7);
    trace_line(39);
    n3->next = NULL;
    trace_line(40);
    n3->prev = tail;
    trace_dll_prev_link("dll", n3->id, tail->id);
    trace_line(41);
    tail->next = n3;
    trace_dll_next_link("dll", tail->id, n3->id);
    trace_line(42);
    tail = n3;
    trace_dll_pointer("dll", "tail", n3->id);

    trace_line(44);
    Node* n4 = (Node*)malloc(sizeof(Node));
    trace_line(45);
    counter++;
    trace_var("counter", counter);
    trace_line(46);
    sprintf(n4->id, "n%d", counter);
    trace_line(47);
    n4->value = 10;
    trace_dll_node("dll", n4->id, 10);
    trace_line(48);
    n4->next = NULL;
    trace_line(49);
    n4->prev = tail;
    trace_dll_prev_link("dll", n4->id, tail->id);
    trace_line(50);
    tail->next = n4;
    trace_dll_next_link("dll", tail->id, n4->id);
    trace_line(51);
    tail = n4;
    trace_dll_pointer("dll", "tail", n4->id);

    trace_line(53);
    printf("Backward: ");
    trace_line(54);
    Node* curr = tail;
    trace_dll_pointer("dll", "curr", tail->id);
    trace_line(55);
    while (curr != NULL) {
        trace_line(55);
        trace_dll_highlight("dll", curr->id);
        trace_line(56);
        printf("%d ", curr->value);
        trace_line(57);
        curr = curr->prev;
        trace_dll_pointer("dll", "curr", curr ? curr->id : "NULL");
    }
    trace_line(59);
    printf("\n");

    trace_line(61);
    return 0;
}
