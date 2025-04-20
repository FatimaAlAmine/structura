#include "header.h"

char horizontal[ROWS + 1][COLS] = {0};
char vertical[ROWS][COLS + 1] = {0};
char box[ROWS][COLS] = {0};

int main()
{
    srand(time(NULL)); //random 
    emptyBoard();
    char player = 'A';
    int scoreA = 0, scoreB = 0;
    char opponent;
    int row1, col1, row2, col2;
    char input[100];

    // Human or Bot?
    do
    {
        printf("Choose opponent: (H)uman or (B)ot? ");
        fgets(input, sizeof(input), stdin);
        if ((input[0] == 'H' || input[0] == 'h' ||
             input[0] == 'B' || input[0] == 'b') &&
            input[1] == '\n')
        {
            opponent = input[0];
            break;
        }
        else
        {
            printf("Invalid input. Please enter only H or B.\n");
        }
    } while (1);

    bool againstBot = (opponent == 'B' || opponent == 'b');
    int difficulty = 1;
    if (againstBot)
    {
        difficulty = chooseDifficulty();
    }

    // Continue until every box in the grid is claimed.
    while (!gameEnd())
    {
        printf("\nCurrent board:\n");
        printGrid();
        printf("\n%c's turn.\n", player);

        if (player == 'A')
        { // human
            moves(player, &row1, &col1, &row2, &col2);
            bool extraTurn = checkAndMarkBox(player); // get an extra turn depending if scored
            countScoresParallel(&scoreA, &scoreB);
            printf("\nScore Update:\n");
            printf("Player A score: %d\n", scoreA);
            if (againstBot)
                printf("Bot score     : %d\n", scoreB);
            else
                printf("Player B score: %d\n", scoreB);
            if (extraTurn && !gameEnd())
            {
                printf("\nExtra move for %c!\n", player);
            }
            else if (!gameEnd())
            { // switch 
                player = (player == 'A') ? 'B' : 'A';
            }
        }
        else
        {
            // Opponent's turn (for Bot or second human).
            if (againstBot)
            {
                bool moveCompleted; // Local flag for whether the move completed a box.
                do
                {
                    if (difficulty == 1)
                    {
                        botMove();
                        moveCompleted = checkAndMarkBox('B');
                    }
                    else if (difficulty == 2)
                    {
                        // Try to claim a box with 3 sides already drawn
                        bool greedy = greedyCompleteAvailableBox(); // completes & claims the first such box (and prints the move)

                        // If no box was available, make a safe random move
                        if (!greedy)
                        {
                            Move m = pickRandomSafeMove();
                            if (m.row1 == m.row2)
                            {
                                horizontal[m.row1][(m.col1 < m.col2 ? m.col1 : m.col2)] = '-';
                            }
                            else
                            {
                                vertical[(m.row1 < m.row2 ? m.row1 : m.row2)][m.col1] = '|';
                            }
                            printf("Bot made move: %d %d %d %d\n", m.row1, m.col1, m.row2, m.col2);
                        }

                        //  Mark any additional boxes completed by that move
                        bool extra = checkAndMarkBox('B');

                        // Only one extra turn if any box was claimed
                        moveCompleted = greedy || extra;
                    }

                    else if (difficulty == 3)
                    { // minimax strategy
                        hardBotMove();
                        moveCompleted = checkAndMarkBox('B');
                    }
                    countScoresParallel(&scoreA, &scoreB);
                    printf("\nScore Update:\n");
                    printf("Player A score: %d\n", scoreA);
                    if (againstBot)
                        printf("Bot score     : %d\n", scoreB);
                    else
                        printf("Player B score: %d\n", scoreB);
                    if (moveCompleted && !gameEnd())
                    {
                        printf("\nExtra move for B!\n");
                        printGrid();
                    }
                } while (moveCompleted && !gameEnd());
                if (!gameEnd())
                {
                    player = (player == 'A') ? 'B' : 'A'; // switch 
                }
            }
            else
            {
                moves(player, &row1, &col1, &row2, &col2);
                bool extraTurn = checkAndMarkBox(player);
                countScoresParallel(&scoreA, &scoreB);
                printf("\nScore Update:\n");
                printf("Player A score: %d\n", scoreA);
                printf("Player B score: %d\n", scoreB);
                if (extraTurn && !gameEnd())
                {
                    printf("\nExtra move for %c!\n", player);
                    printGrid();
                }
                else if (!gameEnd())
                {
                    player = (player == 'A') ? 'B' : 'A';
                }
            }
        }
    }
    finalizeBoard();

    printf("\nFinal board:\n");
    printGrid();
    countScoresParallel(&scoreA, &scoreB);
    printf("\nGame Over!\nPlayer A score: %d, Player B score: %d\n", scoreA, scoreB);
    printf("Winner: %s\n", (scoreA > scoreB) ? "Player A" : (scoreB > scoreA) ? (againstBot ? "Bot" : "Player B")
                                                                              : "It's a tie!");
    return 0;
}
