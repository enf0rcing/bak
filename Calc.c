#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct arrStack {
    int data[100];
    int top;
} Stack;

int basic_calc(int operator, int x, int y) {
    switch (operator) {
        case '+' :
            return x + y;
        case '-' :
            return x - y;
        case '*' :
            return x * y;
        case '/' :
            return x / y;
        default:
            return 0;
    }
}

void push(Stack *s, int x) {
    s->data[++s->top] = x;
}

int pop(Stack *s) {
    return s->data[s->top--];
}

int main() {
    char str[1000];
    scanf("%s", str);
    Stack nS, oS;
    nS.top = -1;
    oS.top = -1;
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '[' || str[i] == '{') {
            str[i] = '(';
        } else if (str[i] == ']' || str[i] == '}') {
            str[i] = ')';
        }
    }
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (isdigit(str[i]) || str[i] == '-' && (i == 0 || str[i - 1] == '(') && isdigit(str[i + 1])) {
            char *p;
            push(&nS, strtol(&str[i], &p, 10));
            do {
                i += 1;
            } while (isdigit(str[i]));
            i -= 1;
        } else if (str[i] == '(') {
            push(&oS, str[i]);
        } else if (str[i] == ')') {
            while (oS.top != -1 && oS.data[oS.top] != '(') {
                int b = pop(&nS);
                int a = pop(&nS);
                push(&nS, basic_calc(pop(&oS), a, b));
            }
            pop(&oS);
        } else if (str[i] == '+' || str[i] == '-') {
            while (oS.top != -1 && oS.data[oS.top] != '(') {
                int b = pop(&nS);
                int a = pop(&nS);
                push(&nS, basic_calc(pop(&oS), a, b));
            }
            push(&oS, str[i]);
        } else if (str[i] == '*' || str[i] == '/') {
            while (oS.top != -1 && oS.data[oS.top] != '(' && oS.data[oS.top] != '+' && oS.data[oS.top] != '-') {
                int b = pop(&nS);
                int a = pop(&nS);
                push(&nS, basic_calc(pop(&oS), a, b));
            }
            push(&oS, str[i]);
        } else {
            return -1;
        }
    }
    while (oS.top != -1) {
        int b = pop(&nS);
        int a = pop(&nS);
        push(&nS, basic_calc(pop(&oS), a, b));
    }
    printf("%d", nS.data[0]);
    return 0;
}