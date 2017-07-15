/******************************************************************************/
/*                                                                            */
/*  Topic: Infix to prefix                                                    */
/*                                                                            */
/*  Objective: Convert the infix notation to prefix notation                  */
/*             and evaluate it in prefix fashion                              */
/*                                                                            */
/*  Comments: Implemented the algorithm in chapter 22                         */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define MAXCOLS 80
#define MAXDIGITS 3
#define EMPTYSTACK -1
#define TRUE 1
#define FALSE 0
#define INFILENAME "input17.doc"
#define OUTFILENAME "output17.doc"

typedef struct opdstack {
    int top;
    double items[MAXCOLS];
} OPDSTACK;
typedef struct stack {
    int top;
    char items[MAXCOLS][MAXDIGITS];
} STACK;

void read(STACK *);
void prefix(STACK *, char (*prer)[MAXDIGITS]);
bool empty(STACK *);
bool isoperand(char *);
void popandtest(STACK *, char (*px)[MAXDIGITS], int *);
bool prcd(char *, char *);
void push(STACK *, char *);
char *pop(STACK *);
void reverse(char (*array)[MAXDIGITS], int);
double eval(char (*expr)[MAXDIGITS], int);
bool isdigit(char);
void pushopd(OPDSTACK *, double);
double popopd(OPDSTACK *);
bool emptyopd(OPDSTACK *);
double oper(char *, double, double);
int pfprintf(FILE *, const char *, ...);

FILE *pIn, *pOut;
int length;

int main() {
    STACK infixstack;
    char prer[MAXCOLS][MAXDIGITS];
    double result;
    infixstack.top = EMPTYSTACK;

    // open output file
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    read(&infixstack); // read the input from the input file into a stack
    prefix(&infixstack, prer); // convert the infix notation to prefix notation
    pfprintf(pOut, "the result value is: %f\n", eval(prer, length)); // evaluate the expression in prefix format

    fclose(pOut);
}

void read(STACK *infixstack) {
    char s[MAXDIGITS];

    // open input file
    if ((pIn = fopen(INFILENAME, "r")) == NULL) {
        printf("%s could not be opend\n", INFILENAME);
        exit(1);
    }

    pfprintf(pOut, "the original infix expression is\n");
    while (fscanf(pIn, "%s", s) != EOF) {
        pfprintf(pOut, "%s ", s);
        push(infixstack, s);
    }
    pfprintf(pOut, "\n");

    fclose(pIn);
}

void prefix(STACK *infix, char (*prer)[MAXDIGITS]) {
    int position, und;
    int outpos = 0;
    char topsymb[MAXDIGITS] = "+";
    char symb[MAXDIGITS];
    STACK opstk;
    opstk.top = EMPTYSTACK; // the empty operator stack

    while (!empty(infix)) {
        strcpy(symb, pop(infix)); // symb = next input character

        if (isoperand(symb)) // symb is operand
            strcpy(prer[outpos++], symb); // add symb to the prefix string
        else { // symb is operaor
            popandtest(&opstk, &topsymb, &und);

            while (!und && prcd(topsymb, symb)) {
                strcpy(prer[outpos++], topsymb); // add topsymb to the prefix string
                popandtest(&opstk, &topsymb, &und);
            }

            if (!und)
                push(&opstk, topsymb);
            if (und || strcmp(symb, "(") != 0) // underflow or hit open parenthesis
                push(&opstk, symb);
            else
                strcpy(topsymb, pop(&opstk));
        }
    }
    // output any remaining operators
    while (!empty(&opstk))
        strcpy(prer[outpos++], pop(&opstk)); // add popped symbol to the prefix string
    length = outpos;

    reverse(prer, length); // reverse the stack

    pfprintf(pOut, "prefix expression is\n");
    for (int i = 0; i < length; i++)
        pfprintf(pOut, "%s ", prer[i]);
    pfprintf(pOut, "\n");
}

bool empty(STACK *ps) {
    return ps->top == EMPTYSTACK;
}

bool isoperand(char *symb) {
    for (int i = 0; symb[i] != '\0'; i++)
        if (!isdigit(*(symb + i)))
            return FALSE;

    return TRUE;
}

void popandtest(STACK *ps, char (*px)[MAXDIGITS], int *pund) {
    if (empty(ps)) {
        *pund = TRUE;
        return;
    }

    *pund = FALSE;
    strcpy(*px, ps->items[ps->top--]);
}

