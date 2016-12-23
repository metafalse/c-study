#include <stdio.h>
#include <stdlib.h>

#define MAXSTACK 26
#define EMPTYSTACK -1
#define TRUE 1
#define FALSE 0

typedef struct stack {
    int top;
    char stackelement[MAXSTACK];
} CHSTACK;

int empty(CHSTACK *);
char pop(CHSTACK *);
void push(CHSTACK *, char);

int main() {
    CHSTACK alphstack, *asp;
    char seq, ch, keystroke;
    alphstack.top = EMPTYSTACK;
    asp = &alphstack;

    int i;    
    for (i = 0; i < MAXSTACK; i++) {
        printf("\nPlease enter the next char in seq: ");
        scanf("%c%c", &seq, &keystroke);
        push(asp, seq);
    }
    
    for (i = 0; i < MAXSTACK; i++) {
        ch = pop(asp);
        printf("\nnext char in seq is: %c", ch);
    }
    printf("\n\nEnd of character seq **\n");
}

int empty(CHSTACK *ps) {
    if (ps->top == -1)
        return TRUE;
    else
        return FALSE;
}

char pop(CHSTACK *ps) {
    if (empty(ps)) {
        printf("%s", "stack underflow");
        exit(1);
    }
    return ps->stackelement[ps->top--];
}

void push(CHSTACK *ps, char x) {
    if (ps->top == MAXSTACK - 1) {
        printf("%s", "stack overflow");
        exit(1);
    }
    else
        ps->stackelement[++(ps->top)] = x;
}
