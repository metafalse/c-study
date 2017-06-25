/******************************************************************************/
/*                                                                            */
/*  Topic: Tic Tac Toe                                                        */
/*                                                                            */
/*  Objective: Implement a 4x4 tic-tac-toe game                               */
/*                                                                            */
/*  Comments: Thee player who obtains 4 X’s (or 4 O’s)                        */
/*            in a row – vertical, horizontal, or diagonal – wins.            */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#define SIZE 4
#define DEFAULT '*'
#define PLAYER_1 'X'
#define PLAYER_2 'O'
#define FALSE 0
#define TRUE 1
#define OUTFILENAME "output6.doc"

void initializeBoard();
void displayBoard();
bool isValidInput();
bool isGameOver();
bool isBoardFull();
bool isWinner();
bool isAnyRowFull();
bool isRowFull(int);
bool isAnyColFull();
bool isColFull(int);
bool isMajorDiagonalFull();
bool isMinorDiagonalFull();
int pfprintf(FILE *, const char *, ...);

char board[SIZE][SIZE];
char current; // current player's symbol
int rowEntered = -1, colEntered = -1; // initialize by values out of range
FILE *pOut;

int main() {
    // open output file
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    initializeBoard();
    displayBoard();

    while (!isGameOver()) {
        current = current == PLAYER_1 ? PLAYER_2 : PLAYER_1; // change player's symbol

        // prompt user to enter where to move
        do {
            pfprintf(pOut, "Please enter %c's move as \"row column\": ", current);
            scanf(        "%d %d",  &rowEntered, &colEntered);
            fprintf(pOut, "%d %d\n", rowEntered,  colEntered);
            while (getchar() != '\n')
                continue;
        } while (!isValidInput());

        board[rowEntered][colEntered] = current; // place the player's symbol
        displayBoard();
    }

    if (isBoardFull())
        pfprintf(pOut, "Board is full\n");
    if (isWinner())
        pfprintf(pOut, "%c is winner\n", current);

    fclose(pOut);
}

void initializeBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = DEFAULT;
}

void displayBoard() {
    pfprintf(pOut, "  0 1 2 3\n");

    for (int i = 0; i < SIZE; i++) {
        pfprintf(pOut, "%d ", i);

        for (int j = 0; j < SIZE; j++) {
            pfprintf(pOut, "%c", board[i][j]);
            pfprintf(pOut, j == SIZE - 1 ? "\n" : " ");
        }
    }
}

bool isValidInput() {
    if (rowEntered >= 0 && rowEntered <= 3 && colEntered >= 0 && colEntered <= 3 &&
            board[rowEntered][colEntered] == DEFAULT)
        return TRUE;

    pfprintf(pOut, "invalid input\n");
    return FALSE;
}

bool isGameOver() {
    return isBoardFull() || isWinner();
}

bool isBoardFull() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == DEFAULT)
                return FALSE;

    return TRUE;
}

bool isWinner() {
    return isAnyRowFull() || isAnyColFull() || isMajorDiagonalFull() || isMinorDiagonalFull();
}

bool isAnyRowFull() {
    for (int i = 0; i < SIZE; i++)
        if (isRowFull(i))
            return TRUE;

    return FALSE;
}

bool isRowFull(int rowIdx) {
    for (int i = 0; i < SIZE; i++)
        if (board[rowIdx][i] != current)
            return FALSE;

    return TRUE;
}

bool isAnyColFull() {
    for (int i = 0; i < SIZE; i++)
        if (isColFull(i))
            return TRUE;

    return FALSE;
}

bool isColFull(int colIdx) {
    for (int i = 0; i < SIZE; i++)
        if (board[i][colIdx] != current)
            return FALSE;

    return TRUE;
}

bool isMajorDiagonalFull() {
    for (int i = 0; i < SIZE; i++)
        if (board[i][i] != current)
            return FALSE;

    return TRUE;
}

bool isMinorDiagonalFull() {
    for (int i = 0; i < SIZE; i++)
        if (board[i][SIZE - 1 - i] != current)
            return FALSE;

    return TRUE;
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