bool prcd(char *opr1, char *opr2) {
    if      (strcmp(opr1, ")") == 0) return FALSE;
    else if (strcmp(opr1, "+") == 0) return strcmp(opr2, "(") == 0;
    else if (strcmp(opr1, "-") == 0) return strcmp(opr2, "(") == 0;
    else if (strcmp(opr1, "*") == 0) return strcmp(opr2, "(") == 0 || strcmp(opr2, "+") == 0 || strcmp(opr2, "-") == 0;
    else if (strcmp(opr1, "/") == 0) return strcmp(opr2, "(") == 0 || strcmp(opr2, "+") == 0 || strcmp(opr2, "-") == 0;
    else if (strcmp(opr1, "^") == 0) return strcmp(opr2, "(") == 0 || strcmp(opr2, "*") == 0 || strcmp(opr2, "/") == 0 || strcmp(opr2, "+") == 0 || strcmp(opr2, "-") == 0;
    else if (strcmp(opr1, "%") == 0) return strcmp(opr2, "(") == 0 || strcmp(opr2, "*") == 0 || strcmp(opr2, "/") == 0 || strcmp(opr2, "+") == 0 || strcmp(opr2, "-") == 0;
    else {
        pfprintf(pOut, "illegal operation");
        exit(1);
    }
}

void push(STACK *ps, char *x) {
    if (ps->top == MAXCOLS - 1) {
        pfprintf(pOut, "stack overflow");
        exit(1);
    }

    strcpy(ps->items[++(ps->top)], x);
}

char *pop(STACK *ps) {
    if (empty(ps)) {
        pfprintf(pOut, "stack underflow");
        exit(1);
    }

    return ps->items[ps->top--];
}

// reverse contents of the stack
void reverse(char (*array)[MAXDIGITS], int length) {
    int i, j, k;
    char tmp[MAXCOLS][MAXDIGITS];

    for (i = 0, j = length - 1; j >= 0; i++, j--)
        strcpy(tmp[i], array[j]);
    for (k = 0; k < length; k++)
        strcpy(array[k], tmp[k]);
}

double eval(char (*expr)[MAXDIGITS], int length) {
    int c, position;
    char s[MAXDIGITS];
    double opnd1, opnd2, value;
    OPDSTACK opndstk;
    opndstk.top = EMPTYSTACK;

    reverse(expr, length); // reverse the stack
    for (position = 0; position < length; position++) {
        strcpy(s, expr[position]);

        if (isoperand(s)) // is operand
            pushopd(&opndstk, atof(s));
        else { // is operator
            opnd1 = popopd(&opndstk);
            opnd2 = popopd(&opndstk);
            value = oper(s, opnd1, opnd2);
            pushopd(&opndstk, value);
        }
    }

    return popopd(&opndstk);
}

bool isdigit(char symb) {
    return symb >= '0' && symb <= '9';
}

void pushopd(OPDSTACK *ps, double x) {
    if (ps->top == MAXCOLS - 1) {
        pfprintf(pOut, "stack overflow");
        exit(1);
    }

    ps->items[++(ps->top)] = x;
}

double popopd(OPDSTACK *ps) {
    if (emptyopd(ps)) {
        pfprintf(pOut, "stack underflow");
        exit(1);
    }

    return ps->items[ps->top--];
}

bool emptyopd(OPDSTACK *ps) {
    return ps->top == EMPTYSTACK;
}

double oper(char *symb, double op1, double op2) {
    if      (strcmp(symb, "+") == 0) return op1 + op2;
    else if (strcmp(symb, "-") == 0) return op1 - op2;
    else if (strcmp(symb, "*") == 0) return op1 * op2;
    else if (strcmp(symb, "/") == 0) return op1 / op2;
    else if (strcmp(symb, "%") == 0) return (int) op1 % (int) op2;
    else if (strcmp(symb, "^") == 0) return pow(op1, op2);
    else {
        pfprintf(pOut, "illegal operation");
        exit(1);
    }
}

// a function combining printf and fprintf
int pfprintf(FILE *fp, const char *format, ...) {
    va_list ap;
    int result;

    va_start(ap, format);
    result = vfprintf(fp, format, ap);
    va_end(ap);
    if (fp != stdout && fp != stderr) {
        va_start(ap, format);
        result = vprintf(format, ap);
        va_end(ap);
    }

    return result;
}
