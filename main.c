
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"      
#include "moves.h"       
#include "gameLogic.h"   
#include "botLogic.h"     


int main() {
    srand(time(NULL)); // Seed the random number generator
    emptyBoard();
    char player = 'A';
    int scoreA = 0, scoreB = 0;
    char opponent;
    printf("Choose opponent: (H)uman or (B)ot? ");
    scanf(" %c", &opponent);
    bool againstBot = (opponent == 'B' || opponent == 'b'); // Handle lowercase 'b'
    int difficulty = 1; // Default to Easy

    if (againstBot) {
        difficulty = chooseDifficulty();
    }

    while (!gameEnd()) {
        printGrid(); // Print the current state of the board
    
        if (player == 'A') {
            moves(player); // Player A's turn (human)
        } else if (againstBot) {
            botMove(); // Player B's turn (bot)
        } else {
            moves(player); // Player B's turn (human)
        }
    
        bool completedBox = checkAndMarkBox(player); // Check and mark completed boxes
    
        countScores(&scoreA, &scoreB); // Update the scores
        // Conditional score display
        if (againstBot) {
            printf("Player A score: %d\n", scoreA);
            printf("Bot score     : %d\n", scoreB);
        } else {
            printf("Player A score: %d\n", scoreA);
            printf("Player B score: %d\n", scoreB);
        }
        if (!completedBox) {
            player = (player == 'A') ? 'B' : 'A'; // Switch turns if no box is completed
            }
        }

    countScores(&scoreA, &scoreB);
    printf("Game Over! Player A score: %d, Player B score: %d\n", scoreA, scoreB);
    printf("Winner: %s\n", (scoreA > scoreB) ? "Player A" : (scoreB > scoreA) ? "Player B" : "It's a tie!");

    return 0;
}
