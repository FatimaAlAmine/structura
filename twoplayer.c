#include <stdio.h>
#include <stdbool.h>

#define ROWS 4
#define COLS 5

// store horizonatal and vertical lines
 char horizontal [ROWS +1][COLS];
 char vertical [ROWS][COLS +1];
 // box of complete a and b
 char box[ROWS][COLS];

// empty grid
void emptyBoard(){
    for(int i=0; i<= ROWS; i++){
        for(int j=0; j<= COLS; j++){
            horizontal[i][j] = ' '; // game did not start nothing
        }
    }
    for (int i=0; i<=ROWS; i++){
        for (int j=0; j<=COLS; j++){
            vertical[i][j] = ' ';
        }
    }
    // we still didn't ask the user for input so nothing yet
    for (int i=0; i<=ROWS; i++){
        for(int j=0; j<= COLS; j++){
            box[i][j] = ' ';
        }
    }
}


void printGrid() {
    
    printf("   ");
    printf("0   1   2   3   4   5");
    printf("\n");
    
    
   for (int i = 0; i < ROWS + 1; i++) {
        printf(" %d ", i); // prints each number for rows
        for (int j = 0; j < COLS; j++) {
            printf(". %c ", horizontal[i][j]);
        }
        printf(".\n"); // last dot
       
        if (i < ROWS) {
            printf("   ");
            for (int j = 0; j < COLS; j++) {
                printf("%c %c ", vertical[i][j], box[i][j]);
            }
            printf("%c\n", vertical[i][COLS]);
        }
    }
}

void moves(char player)
{
    // to connect a line we need 2 dots
    // row1 column1 dot row2 column2 second (4,0) (4,1)
    int row1;
    int row2;
    int column1;
    int column2;
    printf("%c's turn. Enter the row and the column of the first dot (e.g., A0 -> 0 0) and the second dot: ", player);
    scanf("%d %d %d %d", &row1, &column1, &row2, &column2);
    // this takes the input from the user

    if (row1 == row2 && (column1 + 1 == column2 || column2 + 1 == column1)) {
        int min_col = (column1 < column2) ? column1 : column2;
        if (row1 >= 0 && row1 <= ROWS && min_col >= 0 && min_col < COLS && horizontal[row1][min_col] == ' ') {
            horizontal[row1][min_col] = '-';
        } else {
            printf("Invalid move. Try again.\n");
            moves(player);
        }
    } else if (column1 == column2 && (row1 + 1 == row2 || row2 + 1 == row1)) {
        int min_row = (row1 < row2) ? row1 : row2;
        if (min_row >= 0 && min_row < ROWS && column1 >= 0 && column1 <= COLS && vertical[min_row][column1] == ' ') {
            vertical[min_row][column1] = '|';
        } else {
            printf("Invalid move. Try again.\n");
            moves(player);
        }
    } else {
        printf("Invalid move. Try again.\n");
        moves(player);
    }
}


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


int main() {
    emptyBoard();
    char player = 'A';
    int scoreA = 0, scoreB = 0;

    while (!gameEnd()) {
        printGrid(); //current state of the board
        moves(player); //get the move from the current player
        bool completedBox = checkAndMarkBox(player); //to check and mark boxes after each move

        countScores(&scoreA, &scoreB); //count the scores

        //update scores
        printf("Player A score: %d\n", scoreA);
        printf("Player B score: %d\n", scoreB);

        // Switch turns between Player A and Player B if no box is completed
        if (!completedBox) {
            if (player == 'A') {
                player = 'B';
            } else {
                player = 'A';
            }
        }
    }
    
    printf("Game Over! Player A score: %d, Player B score: %d\n", scoreA, scoreB);
    printf("Winner: %s\n", (scoreA > scoreB) ? "Player A" : (scoreB > scoreA) ? "Player B" : "It's a tie!");

return 0;
}
