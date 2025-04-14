#include "header.h"

void moves(char player, int *row1, int *col1, int *row2, int *col2) {
    printf("%c's turn. Enter the row and the column of the first dot (e.g., 0 0 0 1): ", player);
    scanf("%d %d %d %d", row1, col1, row2, col2);

    if (*row1 == *row2 && (*col1 + 1 == *col2 || *col2 + 1 == *col1)) {
        int min_col = (*col1 < *col2) ? *col1 : *col2;
        if (*row1 >= 0 && *row1 <= ROWS && min_col >= 0 && min_col < COLS && horizontal[*row1][min_col] == ' ') {
            horizontal[*row1][min_col] = '-';
        } else {
            printf("Invalid move. Try again.\n");
            moves(player, row1, col1, row2, col2);
        }
    } 
    else if (*col1 == *col2 && (*row1 + 1 == *row2 || *row2 + 1 == *row1)) {
        int min_row = (*row1 < *row2) ? *row1 : *row2;
        if (min_row >= 0 && min_row < ROWS && *col1 >= 0 && *col1 <= COLS && vertical[min_row][*col1] == ' ') {
            vertical[min_row][*col1] = '|';
        } else {
            printf("Invalid move. Try again.\n");
            moves(player, row1, col1, row2, col2);
        }
    } 
    else {
        printf("Invalid move. Try again.\n");
        moves(player, row1, col1, row2, col2);
    }
}

bool isValidMove(int row1, int col1, int row2, int col2) {
    if (row1 == row2) { // Horizontal line
        int min_col = (col1 < col2) ? col1 : col2;
        return row1 >= 0 && row1 <= ROWS && min_col >= 0 && min_col < COLS && horizontal[row1][min_col] == ' ';
    } else if (col1 == col2) { // Vertical line
        int min_row = (row1 < row2) ? row1 : row2;
        return col1 >= 0 && col1 <= COLS && min_row >= 0 && min_row < ROWS && vertical[min_row][col1] == ' ';
    }
    return false; // Invalid move
}
