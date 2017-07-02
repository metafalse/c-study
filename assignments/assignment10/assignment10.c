/******************************************************************************/
/*                                                                            */
/*  Topic: Recursion                                                          */
/*                                                                            */
/*  Objective: Implement Tower of Hanoi problem                               */
/*                                                                            */
/*  Comments: Just call a recursive function                                  */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdarg.h>

#define OUTFILE4NAME "output10-4.doc"
#define OUTFILE5NAME "output10-5.doc"
#define OUTFILE6NAME "output10-6.doc"

FILE *pOut;
int currentDiskToTarget;

void moveHanoi(int, char, char, char);
int pfprintf(FILE *, const char *, ...);

int main() {
    if ((pOut = fopen(OUTFILE4NAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILE4NAME);
        return -1;
    }
    pfprintf(pOut, "Run the program with 4 disks\n");
    currentDiskToTarget = 4;
    moveHanoi(4, 'A', 'B', 'C');

    if ((pOut = fopen(OUTFILE5NAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILE5NAME);
        return -1;
    }
    pfprintf(pOut, "Run the program with 5 disks\n");
    currentDiskToTarget = 5;
    moveHanoi(5, 'A', 'B', 'C');

    if ((pOut = fopen(OUTFILE6NAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILE6NAME);
        return -1;
    }
    pOut = fopen("output10-6.doc", "w");
    pfprintf(pOut, "Run the program with 6 disks\n");
    currentDiskToTarget = 6;
    moveHanoi(6, 'A', 'B', 'C');

    fclose(pOut);
}

// move function using recursion
void moveHanoi(int n, char from, char aux, char to) {
    if (n == 0)
        return;

    moveHanoi(n - 1, from, to, aux); // move disks from 'from' to 'aux' using 'to' as auxiliary pole

    if (n == currentDiskToTarget && to == 'C') { // if this is final move of any disk
        currentDiskToTarget--;
        pfprintf(pOut, "Final ");
    }
    pfprintf(pOut, "Move of disk %d from %c to %c\n", n, from, to);

    moveHanoi(n - 1, aux, from, to); // move disks from 'aux' to 'to' using 'from' as auxiliary pole
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
