#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXCOLS 80
#define EMPTYSTACK -1
#define TRUE 1
#define FALSE 0

typedef struct opdstack {
    int top;
    double items[MAXCOLS];
} OPDSTACK;
typedef struct stack {
    int top;
    char items[MAXCOLS];
} STACK;

double eval(char []);
void postfix(char *, char *);
bool isoperand(char);
bool isdigit(char);
void popandtest(STACK *, char *, int *);
bool empty(STACK *);
char pop(STACK *);
void push(STACK *, char);
bool emptyopd(OPDSTACK *);
double popopd(OPDSTACK *);
void pushopd(OPDSTACK *, double);
bool prcd(char, char);
double oper(int, double, double);

int main() {
    char infix[MAXCOLS] = {"(9+7)*(5-3)"};
    //char infix[MAXCOLS] = {"9^3*3-7+9/3/(4-1)"};
    char postr[MAXCOLS];
    int pos = 0;
    /* while((infix[pos++] = getchar()) != '\n') infix[--pos] = '\0'; */
    printf("%s %s", "the original infix expression is", infix);
    postfix(infix, postr);
    printf("postfix is %s", postr);
    printf("\n %s %f\n", "the value is: ", eval(postr));
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
            printf("illegal operation");
            exit(1);
    }
}

void postfix(char infix[], char postr[]) {
    int position, und;
    int outpos = 0;
    char topsymb = '+';
    char symb;
    struct stack opstk;
    opstk.top = EMPTYSTACK;
    for (position = 0; (symb = infix[position]) != '\0'; position++)
        if (isoperand(symb))
            postr[outpos++] = symb;
        else {
            popandtest(&opstk, &topsymb, &und);
            while (!und && prcd(topsymb, symb)) {
                postr[outpos++] = topsymb;
                popandtest(&opstk, &topsymb, &und);
            }
            if (!und)
                push(&opstk, topsymb);
            if (und || (symb != ')'))
                push(&opstk, symb);
            else
                topsymb = pop(&opstk);
        }
    while (!empty(&opstk))
        postr[outpos++] = pop(&opstk);
    postr[outpos] = '\0';
}

bool isdigit(char symb) {
    return symb >= '0' && symb <= '9';
}

bool empty(STACK *ps) {
    return ps->top == EMPTYSTACK;
}

char pop(STACK *ps) {
    if (empty(ps)) {
        printf("stack underflow");
        exit(1);
    }
    return ps->items[ps->top--];
}

double eval(char expr[]) {
    int c, position;
    double opnd1, opnd2, value;
    struct opdstack opndstk;
    opndstk.top = EMPTYSTACK;
    for (position = 0; (c = expr[position]) != '\0'; position++)
        if (isdigit(c))
            pushopd(&opndstk, (double) (c - '0'));
        else {
            opnd2 = popopd(&opndstk);
            opnd1 = popopd(&opndstk);
            value = oper(c, opnd1, opnd2);
            pushopd(&opndstk, value);
        }
    return popopd(&opndstk);
}

void push(STACK *ps, char x) {
    if (ps->top == MAXCOLS - 1) {
        printf("stack overflow");
        exit(1);
    }
    ps->items[++(ps->top)] = x;
}

bool emptyopd(OPDSTACK *ps) {
    return ps->top == EMPTYSTACK;
}

double popopd(OPDSTACK *ps) {
    if (emptyopd(ps)) {
        printf("stack underflow");
        exit(1);
    }
    return ps->items[ps->top--];
}

void pushopd(OPDSTACK *ps, double x) {
    if (ps->top == MAXCOLS - 1) {
        printf("stack overflow");
        exit(1);
    }
    ps->items[++(ps->top)] = x;
}

bool isoperand(char symb) {
    return symb >= '0' && symb <= '9';
}

void popandtest(STACK *ps, char *px, int *pund) {
    if (empty(ps)) {
        *pund = TRUE;
        return;
    }
    *pund = FALSE;
    *px = ps->items[ps->top--];
}

bool prcd(char opr1, char opr2) {
    switch (opr1) {
        case '(': return FALSE;
        case '+': return opr2 == ')' || opr2 == '+';
        case '-': return opr2 == ')' || opr2 == '-';
        case '*': return opr2 == ')' || opr2 == '*' || opr2 == '+' || opr2 == '-';
        case '/': return opr2 == ')' || opr2 == '/' || opr2 == '+' || opr2 == '-';
        case '^': return opr2 == ')' || opr2 == '^' || opr2 == '*' || opr2 == '/' || opr2 == '+' || opr2 == '-';
        case '%': return opr2 == ')' || opr2 == '%' || opr2 == '*' || opr2 == '/' || opr2 == '+' || opr2 == '-';
        default:
            printf("illegal operation");
            exit(1);
    }
}
