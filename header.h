#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define ROWS 4
#define COLS 5
#define INF 1000000
#define THREAD_COUNT 4

typedef struct {
    char horizontal[ROWS + 1][COLS];
    char vertical[ROWS][COLS + 1];
    char box[ROWS][COLS];

} GameState;

typedef struct {
    int row1, col1, row2, col2;
} Move;

typedef struct {
    int startRow, endRow, localScoreA, localScoreB;
} ScoreArgs;

// globals (defined in main.c)
// globals (defined in main.c)
extern char horizontal[ROWS + 1][COLS];
extern char vertical[ROWS][COLS + 1];
extern char box[ROWS][COLS];


//— generalgame.c —
void emptyBoard(void);
void printGrid(void);
void countScoresParallel(int *scoreA, int *scoreB);
bool checkAndMarkBox(char player);
bool gameEnd(void);
bool isValidMove(int row1,int col1,int row2,int col2);
void finalizeBoard(void);

//— 2v2player.c —
void moves(char player, int *row1, int *col1, int *row2, int *col2);
int  chooseDifficulty(void);

//— easy.c —
void botMove(void);

//— medium.c —
bool boxHasThreeSides(int i, int j);
void completeBox(int i, int j);
bool greedyCompleteAvailableBox(void);
bool createsThreeSidedBox(int r1,int c1,int r2,int c2);
Move pickRandomSafeMove(void);

//— hard.c —
void copyRealToState(GameState *state);
void copyState(GameState *dest, GameState *src);
bool isValidMoveState(GameState *state,int r1,int c1,int r2,int c2);
void applyMoveState(GameState *state, Move mv, char player, bool *boxCompleted);
int  evaluateState(GameState *state);
bool gameEndState(GameState *state);
int  getAvailableMoves(GameState *state, Move moves[], int maxMoves);
void shuffleMoves(Move moves[], int count);
int  minimax(GameState *state, int depth, bool isMaximizing, int alpha, int beta);
Move findBestMove(int depth);
void hardBotMove(void);

//— main.c —
int main(void);

#endif // HEADER_H
