#include "header.h"


int main() {
    srand(time(NULL)); // Seed the random number generator
    emptyBoard();
    char player = 'A';
    int scoreA = 0, scoreB = 0;
    char opponent;
    
    int row1, col1, row2, col2; //store the last move
    
    printf("Choose opponent: (H)uman or (B)ot? ");
    scanf(" %c", &opponent);
    bool againstBot = (opponent == 'B' || opponent == 'b'); // Handle lowercase 'b'
    int difficulty = 1; // Default to Easy

    if (againstBot) {
        difficulty = chooseDifficulty();
    }

       while (!gameEnd()) {
    printGrid();

    if (player == 'A') {
        moves(player, &row1, &col1, &row2, &col2);
    } else if (againstBot) {
        do {
            // Keep bot playing as long as it completes boxes
            bool completedBox = false;

            if (difficulty == 1) {
                botMove();
            } else if (difficulty == 2) {
                completedBox = botMoveMedium(row1, col1, row2, col2); // Returns true if it completes a box
            } else {
                botMove(); // Future hard-level bot logic
            }

            // Check if the bot completed another box
            completedBox |= checkAndMarkBox('B'); // Verify additional box completion

            countScores(&scoreA, &scoreB);

            // Update score display
            printf("Player A score: %d\n", scoreA);
            printf("Bot score     : %d\n", scoreB);

            if (!completedBox) {
                // Exit bot loop if no boxes were completed
                break;
            }
        } while (true); // Repeat until the bot fails to complete a box
    } else {
        moves(player, &row1, &col1, &row2, &col2);
    }

    // Switch turns unless the bot/human completes a box
    bool completedBox = checkAndMarkBox(player);
    if (!completedBox) {
        player = (player == 'A') ? 'B' : 'A'; // Switch turns
    }
}

    
    countScores(&scoreA, &scoreB);
    printf("Game Over! Player A score: %d, Player B score: %d\n", scoreA, scoreB);
    printf("Winner: %s\n", (scoreA > scoreB) ? "Player A" : (scoreB > scoreA) ? "Player B" : "It's a tie!");

    return 0;
}
