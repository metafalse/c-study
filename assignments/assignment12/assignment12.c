/******************************************************************************/
/*                                                                            */
/*  Topic: Sorting                                                            */
/*                                                                            */
/*  Objective: Implement 4 simple sort routines and 3 advanced sort routines  */
/*                                                                            */
/*  Comments: The code in chapter 18 & 19 modified to make it work as desired */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#define ASIZE 40
#define TRUE 1
#define FALSE 0
#define INFILENAME "input12.doc"
#define OUTFILENAME "output12.doc"

void swap(int *, int *);
void printarray(int *, int);
bool isValidInput(int, int, int);
void bubblesort(int *, int);
void insertsort(int *, int);
void selectionsort(int *, int);
void shellsort(int *, int, int *, int);
int partition(int *iap, int left, int right);
void quicksort(int *, int, int);
void heapsort(int *, int);
void mergesort(int *, int);
int pfprintf(FILE *, const char *, ...);

FILE *pIn, *pOut;

int main() {
    int item, choice = 0, numinc = 3, iar[ASIZE], increments[] = {5, 3, 1};

    // open input and output file
    if ((pIn = fopen(INFILENAME, "r")) == NULL) {
        printf("%s could not be opend\n", INFILENAME);
        return -1;
    }
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    // scan values from the input file into an array
    for (int i = 0; fscanf(pIn, "%d", &item) != EOF; i++)
        iar[i] = item;

    pfprintf(pOut, "Data in items in original order\n");
    printarray(iar, ASIZE);

    // menu for choosing a simple sort routine
    pfprintf(pOut, "1 Bubble Sort\n");
    pfprintf(pOut, "2 Insertion Sort\n");
    pfprintf(pOut, "3 Selection Sort\n");
    pfprintf(pOut, "4 Shell Sort\n");

    // prompt user to choose a simple sort routine
    do { 
        pfprintf(pOut, "Choose the simple sort routine from above: ");
        scanf(        "%d",  &choice);
        fprintf(pOut, "%d\n", choice);
        while (getchar() != '\n')
            continue;
    } while (!isValidInput(choice, 1, 4));

    // print the result of the simple sort routine
    switch (choice) {
        case 1:
            bubblesort(iar, ASIZE);
            pfprintf(pOut, "Result of bubble sort\n");
            break;
        case 2:
            insertsort(iar, ASIZE);
            pfprintf(pOut, "Result of insert sort\n");
            break;
        case 3:
            selectionsort(iar, ASIZE);
            pfprintf(pOut, "Result of selection sort\n");
            break;
        case 4:
            shellsort(iar, ASIZE, increments, numinc);
            pfprintf(pOut, "Result of shell sort\n");
            break;
    }
    printarray(iar, ASIZE);

    choice = 0;
    // menu for choosing a advanced sort routine
    pfprintf(pOut, "1 Quick Sort\n");
    pfprintf(pOut, "2 Heap Sort\n");
    pfprintf(pOut, "3 Merge Sort\n");

    // prompt user to choose an advanced sort routine
    do { 
        pfprintf(pOut, "Choose the advanced sort routine from above: ");
        scanf(        "%d",  &choice);
        fprintf(pOut, "%d\n", choice);
        while (getchar() != '\n')
            continue;
    } while (!isValidInput(choice, 1, 3));

    // print the result of the advanced sort routine
    switch (choice) {
        case 1:
            quicksort(iar, 0, ASIZE - 1);
            pfprintf(pOut, "Result of quick sort\n");
            break;
        case 2:
            heapsort(iar, ASIZE);
            pfprintf(pOut, "Result of heap sort\n");
            break;
        case 3:
            mergesort(iar, ASIZE);
            pfprintf(pOut, "Result of merge sort\n");
            break;
    }
    printarray(iar, ASIZE);

    fclose(pIn);
    fclose(pOut);
}

void swap(int *elem1ptr, int *elem2ptr) {
    int tmp;

    tmp = *elem1ptr;
    *elem1ptr = *elem2ptr;
    *elem2ptr = tmp;
}

void printarray(int *pap, int size) {
    int count;

    for (count = 0; count <= size -1; count++)
        pfprintf(pOut, "%4d", pap[count]);
    pfprintf(pOut, "\n");
}

bool isValidInput(int choice, int low, int high) {
    if (choice >= low && choice <= high)
        return TRUE;

    pfprintf(pOut, "invalid input\n");
    return FALSE;
}

