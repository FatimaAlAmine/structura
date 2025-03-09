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
