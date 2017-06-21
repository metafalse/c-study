/******************************************************************************/
/*                                                                            */
/*  Topic: Array Manipulations                                                */
/*                                                                            */
/*  Objective: Print the array in original, reversed and ascending order      */
/*             Print the indices of the indicated number                      */
/*                                                                            */
/*  Comments: Iterates a predetermined number of times                        */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>

#define ASIZE 40 // size of array or number of integers
#define NUMBER_OF_IDENTIFICATIONS 9 // do identification this number of times

int main()
{
    int ia[ASIZE]; // stores integers that user entered
    int tmp; // temporary integer valiable
    size_t i, j, pass; // loop counters

    // prompt to user to enter integers a predetermined number of times
    for (i = 0; i < ASIZE; i++)
    {
        printf("Enter a integer: ");
        scanf("%d", &ia[i]);
    }

    // print the array
    printf("\nData items in original order:\n");
    for (i = 0; i < ASIZE; i++)
        printf("%4d", ia[i]);

    // reverse the arary
    for (i = 0, j = ASIZE - 1; i < ASIZE / 2; i++, j--)
    {
        tmp = ia[i];
        ia[i] = ia[j];
        ia[j] = tmp;
    }

    // print the array
    printf("\nData items in reversed order:\n");
    for (i = 0; i < ASIZE; i++)
        printf("%4d", ia[i]);

    // bubble sort
    for (pass = ASIZE; pass > 0; pass--)
    {
        for (i = 0; i < pass - 1; i++)
        {
            if (ia[i] > ia[i + 1])
            {
                tmp = ia[i];
                ia[i] = ia[i + 1];
                ia[i + 1] = tmp;
            }
        }
    }

    // print the array
    printf("\nData items in ascending order:\n");
    for (i = 0; i < ASIZE; i++)
        printf("%4d", ia[i]);

    // iterates a predetermined number of times
    for (i = 0; i < NUMBER_OF_IDENTIFICATIONS; i++)
    {
        // prompt user to enter the value to be searched
        printf("\nPlease enter the value to be searched: ");
        scanf("%d", &tmp);

        // iterate through the array
        for (j = 0; j < ASIZE; j++)
        {
            // when the value is found
            if (ia[j] == tmp)
            {
                printf(
                    "Found the value %d in the array at subscript: %lu",
                    tmp,
                    j
                );
                break;
            }

            // when coming here last element without break
            if (j == ASIZE -1)
                printf("Not found the value in the array");
        }
    }
    puts("");
}
