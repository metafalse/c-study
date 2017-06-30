/******************************************************************************/
/*                                                                            */
/*  Topic: Queues                                                             */
/*                                                                            */
/*  Objective: Implement a queue data structure using an array                */
/*                                                                            */
/*  Comments: The code in chapter 21 modified to make it work as desired      */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define MAXQUEUE 26
#define DEFAULTPOS -1
#define TRUE 1
#define FALSE 0
#define INFILENAME "input9.doc"
#define OUTFILENAME "output9.doc"

typedef struct queue {
    int queueelement[MAXQUEUE];
    int front, rear;
} QUEUE;

bool isSameFrontAndRear(QUEUE *);
char removedata(QUEUE *);
void insert(QUEUE *, int);
void displayQueue(QUEUE *);
int pfprintf(FILE *, const char *, ...);

FILE *pIn, *pOut;

int main() {
    char c;
    int data, removed;
    QUEUE queue, *pq;
    pq = &queue;
    queue.front = queue.rear = DEFAULTPOS;

    // open input and output file
    if ((pIn = fopen(INFILENAME, "r")) == NULL) {
        printf("%s could not be opend\n", INFILENAME);
        return -1;
    }
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    displayQueue(pq);
    while ((c = fgetc(pIn)) != EOF) {
        switch (c) {
            case 'E': // ENQUE
                fscanf(pIn, "%d", &data);
                insert(pq, data);
                pfprintf(pOut, "INPUT: %c %d\n", c, data);
                pfprintf(pOut, "Inserted %d into the queue\n", data);
                break;
            case 'D': // DEQUE
                pfprintf(pOut, "INPUT: %c\n", c);
                removed = removedata(pq);
                pfprintf(pOut, "Removed %d out of the queue\n", removed);
                break;
        }
        displayQueue(pq);
    }

    fclose(pIn);
    fclose(pOut);
}

bool isSameFrontAndRear(QUEUE *pq) {
    return pq->front == pq->rear;
}

char removedata(QUEUE *pq) {
    if (isSameFrontAndRear(pq)) { // if empty
        pfprintf(pOut, "queue underflow");
        exit(1);
    }

    pq->front = pq->front == MAXQUEUE - 1 ? 0 : pq->front + 1;
    return pq->queueelement[pq->front];
}

void insert(QUEUE *pq, int x) {
    pq->rear = pq->rear == MAXQUEUE - 1 ? 0 : pq->rear + 1;
    // check for overflow condition
    if (isSameFrontAndRear(pq)) {
        pfprintf(pOut, "queue overflow");
        exit(1);
    }

    pq->queueelement[pq->rear] = x;
}

void displayQueue(QUEUE *pq) {
    int current;

    pfprintf(pOut, "Current queue: ");
    if (isSameFrontAndRear(pq)) { // if empty
        pfprintf(pOut, "\n");
        return;
    }

    current = pq->front;
    while (current != pq->rear) {
        current = current == MAXQUEUE - 1 ? 0 : current + 1;
        pfprintf(pOut, "%d ", pq->queueelement[current]);
    }
    pfprintf(pOut, "\n");
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
