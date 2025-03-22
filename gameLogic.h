#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdbool.h>

void countScores(int *scoreA, int *scoreB);
bool checkAndMarkBox(char player);
bool gameEnd();

#endif
