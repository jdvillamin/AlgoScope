/* Source: https://www.geeksforgeeks.org/dsa/convert-infix-expression-to-postfix-expression/ */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "tracer.h"

int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Check if operator is right-associative
int isRightAssociative(char c) {
    return c == '^';
}

void infixToPostfix(char* exp) {
    trace_line(24);
    int len = strlen(exp);
    trace_var_init("len", len);
    trace_line(25);
    char result[len + 1];
    trace_line(26);
    char stack[len];
    trace_line(27);
    int j = 0;
    trace_var_init("j", j);
    trace_line(28);
    int top = -1;
    trace_var_init("top", top);

    trace_line(30);
    for (int i = 0; i < len; i++) {
        trace_line(30);
        trace_var_init("i", i);
        trace_line(31);
        char c = exp[i];
        trace_var_init("c", c);

        // If operand, add to result
        trace_line(34);
        if (isalnum(c)) {
            trace_line(35);
            result[j++] = c;
            trace_var("j", j);
        }
        // If '(', push to stack
        else if (c == '(') {
            trace_line(39);
            stack[++top] = '(';
            trace_var("top", top);
        }
        // If ')', pop until '('
        else if (c == ')') {
            trace_line(43);
            while (top != -1 && stack[top] != '(') {
                trace_line(43);
                trace_line(44);
                result[j++] = stack[top--];
                trace_var("j", j);
                trace_var("top", top);
            }

            // pop '('
            trace_line(48);
            top--;
            trace_var("top", top);
        }

        // If operator
        else {
            trace_line(53);
            while (top != -1 && stack[top] != '(' &&
                  (prec(stack[top]) > prec(c) ||
                  (prec(stack[top]) == prec(c) && !isRightAssociative(c)))) {
                trace_line(53);
                trace_line(56);
                result[j++] = stack[top--];
                trace_var("j", j);
                trace_var("top", top);
            }
            trace_line(58);
            stack[++top] = c;
            trace_var("top", top);
        }
    }

    // Pop remaining operators
    trace_line(63);
    while (top != -1) {
        trace_line(63);
        trace_line(64);
        result[j++] = stack[top--];
        trace_var("j", j);
        trace_var("top", top);
    }

    trace_line(67);
    result[j] = '\0';
    trace_line(68);
    printf("%s\n", result);
}

int main() {
    trace_line(72);
    char exp1[] = "a*(b+c)/d";
    trace_line(73);
    infixToPostfix(exp1);
    trace_line(74);
    return 0;
}
