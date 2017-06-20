/******************************************************************************/
/*                                                                            */
/*  Topic: Loops                                                              */
/*                                                                            */
/*  Objective: Print the average, maximum and minimum of all inputs received  */
/*                                                                            */
/*  Comments: Iterate the loop 15 times                                       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>

#define NUMBER_OF_SCORES 15

int main()
{
    int score; // stores a score user entered
    int max = 0; // initializes the maximum score to the lowest score 0
    int min = 100; // initializes the minimum score to the highest score 0
    float sum = 0; // initializes the sum to 0;

    // iterates a predetermined number of times
    for (size_t i = 0; i < NUMBER_OF_SCORES; i++)
    {
        // prompt user to enter a score until user enters valid score
        do
        {
            printf("Enter a score in the range 0 to 100: ");
            scanf("%d", &score);
        } while (score < 0 || score > 100);

        // print the score that user entered
        printf("You entered %d\n", score);

        if (score > max)
            max = score;

        if (score < min)
            min = score;

        sum += score;
    }

    // Print the average, maximum and minimum
    printf("Average: %f\n", sum / NUMBER_OF_SCORES);
    printf("Maximum: %d\n", max);
    printf("Minimum: %d\n", min);
}
