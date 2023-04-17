#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct arrStack {
    int num[100];
    char op[100];
    int top;
}Stack;

int trans(char *str, int i, int j) {
    int res = 0;
    for (int x = i; x < j; x++) {
        if (res) {
            res *= 10;
        }
        if (str[x] == '-') {
            continue;
        }
        res += str[x] - '0';
    }
    if (str[i] == '-') {
        return -res;
    }
    return res;
}
int calc(char o, int a, int b) {
    switch (o) {
        case '+' :
            return a + b;
        case '-' :
            return a - b;
        case '*' :
            return a * b;
        case '/' :
            return a / b;
    }
    return INT_MIN;
}
void push(Stack *s, int n, char o) {
    s->top++;
    if (n != INT_MIN) {
        s->num[s->top] = n;
    }
    if (o != '\0') {
        s->op[s->top] = o;
    }
}
int popn(Stack *s) {
    return s->num[s->top--];
}
char popo(Stack *s) {
    return s->op[s->top--];
}
int main() {
    char str[1000];
    scanf("%s", str);
    Stack *ns, *os;
    ns = (Stack *)malloc(sizeof(Stack));
    os = (Stack *)malloc(sizeof(Stack));
    ns->top = -1;
    os->top = -1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '[' || str[i] == '{') {
            str[i] = '(';
        } else if (str[i] == ']' || str[i] == '}') {
            str[i] = ')';
        }
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9' || str[i] == '-' && (i == 0 || str[i - 1] == '(') && str[i + 1] >= '0' && str[i + 1] <= '9') {
            int j;
            for (j = i + 1; str[j] >= '0' && str[j] <= '9'; j++);
            push(ns, trans(str, i, j), '\0');
            i = j - 1;
        } else if (str[i] == '+' || str[i] == '-') {
            while (os->top != -1 && os->op[os->top] != '(') {
                int b = popn(ns);
                int a = popn(ns);
                push(ns, calc(popo(os), a, b), '\0');
            }
            push(os, INT_MIN, str[i]);
        } else if (str[i] == '*' || str[i] == '/') {
            while (os->top != -1 && os->op[os->top] != '(' && os->op[os->top] != '+' && os->op[os->top] != '-') {
                int b = popn(ns);
                int a = popn(ns);
                push(ns, calc(popo(os), a, b), '\0');
            }
            push(os, INT_MIN, str[i]);
        } else if (str[i] == '(') {
            push(os, INT_MIN, str[i]);
        } else {
            while (os->top != -1 && os->op[os->top] != '(') {
                int b = popn(ns);
                int a = popn(ns);
                push(ns, calc(popo(os), a, b), '\0');
            }
            popo(os);
        }
    }
    while (os->top != -1) {
        int b = popn(ns);
        int a = popn(ns);
        push(ns, calc(popo(os), a, b), '\0');
    }
    printf("%d", ns->num[0]);
    return 0;
}