void bubblesort(int *iap, int size) {
    int i, j;

    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - 1 - i; j++)
            if (iap[j] > iap[j + 1])
                swap(&iap[j], &iap[j + 1]);
}

void insertsort(int *iap, int size) {
    int i, j, tmp;

    for (i = 1; i < size; i++) {
        tmp = iap[i];
        for (j = i - 1; j >= 0 && tmp < iap[j]; j--)
            iap[j + 1] = iap[j];
        iap[j + 1] = tmp;
    }
}

void selectionsort(int *iap, int size) {
    int i, j, min;

    for (i = 0; i < size - 1; i++) {
        min = i;
        for (j = i + 1; j < size; j++)
            if (iap[j] < iap[min])
                min = j;
        swap(&iap[i], &iap[min]);
    }
}

void shellsort(int *iap, int size, int increments[], int numinc) {
    int incr, i, j, span, tmp;

    for (incr = 0; incr < numinc; incr++) {
        span = increments[incr];
        for (i = span; i < size; i++) {
            tmp = iap[i];
            for (j = i - span; j >= 0 && tmp < iap[j]; j -= span)
                iap[j + span] = iap[j];
            iap[j + span] = tmp;
        }
    }
}

int partition(int *iap, int left, int right) {
    int pivot = iap[left]; // final position is sought for pivot
    int up = right;
    int down = left;

    while (down < up) {
        while (iap[down] <= pivot && down < right)
            down++; // move up the array
        while (iap[up] > pivot)
            up--; // move down the array
        if (down < up)
            swap(&iap[down], &iap[up]);
    }
    swap (&iap[up], &iap[left]);

    return up;
}

void quicksort(int *iap, int left, int right) {
    if (left >= right)
        return; // array is sorted

    int index = partition(iap, left, right);
    quicksort(iap, left, index - 1);
    quicksort(iap, index + 1, right); 
}

void heapsort(int *iap, int size) {
    int i, elt, ch, pa, ivalue;
    // preprocessing phase; create initial heap

    for (i = 1; i < size; i++) {
        elt = iap[i];
        // pqinsert(iap, i, elt)
        ch = i;
        pa = (ch - 1) / 2;

        while (ch > 0 && iap[pa] < elt) {
            iap[ch] = iap[pa];
            ch = pa;
            pa = (ch - 1) / 2;
        }
        iap[ch] = elt;
    }
    // selection phase; repeatedly remove iap[0], insert it in its proper position and adjust the heap
    for (i = size - 1; i > 0; i--) {
        ivalue = iap[i]; // store last value of the heap into temporary variable
        iap[i] = iap[0]; // store root value of the heap into where last value of the heap was

        // from here adjust the heap
        pa = 0;
        // make ch largechild
        ch = i == 1 ? -1 : 1;
        if (i > 2 && iap[2] > iap[1])
            ch = 2;
        while (ch >= 0 && ivalue < iap[ch]) {
            iap[pa] = iap[ch];
            pa = ch;
            // make ch largechild
            ch = 2 * pa + 1;
            if (ch + 1 <= i - 1 && iap[ch] < iap[ch + 1])
                ch = ch + 1;
                if (ch > i - 1)
                    ch = -1;
        }
        iap[pa] = ivalue;
    }
}

void mergesort(int *iap, int size) {
    int aux[size], i, j, k, L1, L2, subsize, u1, u2;
    subsize = 1; // merge files of size 1
    while (subsize < size) {
        L1 = k = 0; // L1 are lower bounds of first file. k is index for auxiliary array
        while (L1 + subsize < size) {
            // compute remaining indices
            L2 = L1 + subsize;
            // proceed through the two sub-files
            u1 = L2 - 1;
            u2 = L2 + subsize - 1 < size ? L2 + subsize - 1 : size - 1;
            for (i = L1, j = L2; i <= u1 && j <= u2; k++)
                // enter smaller into the array aux
                aux[k] = iap[i] <= iap[j] ? iap[i++] : iap[j++];
            // at this point, one of the sub-files has been exhausted. Insert any remaining portions of the other file.
            for (; i <= u1; k++)
                aux[k] = iap[i++];
            for (; j <= u2; k++)
                aux[k] = iap[j++];
            // advance L1 to the start of the next pair of files
            L1 = u2 + 1;
        }
        // copy any remaining single file
        for (i = L1; k < size; i++)
            aux[k++] = iap[i];
        // copy aux into x and adjust size
        for (i = 0; i < size; i++)
            iap[i] = aux[i];
        subsize *= 2;
    }
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
