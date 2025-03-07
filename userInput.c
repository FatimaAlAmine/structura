#include <stdio.h>
#include <stdbool.h>
#include "printGrid.c"


void moves(char player)
{
    // to connect a line we need 2 dots
    // row1 column1 dot row2 column2 second (4,0) (4,1)
    int row1;
    int row2;
    int column1;
    int column2;

    printf("%c's turn. Enter the row and the column of the first dot (e.g., A0 -> 0 0) and the second dot: ", player);
    scanf("%d %d %d %d", &row1, &column1, &row2, &column2);
    // this takes the input from the user

    // if both have same row but dif column "-" horizontal
    if (row1 == row2 && column1 + 1 == column2)
    {
        // check if conditions are good "empty" "numbers are +"
        if (row1 >= 0 && row1 <= ROWS && column1 >= 0 && column1 < COLS && horizontal[row1][column1] == ' ')
        {
            horizontal[row1][column1] = '-';
        }
        else
        {
            printf("Invalid move. Try again.\n");
            moves(player);
        }
        // if = columns but dif rows "|"
    }
    else if (column1 == column2 && row1 + 1 == row2)
    {
        // conditions
        if (row1 >= 0 && row1 < ROWS && column1 >= 0 && column1 <= COLS && vertical[row1][column1] == ' ')
        {
            vertical[row1][column1] = '|';
        }
        else
        {
            printf("Invalid move. Try again.\n");
            moves(player);
        }
    }
    else
    {
        printf("Invalid move. Try again.\n");
        moves(player);
    }
}
