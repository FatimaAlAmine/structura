#include <stdio.h>
#include "board.h"

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

    if (row1 == row2 && (column1 + 1 == column2 || column2 + 1 == column1)) {
        int min_col = (column1 < column2) ? column1 : column2;
        if (row1 >= 0 && row1 <= ROWS && min_col >= 0 && min_col < COLS && horizontal[row1][min_col] == ' ') {
            horizontal[row1][min_col] = '-';
        } else {
            printf("Invalid move. Try again.\n");
            moves(player);
        }
    } else if (column1 == column2 && (row1 + 1 == row2 || row2 + 1 == row1)) {
        int min_row = (row1 < row2) ? row1 : row2;
        if (min_row >= 0 && min_row < ROWS && column1 >= 0 && column1 <= COLS && vertical[min_row][column1] == ' ') {
            vertical[min_row][column1] = '|';
        } else {
            printf("Invalid move. Try again.\n");
            moves(player);
        }
    } else {
        printf("Invalid move. Try again.\n");
        moves(player);
    }
}
