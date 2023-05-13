#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct arrStack {
    double data[1000];
    int top;
} Stack;

void push(Stack *s, double x) {
    s->data[++s->top] = x;
}

double pop(Stack *s) {
    return s->data[s->top--];
}

int pre_process(char *str) {
    int len = 0;
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] != ' ') {
            if (str[i] == '[' || str[i] == '{') {
                str[i] = '(';
            } else if (str[i] == ']' || str[i] == '}') {
                str[i] = ')';
            } else if (isdigit(str[i]) || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
                       str[i] == '.' || str[i] == '(' || str[i] == ')') {
                //do nothing
            } else {
                return -1;
            }

            str[len] = str[i];
            len += 1;
        }
    }
    str[len] = '\0';
    return len;
}

int get_pri(char operator) {
    if (operator == '+' || operator == '-') {
        return 1;
    }
    if (operator == '*' || operator == '/') {
        return 2;
    }
    return 0;   //operator == '('
}

double basic_calc(char operator, double y, double x) {
    switch (operator) {
        case '+' :
            return x + y;
        case '-' :
            return x - y;
        case '*' :
            return x * y;
        default:    //operator == '/'
            return x / y;
    }
}

int main() {
    char str[1000];
    scanf("%[^\n]", str);
    getchar();
    int len = pre_process(str);
    if (len == -1) {
        printf("Error.\n");
        return -1;
    }
    Stack nS = {.top = -1}, oS = {.top = -1};


    for (int i = 0; i < len; i += 1) {
        if (isdigit(str[i])) {
            char *p;
            push(&nS, strtod(&str[i], &p));
            do {
                i += 1;
            } while (isdigit(str[i]) || str[i] == '.');
            i -= 1;
        } else if (str[i] == '(') {
            push(&oS, str[i]);
        } else if (str[i] == ')') {
            while (oS.top != -1 && oS.data[oS.top] != '(') {
                if (nS.top < 1) {
                    printf("Error.\n");
                    return -1;
                }
                push(&nS, basic_calc(pop(&oS), pop(&nS), pop(&nS)));
            }
            pop(&oS);
        } else {
            if (i == len - 1 || str[i + 1] == ')') {
                printf("Error.\n");
                return -1;
            }
            if (i == 0 || str[i - 1] == '(') {
                push(&nS, 0);
            }
            while (oS.top != -1 && get_pri(str[i]) <= get_pri(oS.data[oS.top])) {
                if (nS.top < 1) {
                    printf("Error.\n");
                    return -1;
                }
                push(&nS, basic_calc(pop(&oS), pop(&nS), pop(&nS)));
            }
            push(&oS, str[i]);
        }
    }
    while (oS.top != -1) {
        if (nS.top < 1) {
            printf("Error.\n");
            return -1;
        }
        push(&nS, basic_calc(pop(&oS), pop(&nS), pop(&nS)));
    }

    printf("%f", nS.data[0]);
    return 0;
}