/******************************************************************************/
/*                                                                            */
/*  Topic: N Queens                                                           */
/*                                                                            */
/*  Objective: Place 8 queens on an 8 x 8 chess board so that none of the     */
/*             queens attack each other                                       */
/*                                                                            */
/*  Comments: The code in chapter 23 modified to make it work as desired      */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#define BOARDSIZE 8
#define DIAGONAL 2 * BOARDSIZE - 1
#define DOWNOFFSET 7
#define FALSE 0
#define TRUE 1
#define OUTFILENAME "output7.doc"

bool isValidInput();
void clearBoard();
void addQueen();
void writeBoard();
int pfprintf(FILE *, const char *, ...);

int queencol[BOARDSIZE]; // queen column
bool colfree[BOARDSIZE]; // is column free
bool upfree[DIAGONAL]; // up diagonal free
bool downfree[DIAGONAL]; // down diagonal free
int queencount = -1; // row queen is placed
int numsol = 0; // number of solutions found
int colIdx = -1; // initial row number initialized by value out of range
FILE *pOut;

int main() {
    char cont;

    // open output file
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    do {
        // prompt user to enter where to move
        do {
            pfprintf(pOut, "Enter initial row number: ");
            scanf(        "%d",  &colIdx);
            fprintf(pOut, "%d\n", colIdx);
            while (getchar() != '\n')
                continue;
        } while (!isValidInput());

        clearBoard();
        // put the queen in initial row
        queencol[++queencount] = colIdx;
        colfree[colIdx] = FALSE;
        upfree[queencount + colIdx] = FALSE;
        downfree[queencount - colIdx + DOWNOFFSET] = FALSE;

        addQueen();

        pfprintf(pOut, "Continue? (y/n): ");
        scanf(        "%c",  &cont);
        fprintf(pOut, "%c\n", cont);
    } while (cont == 'y');

    fclose(pOut);
}

bool isValidInput() {
    if (colIdx >= 0 && colIdx <= 7)
        return TRUE;

    pfprintf(pOut, "invalid input\n");
    return FALSE;
}

// clears the board for next placement
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

void addQueen() {
    int col; // column being tried for the queen
    queencount++;
    
    for (col = 0; col < BOARDSIZE; col++) {
        if (!colfree[col] || !upfree[queencount + col] || !downfree[queencount - col + DOWNOFFSET])
            continue;

        // put the queen in position(queencount, col)
        queencol[queencount] = col;
        colfree[col] = FALSE;
        upfree[queencount + col] = FALSE;
        downfree[queencount - col + DOWNOFFSET] = FALSE;

        if (queencount == BOARDSIZE - 1) { // terminal condition
            pfprintf(pOut, "\n%d Queen Solution: %d\n\n", 8,   numsol);
            writeBoard();
        }
        else
            addQueen(); // recursive call

        if (queencount - 1 < 0)
            continue;

        colfree[col] = TRUE; // backtrack queen
        upfree[queencount - 1 + col] = TRUE;
        downfree[queencount - 1 - col + DOWNOFFSET] = TRUE;
        queencount--;
    }
}

// prints the output of N queens placement
void writeBoard() {
    int col;
    static int qcount = 0;

    for (col = 0; col < BOARDSIZE; col++)
        pfprintf(pOut, queencol[qcount] == col ? (qcount == 0 ? "U    " : "Q    ") : "*    ");
    pfprintf(pOut, "\n\n");

    if (qcount++ < BOARDSIZE - 1)
        writeBoard();
    qcount = 0;
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
