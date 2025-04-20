#include "header.h"

// Requires: player ('A' or 'B'), pointers for row1, col1, row2, col2 to store user input. Global arrays horizontal and vertical must be initialized with dimensions [ROWS + 1][COLS] and [ROWS][COLS + 1], respectively.
// Effect: Prompts the user to input coordinates for a valid move. If invalid input or move (not forming a horizontal or vertical connection, or if the edge is occupied), it re-prompts the user. Upon a valid move, it marks the corresponding edge in the horizontal or vertical array.
void moves(char player, int *row1, int *col1, int *row2, int *col2)
{
    printf("%c's turn. Enter the row and the column of the first and second dots (e.g., 0 0 0 1): ", player);
    if (scanf("%d %d %d %d", row1, col1, row2, col2) != 4)
    {
        printf("Invalid input. Please enter four integers.\n");
        while (getchar() != '\n');                             
        moves(player, row1, col1, row2, col2); // again
        return;
    }
    // horizontal connection?
    if (*row1 == *row2 && (*col1 + 1 == *col2 || *col2 + 1 == *col1))
    {
        int min_col = (*col1 < *col2) ? *col1 : *col2;
        if (*row1 >= 0 && *row1 <= ROWS && min_col >= 0 && min_col < COLS && horizontal[*row1][min_col] == ' ')
        {
            horizontal[*row1][min_col] = '-';
        }
        else
        {
            printf("Invalid move. Try again.\n");
            moves(player, row1, col1, row2, col2);
        }
    }
    else if (*col1 == *col2 && (*row1 + 1 == *row2 || *row2 + 1 == *row1))
    {
        int min_row = (*row1 < *row2) ? *row1 : *row2;
        if (min_row >= 0 && min_row < ROWS && *col1 >= 0 && *col1 <= COLS && vertical[min_row][*col1] == ' ')
        {
            vertical[min_row][*col1] = '|';
        }
        else
        {
            printf("Invalid move. Try again.\n");
            moves(player, row1, col1, row2, col2);
        }
    }
    else
    {
        printf("Invalid move. Try again.\n");
        moves(player, row1, col1, row2, col2);
    }
}

// Requires: User input to select a bot difficulty level (integer between 1 and 3: Easy, Medium, Hard).
// Effect: Prompts the user to choose a difficulty, reads the input, and defaults to Easy if invalid input is given. Returns the chosen difficulty level as an integer.
int chooseDifficulty()
{
    int level;
    printf("Choose bot difficulty:\n");
    printf("1. Easy \n");
    printf("2. Medium \n");
    printf("3. Hard \n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &level);
    if (level < 1 || level > 3)
    {
        printf("Invalid choice. Defaulting to Easy.\n");
        level = 1;
    }
    return level;
}
