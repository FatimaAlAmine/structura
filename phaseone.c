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
    
    
    for (int i = 0; i < ROWS+1; i++) {
        printf(" %d ", i); // prints each number for rows
        for (int j = 0; j < COLS; j++) {
            printf(". %c ", horizontal[i][j]);
            }
            printf(".\n"); // last dot
            
           if (i < ROWS ) {
            printf("    ");
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

int main() {
   
    emptyBoard();
    char player1 ='A';
    char player2 = 'B';
    
    while(true){
        printGrid();
        break;
    }

    return 0;
}
