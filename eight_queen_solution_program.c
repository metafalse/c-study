#include <stdio.h>
#include <stdbool.h>

#define BOARDSIZE 8
#define DIAGONAL (2 * BOARDSIZE - 1)
#define DOWNOFFSET 7
#define FALSE 0
#define TRUE 1

void writeBoard(void);
void clearBoard(void);
void addQueen(void);

int queencol[BOARDSIZE];
bool colfree[BOARDSIZE];
bool upfree[DIAGONAL];
bool downfree[DIAGONAL];
int queencount = -1;
int numsol = 0;

int main() {
    int i;
    for (i = 0; i < BOARDSIZE; i++) {
        clearBoard();
        queencol[++queencount] = i;
        colfree[i] = FALSE;
        upfree[queencount + i] = FALSE;
        downfree[queencount - i + DOWNOFFSET] = FALSE;
        addQueen();
    }
}

void addQueen() {
    int col;
    queencount++;
    
    for (col = 0; col < BOARDSIZE; col++) {
        if (colfree[col] && upfree[queencount + col] &&
            downfree[queencount - col + DOWNOFFSET]) {
            queencol[queencount] = col;
            colfree[col] = FALSE;
            upfree[queencount + col] = FALSE;
            downfree[queencount - col + DOWNOFFSET] = FALSE;
            if (queencount == BOARDSIZE - 1) {
                printf("\n%d Queen Solution: %d\n\n", 8, ++numsol);
                writeBoard();
            }
            else
                addQueen();
            if (queencount - 1 < 0)
                continue;
            colfree[col] = TRUE;
            upfree[queencount - 1 + col] = TRUE;
            downfree[queencount - 1 - col + DOWNOFFSET] = TRUE;
            queencount--;
        }
    }
}

void writeBoard(void) {
    int col;
    static int qcount = 0;
    for (col = 0; col < BOARDSIZE; col++) {
        if (queencol[qcount] == col)
            printf("Q   ");
        else
            printf("*   ");
    }
    printf("\n\n");
    if (qcount++ < BOARDSIZE - 1)
        writeBoard();
    qcount = 0;
}

void clearBoard() {
    for (int i = 0; i < BOARDSIZE; i++) {
        colfree[i] = TRUE;
        queencol[i] = -1;
    }
    for (int j = 0; j < DIAGONAL; j++) {
        upfree[j] = TRUE;
        downfree[j] = TRUE;
    }
    queencount = -1;
}
