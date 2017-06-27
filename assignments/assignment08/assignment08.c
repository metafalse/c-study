/******************************************************************************/
/*                                                                            */
/*  Topic: Stacks                                                             */
/*                                                                            */
/*  Objective: Evaluate the validity of the scopes in the expression          */
/*             implementing stacks                                            */
/*                                                                            */
/*  Comments: The code in chapter 20 modified to make it work as desired      */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define MAXSTACK 26
#define EMPTYSTACK -1
#define TRUE 1
#define FALSE 0
#define INFILENAME "input8.doc"
#define OUTFILENAME "output8.doc"

typedef struct stack {
    int top;
    char stackelement[MAXSTACK];
} STACK;

bool empty(STACK *);
bool full(STACK *);
char pop(STACK *);
void push(STACK *, char);
int pfprintf(FILE *, const char *, ...);

FILE *pIn, *pOut;

int main() {
    char c, popped;
    STACK *sp;
    sp->top = EMPTYSTACK;

    // open input and output file
    if ((pIn = fopen(INFILENAME, "r")) == NULL) {
        printf("%s could not be opend\n", INFILENAME);
        return -1;
    }
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    while ((c = getc(pIn)) != EOF) {
        if (c == ' ')
            continue;

        pfprintf(pOut, "%c is found", c);
        // push begin scopes onto the stack
        if (c == '{' || c == '(' || c == '[') {
            push(sp, c);
            pfprintf(pOut, " Pushed %c onto the stack\n", c);
        }
        // pop and verify end scopes out of the stack
        else if (c == '}' || c == ')' || c == ']') {
            popped = pop(sp);
            pfprintf(pOut, " Popped %c out of the stack", popped);
            if ((popped == '{' && c == '}') || (popped == '(' && c == ')') || (popped == '[' && c == ']'))
                pfprintf(pOut, " They matches. Correct scope.\n");
            else {
                pfprintf(pOut, " They does not match. Incorrect scope.\n");
                exit(1);
            }
        }
        else
            pfprintf(pOut, "\n");
    }

    pfprintf(pOut, "All scopes are correct\n");

    fclose(pIn);
    fclose(pOut);
}

// function verifies whether stack is empty
bool empty(STACK *ps) {
    return ps->top == EMPTYSTACK;
}

bool full(STACK *ps) {
    return ps->top == MAXSTACK - 1;
}

char pop(STACK *ps) {
    if (empty(ps)) {
        pfprintf(pOut, "stack underflow\n");
        exit(1);
    }
    return ps->stackelement[ps->top--];
}

void push(STACK *ps, char x) {
    if (full(ps)) {
        pfprintf(pOut, "stack overflow\n");
        exit(1);
    }
    else
        ps->stackelement[++(ps->top)] = x;
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
