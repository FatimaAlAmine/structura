 #ifndef BOARD_H
#define BOARD_H

#define ROWS 4
#define COLS 5

extern char horizontal[ROWS + 1][COLS];
extern char vertical[ROWS][COLS + 1];
extern char box[ROWS][COLS];

void emptyBoard();
void printGrid();

#endif
