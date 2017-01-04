#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXCOLS 80
#define TRUE 1
#define FALSE 1

typedef struct stack {
    int top;
    int items[MAXCOLS];
} STACK;

double eval(char[]);
double pop(STACK *);
void push(STACK *, int);
bool empty(STACK *);
bool isdigit(char);
double oper(int, double, double);

int main() {
    char expr[MAXCOLS] = {"97+5-"};
    int position = 0;
    printf("%s%s", "the original postfix expression is", expr);
    printf("\n %f", eval(expr));
}

bool isdigit(char symb) {
    return symb >= '0' && symb <= '9';
}

double eval(char expr[]) {
    int c, position;
    double opnd1, opnd2, value;
    struct stack opndstk;
    opndstk.top = -1;
    for (position = 0; (c = expr[position]) != '\0'; position++)
        if (isdigit(c)) {
            push(&opndstk, c - '0');
        }
        else {
            opnd2 = pop(&opndstk);
            opnd1 = pop(&opndstk);
            value = oper(c, opnd1, opnd2);
            push(&opndstk, value);
        }
    return(pop(&opndstk));
}

bool empty(STACK *ps) {
    return ps->top == -1;
}

double oper(int symb, double op1, double op2) {
    switch (symb) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
        case '%': return (int) op1 % (int) op2;
        case '^': return pow(op1, op2);
        default:
            printf("%s", "illegal operation");
            exit(1);
    }
}

double pop(STACK *ps) {
    if (empty(ps)) {
        printf("stack underflow");
        exit(1);
    }
    return ps->items[ps->top--];
}

void push(STACK *ps, int x) {
    if (ps->top == MAXCOLS - 1) {
        printf("stack overflow");
        exit(1);
    }
    else
        ps->items[++(ps->top)] = x;
    return;
}
