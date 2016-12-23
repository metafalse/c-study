#include <stdio.h>
#include <stdlib.h>

#define MAXQUEUE 26
#define TRUE 1
#define FALSE 0

typedef struct queue {
    char queueelement[MAXQUEUE];
    int front, rear;
} CHQUEUE;

int empty (struct queue*);
char removedata (struct queue*);
void insert (struct queue*, char);

int main () {
    CHQUEUE alphqueue, *aqp;
    char seq, ch, keystroke;
    alphqueue.front = alphqueue.rear = -1;
    aqp = &alphqueue;
    
    int i;
    for (i = 0; i < MAXQUEUE; i++) {
        printf("\nPlease enter the next character in sequence: ");
        scanf("%c%c", &seq, &keystroke);
        insert(aqp, seq);
    }
    for (i = 0; i < MAXQUEUE; i++) {
        ch = removedata(aqp);
        printf("\nnext character in sequence is: %c", ch);
    }
    printf("\n\nEnd of character sequence ********\n");
}

int empty(CHQUEUE *pq) {
    if (pq->front == pq->rear)
        return TRUE;
    else
        return FALSE;
}

char removedata(CHQUEUE *pq) {
    if (empty(pq)) {
        printf("%s", "queue underflow");
        exit(1);
    }
    if (pq->front == MAXQUEUE -1)
        pq->front = 0;
    else
        (pq->front)++;
    return pq->queueelement[pq->front];
}

void insert(CHQUEUE *pq, char x) {
    if (pq->rear == MAXQUEUE -1)
        pq->rear = 0;
    else
        (pq->rear)++;
    if (pq->rear == pq->front) {
        printf("%s", "queue overflow");
        exit(1);
    }
    else
        pq->queueelement[pq->rear] = x;
}
