/******************************************************************************/
/*                                                                            */
/*  Topic: Sequencing Cards                                                   */
/*                                                                            */
/*  Objective: Shuffle the cards and open the shuffled cards                  */
/*             as suggested above to show the required sequence               */
/*                                                                            */
/*  Comments: in a way in STRATEGY FOR SEQUENCING THE PLAYING CARDS.doc       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define MAXQUEUE 26
#define CARDS 13
#define DEFAULTPOS -1
#define TRUE 1
#define FALSE 0
#define INFILENAME "input16.doc"
#define OUTFILENAME "output16.doc"

typedef struct queue {
    char queueelement[MAXQUEUE];
    int front, rear;
} QUEUE;

void process();
bool isSameFrontAndRear(struct queue *);
char removedata(struct queue *);
void insert(struct queue *, char);
void displayQueue(struct queue *);
QUEUE shuffle(QUEUE *);
void reverse(struct queue *);
void open(struct queue *);
int pfprintf(FILE *, const char *, ...);

FILE *pIn, *pOut;

int main() {
    // open input and output file
    if ((pIn = fopen(INFILENAME, "r")) == NULL) {
        printf("%s could not be opend\n", INFILENAME);
        return -1;
    }
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    process();
    pfprintf(pOut, "\n");
    process();
    pfprintf(pOut, "\n");

    fclose(pIn);
    fclose(pOut);
}

void process() {
    char c;
    QUEUE original, shuffled;
    // initialize position of front and rear
    original.front = original.rear = shuffled.front = shuffled.rear = DEFAULTPOS;

    while (TRUE) {
        c = fgetc(pIn);
        if (c == '\n' || c == EOF)
            break;
        if (c == ' ' || c == '1') // 10 is dealt with as 0
            continue;
        insert(&original, c);
    }

    pfprintf(pOut, "original sequence: ");
    displayQueue(&original);

    shuffled = shuffle(&original);
    pfprintf(pOut, "shuffled queue: ");
    displayQueue(&shuffled);

    open(&shuffled);
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

void insert(QUEUE *pq, char c) {
    pq->rear = pq->rear == MAXQUEUE - 1 ? 0 : pq->rear + 1;
    // check for overflow condition
    if (isSameFrontAndRear(pq)) {
        pfprintf(pOut, "queue overflow");
        exit(1);
    }

    pq->queueelement[pq->rear] = c;
}

void displayQueue(QUEUE *pq) {
    int current = pq->front;

    if (isSameFrontAndRear(pq)) { // if empty
        pfprintf(pOut, "\n");
        return;
    }

    while (current != pq->rear) {
        current = current == MAXQUEUE - 1 ? 0 : current + 1;
        pfprintf(pOut, "%c ", pq->queueelement[current]);
    }
    pfprintf(pOut, "\n");
}

// return a shuffled queue from the original queue
QUEUE shuffle(QUEUE *pq) {
    QUEUE shuffled;
    shuffled.front = shuffled.rear = DEFAULTPOS; // initialize position of front and rear

    reverse(pq); // to get cards from rear of the original queue
    while (!isSameFrontAndRear(pq)) { // until pq is empty
        // insert the removed card from rear of the original queue into rear of the shuffled queue
        insert(&shuffled, removedata(pq));
        // insert the removed card from front of the shuffled queue into rear of the same queue
        insert(&shuffled, removedata(&shuffled));
        // display current contents of the shuffled queue
        pfprintf(pOut, "shuffle: ");
        displayQueue(&shuffled);
    }
    reverse(&shuffled); // to get cards from rear of the shuffled queue

    return shuffled;
}

// reverse contents of queue
void reverse(QUEUE *pq) {
    char tmp;
    int i, j;

    for (i = pq->front + 1, j = pq->rear; i < j; i++, j--) {
        tmp = pq->queueelement[i];
        pq->queueelement[i] = pq->queueelement[j];
        pq->queueelement[j] = tmp;
    }
}

// open cards from the shuffled set in the instructed way
void open(QUEUE *pq) {
    QUEUE opend;
    char openedCard;

    opend.front = opend.rear = DEFAULTPOS; // initialize position of front and rear

    while (!isSameFrontAndRear(pq)) { // until pq is empty
        insert(pq, removedata(pq)); // the top card from shuffled set go to the bottom of the set
        openedCard = removedata(pq); // the next top card is opened
        // display card now opend and insert it into the queue of opend cards
        pfprintf(pOut, "open: %c\n", openedCard);
        insert(&opend, openedCard);

        // display the rest of the shuffled set
        pfprintf(pOut, "shuffled queue: ");
        displayQueue(pq);
    }
    // display all opend cards in the queue
    pfprintf(pOut, "opend cards: ");
    displayQueue(&opend);
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
