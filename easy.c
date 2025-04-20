#include "header.h"

// Requires: Initialized horizontal and vertical arrays, defined ROWS and COLS constants, and the isValidMove function for move validation.
// Effect: Randomly selects a valid move for the bot, updates the grid with the move, and prints the move in the format "Bot made move: row1 col1 row2 col2".
void botMove()
{
    int row1, col1, row2, col2;
    do
    {
        row1 = rand() % (ROWS + 1);
        col1 = rand() % (COLS + 1);
        if (rand() % 2)
        {
            row2 = row1;
            col2 = (col1 < COLS) ? col1 + 1 : col1 - 1;
        }
        else
        {
            col2 = col1;
            row2 = (row1 < ROWS) ? row1 + 1 : row1 - 1;
        }
    } while (!isValidMove(row1, col1, row2, col2));
    if (row1 == row2)
        horizontal[row1][(col1 < col2 ? col1 : col2)] = '-';
    else
        vertical[(row1 < row2 ? row1 : row2)][col1] = '|';
    printf("Bot made move: %d %d %d %d\n", row1, col1, row2, col2);
}
