#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "medium.h"
#include "botLogic.h"

bool boxHasThreeSides(int i, int j) {
    int count = 0;
    if (horizontal[i][j] == '-') count++;     // Top
    if (horizontal[i + 1][j] == '-') count++; // Bottom
    if (vertical[i][j] == '|') count++;       // Left
    if (vertical[i][j + 1] == '|') count++;   // Right

    return (count == 3); //true if 3 sides are filled
}
// bot medium level completes a box
void completeBox(int i, int j) {
    if (horizontal[i][j] == ' ') {
        horizontal[i][j] = '-';
    } else if (horizontal[i + 1][j] == ' ') {
        horizontal[i + 1][j] = '-';
    } else if (vertical[i][j] == ' ') {
        vertical[i][j] = '|';
    } else if (vertical[i][j + 1] == ' ') {
        vertical[i][j + 1] = '|';
    }
    box[i][j] = 'B'; // Bot takes the box
}



bool botMoveMedium(int row1, int col1, int row2, int col2) {
    int i, j;

    if (row1 == row2) { // Horizontal line
        i = row1;
        j = (col1 < col2) ? col1 : col2;

        // Box above
        if (i > 0 && box[i - 1][j] == ' ' && boxHasThreeSides(i - 1, j)) {
            completeBox(i - 1, j);
            printf("Bot completed the top box at (%d, %d)!\n", i - 1, j);
            return true; // Box completed
        }
        // Box below
        if (i < ROWS && box[i][j] == ' ' && boxHasThreeSides(i, j)) {
            completeBox(i, j);
            printf("Bot completed the bottom box at (%d, %d)!\n", i, j);
            return true; // Box completed
        }
    } else if (col1 == col2) { // Vertical line
        i = (row1 < row2) ? row1 : row2;
        j = col1;

        // Box to the left
        if (j > 0 && box[i][j - 1] == ' ' && boxHasThreeSides(i, j - 1)) {
            completeBox(i, j - 1);
            printf("Bot completed the left box at (%d, %d)!\n", i, j - 1);
            return true; // Box completed
        }
        // Box to the right
        if (j < COLS && box[i][j] == ' ' && boxHasThreeSides(i, j)) {
            completeBox(i, j);
            printf("Bot completed the right box at (%d, %d)!\n", i, j);
            return true; // Box completed
        }
    }

    // Make a random move if no box is completed
    botMove();
    return false; // No box completed
}
