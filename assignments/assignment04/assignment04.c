/******************************************************************************/
/*                                                                            */
/*  Topic: Student & Class Grading                                            */
/*                                                                            */
/*  Objective: Read scores of several tests from input file and               */
/*             Write the statistics into output file for each students        */
/*             as well as for all the students                                */
/*                                                                            */
/*  Comments: Prompt user to enter number of students                         */
/*            No variable or function of lettergrade                          */
/*            to avoid using a pointer of char                                */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#define NUMBER_OF_SCORES 60
#define FALSE 0
#define TRUE 1
#define INFILENAME "input04.doc"
#define OUTFILENAME "output04.doc"

bool isValidInput();
void process();
int getStudentId();
int pfprintf(FILE *, const char *, ...);

FILE *pIn, *pOut;
static int studentId = 1000;
int numOfStudents;

int main() {
    // open input and outputfile
    if ((pIn = fopen(INFILENAME, "r")) == NULL) {
        printf("%s could not be opend\n", INFILENAME);
        return -1;
    }
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    // prompt user to enter number of students
    do {
        pfprintf(pOut, "For how many students? (4 to 6): ");
        scanf(        "%d",  &numOfStudents);
        fprintf(pOut, "%d\n", numOfStudents);
        while (getchar() != '\n')
            continue;
    } while (!isValidInput());

    // write stats
    process();
}

bool isValidInput() {
    if (numOfStudents >= 4 && numOfStudents <= 6)
        return TRUE;

    pfprintf(pOut, "invalid input\n");
    return FALSE;
}

// write stats and scores for each student as well as combined stats for all the students
void process() {
    int i, j, tmp, sid, min, max, minall, maxall;
    float sum, sumall;
    minall = 100; // initialize minimum score to highest value 100
    maxall = 0; // initialize maximum score to lowest value 0

    // loop through all students
    for (i = 0; i < numOfStudents; i++) {
        min = 100; // initialize minimum score to highest value 100
        max = sum = 0; // initialize maximum score to lowest value 0
        sid = getStudentId();
        pfprintf(pOut, "\nStudent number: %d\n", sid);
        pfprintf(pOut, "Test scores:\n");

        // loop through all test scores of each student
        for (j = 0; j < NUMBER_OF_SCORES / numOfStudents; j++) {
            fscanf(pIn, "%d", &tmp);

            // write score and letter grade
            pfprintf(pOut, "Subject %d: %d ", j, tmp);
            // determine letter grade
            if      (tmp >  95) pfprintf(pOut, "A+\n");
            else if (tmp == 95) pfprintf(pOut, "A\n");
            else if (tmp >= 90) pfprintf(pOut, "A-\n");
            else if (tmp >  85) pfprintf(pOut, "B+\n");
            else if (tmp == 85) pfprintf(pOut, "B\n");
            else if (tmp >= 80) pfprintf(pOut, "B-\n");
            else if (tmp >  75) pfprintf(pOut, "C+\n");
            else if (tmp == 75) pfprintf(pOut, "C\n");
            else if (tmp >= 70) pfprintf(pOut, "C-\n");
            else if (tmp >= 60) pfprintf(pOut, "D\n");
            else                pfprintf(pOut, "F\n");

            if (tmp < min)
                min = tmp;
            if (tmp > max)
                max = tmp;
            sum += tmp;
            sumall += tmp;
        }
        pfprintf(pOut, "\nAverage of student %d: %f\n", sid, sum / (NUMBER_OF_SCORES / numOfStudents));
        pfprintf(pOut, "Minimum of student %d: %d\n",   sid, min);
        pfprintf(pOut, "Maximum of student %d: %d\n",   sid, max);

        if (min < minall)
            minall = min;
        if (max > maxall)
            maxall = max;
    }

    // write stats for all students into output file
    pfprintf(pOut, "\nAverage of all students: %f\n", sumall / NUMBER_OF_SCORES);
    pfprintf(pOut, "Minimum of all students: %d\n", minall);
    pfprintf(pOut, "Maximum of all students: %d\n", maxall);
}

// return student number incremented
int getStudentId() {
    return studentId++;
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
