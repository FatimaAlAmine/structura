#include "header.h"

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

void botMove() {
    int row1, col1, row2, col2;
    do {
        row1 = rand() % (ROWS + 1);
        col1 = rand() % (COLS + 1);
        if (rand() % 2) {
            row2 = row1;
            col2 = (col1 < COLS) ? col1 + 1 : col1 - 1;
        } else {
            col2 = col1;
            row2 = (row1 < ROWS) ? row1 + 1 : row1 - 1;
        }
    } while (!isValidMove(row1, col1, row2, col2));
if (row1 == row2) {
        horizontal[row1][(col1 < col2) ? col1 : col2] = '-';
    } else {
        vertical[(row1 < row2) ? row1 : row2][col1] = '|';
    }
    printf("Bot made a move!\n");
}

int chooseDifficulty() {
    int level;
    printf("Choose bot difficulty:\n");
    printf("1. Easy (Random moves)\n");
    printf("2. Medium (Avoid setting up opponent)\n");
    printf("3. Hard (Prioritize completing boxes)\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &level);

    if (level < 1 || level > 3) {
        printf("Invalid choice. Defaulting to Easy.\n");
        level = 1;
    }
    return level;
}
