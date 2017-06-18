/******************************************************************************/
/*                                                                            */
/*  Topic: Temperature                                                        */
/*                                                                            */
/*  Objective: Temperature conversion between Centigrade and Fahrenheit       */
/*                                                                            */
/*  Comments: Simple program doing calculation                                */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>

int main()
{
    int choice; // indicates the choice of conversion
    int temp; // temperature

    // prompt user to enter the choice
    puts("1) Centigrade to Fahrenheit");
    puts("2) Fahrenheit to Centigrade");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        // prompt user to enter the temperature value for conversion
        printf("Enter the temperature value in Centigrade: ");
        scanf("%d", &temp);

        // print the original and converted temperature degrees
        printf(
            "Centigrade scale is %d, equivalent Fahrenheit scale is %d\n",
            temp, temp * 9 / 5 + 32
        );
    }
    else if (choice == 2)
    {
        // prompt user to enter the temperature value for conversion
        printf("Enter the temperature value in Fahrenheit: ");
        scanf("%d", &temp);

        // print the original and converted temperature degrees
        printf(
            "Fahrenheit scale is %d, equivalent Centigrade scale is %d\n",
            temp, (temp - 32) * 5 / 9
        );
    }
    else
    {
        puts("Invalid choice");
    }
}
