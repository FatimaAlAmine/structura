#ifndef HEADER_H
#define HEADER_H

//for all functions
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// board.h
#define ROWS 4
#define COLS 5

extern char horizontal[ROWS + 1][COLS];
extern char vertical[ROWS][COLS + 1];
extern char box[ROWS][COLS];

void emptyBoard();
void printGrid();

// botLogic.h
void botMove();
int chooseDifficulty();

// gameLogic.h

void countScores(int *scoreA, int *scoreB);
bool checkAndMarkBox(char player);
bool gameEnd();

// medium.h
bool botMoveMedium(int row1, int col1, int row2, int col2);

// moves.h
void moves(char player, int *row1, int *col1, int *row2, int *col2);
bool isValidMove(int row1, int col1, int row2, int col2);

#endif
