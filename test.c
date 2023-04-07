#include <stdio.h>

typedef struct arrayStack {
    int n[100];
    char o[100];
    int top;
}Stack;

int stoi(char *s, int i, int j) {//将字符串s i到j之间的字符转换成数字
    int res = 0;
    for (int x = i; x < j; x++) {
        if (s[x] == '-')
            continue;
        if (res)
            res *= 10;
        res += s[x] - '0';
    }
    if (s[i] == '-')
        return -res;
    return res;
}

void push(Stack *s, int n, char o) {//入栈，根据参数决定是数还是字符
    s->top++;
    if (n != 1001)
        s->n[s->top] = n;
    if (o != '\0')
        s->o[s->top] = o;
}

int popn(Stack *s) {//将数出栈
    return s->n[s->top--];
}
char popo(Stack *s) {//将字符出栈
    return s->o[s->top--];
}
int calc(char o, int a, int b) {//四则运算函数
    if (o == '+')
        return a + b;
    else if (o == '-')
        return a - b;
    else if (o == '*')
        return a * b;
    else
        return a / b;
}
int main() {
    Stack ns, os;
    ns.top = -1;//数栈初始化
    os.top = -1;//字符栈初始化
    char str[1001];
    scanf("%s", str);
    for (int i = 0; str[i] != '\0'; i++)//将其他括号转换成小括号
        if (str[i] == '[' || str[i] == '{')
            str[i] = '(';
        else if (str[i] == ']' || str[i] == '}')
            str[i] = ')';

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] >= '0' && str[i] <= '9' || (i == 0 || str[i - 1] == '(') && str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9') {//检测到数字，转换并入数栈
            int j;
            for (j = i + 1; str[j] >= '0' && str[j] <= '9'; j++);
            push(&ns, stoi(str, i, j), '\0');
            i = j - 1;
        }else if (str[i] == '+' || str[i] == '-') {//先判断加减
            if (os.top == -1 || os.o[os.top] == '(')//优先级高，入字符栈
                push(&os, 1001, str[i]);
            else {//优先级不高，字符栈出到高再入栈
                while (os.top != -1 && os.o[os.top] != '(') {
                    int b = popn(&ns);//一旦触发字符栈出栈，数栈出两个数计算，将结果推回
                    int a = popn(&ns);
                    push(&ns, calc(popo(&os), a, b), '\0');
                }
                push(&os, 1001, str[i]);
            }
        }else if (str[i] == '*' || str[i] == '/') {//再判断乘除
            if (os.top == -1 || os.o[os.top] == '(' || os.o[os.top] == '+' || os.o[os.top] == '-')//优先级高，入字符栈
                push(&os, 1001, str[i]);
            else {//优先级不高，字符栈出到高再入栈
                while (os.top != -1 && os.o[os.top] != '(' && os.o[os.top] != '+' && os.o[os.top] != '-') {
                    int b = popn(&ns);//一旦触发字符栈出栈，数栈出两个数计算，将结果推回
                    int a = popn(&ns);
                    push(&ns, calc(popo(&os), a, b), '\0');
                }
                push(&os, 1001, str[i]);
            }
        }else if (str[i] == '(')//检测到左括号，直接入字符栈
            push(&os, 1001, str[i]);
        else//检测到右括号，字符出栈一直出到匹配的左括号
            while (1) {
                char temp = popo(&os);
                if (temp == '(')
                    break;
                int b = popn(&ns);//一旦触发字符栈出栈，数字栈出两个数字并计算，将结果入栈
                int a = popn(&ns);
                push(&ns, calc(temp, a, b), '\0');
            }
    while (os.top != -1) {
        int b = popn(&ns);//一旦触发字符栈出栈，数字栈出两个数字并计算，将结果入栈
        int a = popn(&ns);
        push(&ns, calc(popo(&os), a, b), '\0');
    }
    printf("%d", ns.n[0]);
    return 0;
}