#include "header.h"

// fxn to count the scores for the players and update them
void countScores(int *scoreA, int *scoreB) {
    // initialize scores to zero
    *scoreA = 0;
    *scoreB = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
           
            if (box[i][j] == 'A') { // if square is completed by A
                (*scoreA)++; //dereference scoreA & increment it
               
            } else if (box[i][j] == 'B') { // if square is completed by B
                (*scoreB)++; // dereference scoreB & increment it
            }
        }
    }
}

// fxn to check and mark the completed squares
bool checkAndMarkBox(char player) {
    bool completedBox = false; //flag for the completed boxes
   
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            //check if box is completed
            if (horizontal[i][j] == '-' && horizontal[i + 1][j] == '-' &&
                vertical[i][j] == '|' && vertical[i][j + 1] == '|' && box[i][j] == ' ') {
                 // mark the xompleted box with the player's initial (A or B).    
                box[i][j] = player;
                completedBox = true;
            }
        }
    }
    return completedBox;
}
//check if the game has ended 
bool gameEnd() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (box[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}
