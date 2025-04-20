#include "header.h"

// Requires: A pointer to a ScoreArgs structure with startRow, endRow, localScoreA, and localScoreB, and a valid 'box' array.
// Effect: Iterates over the rows in the range from startRow to endRow, counting occurrences of 'A' and 'B' in the 'box' array to update localScoreA and localScoreB, and returns NULL when completed.
void *partialScoreCount(void *arg)
{
    ScoreArgs *args = (ScoreArgs *)arg;
    args->localScoreA = 0;
    args->localScoreB = 0;

    for (int i = args->startRow; i < args->endRow; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (box[i][j] == 'A')
            {
                args->localScoreA++;
            }
            else if (box[i][j] == 'B')
            {
                args->localScoreB++;
            }
        }
    }
    return NULL;
}

// Requires: The 2D arrays horizontal, vertical, and box must be declared with dimensions at least [ROWS + 1][COLS], [ROWS][COLS + 1], and [ROWS][COLS] respectively.
// Effect: Initializes the game board by setting all elements in the horizontal, vertical, and box arrays to the space character ' ', clearing any previous game state.
void emptyBoard()
{
    for (int i = 0; i <= ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            horizontal[i][j] = ' ';
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j <= COLS; j++)
        {
            vertical[i][j] = ' ';
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            box[i][j] = ' ';
        }
    }
}

// Requires: Global arrays horizontal, vertical, and box must be initialized with dimensions [ROWS + 1][COLS], [ROWS][COLS + 1], and [ROWS][COLS], respectively.
// Effect: Displays the current game grid, printing dots (.) for corners, horizontal/vertical lines from the arrays, and box ownership from the box array, with row and column indices.
void printGrid()
{
    printf("   ");
    for (int j = 0; j <= COLS; j++)
    {
        printf("%d   ", j);
    }
    printf("\n");
    for (int i = 0; i < ROWS + 1; i++)
    {
        printf("%d  ", i);
        for (int j = 0; j < COLS; j++)
        {
            printf(". %c ", horizontal[i][j]);
        }
        printf(".\n");
        if (i < ROWS)
        {
            printf("   ");
            for (int j = 0; j < COLS; j++)
            {
                printf("%c %c ", vertical[i][j], box[i][j]);
            }
            printf("%c\n", vertical[i][COLS]);
        }
    }
}

// Requires: Valid pointers to scoreA and scoreB, and a properly initialized 'box' array. The THREAD_COUNT constant and ROWS should be defined.
// Effect: Creates multiple threads to parallelize the counting of 'A' and 'B' scores in the 'box' array by dividing the rows among the threads. Each thread updates local scores, and the main thread aggregates the results into scoreA and scoreB.
void countScoresParallel(int *scoreA, int *scoreB)
{
    pthread_t threads[THREAD_COUNT];
    ScoreArgs args[THREAD_COUNT];
    int rowsPerThread = ROWS / THREAD_COUNT;

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        args[i].startRow = i * rowsPerThread;
        args[i].endRow = (i == THREAD_COUNT - 1) ? ROWS : args[i].startRow + rowsPerThread;
        pthread_create(&threads[i], NULL, partialScoreCount, &args[i]);
    }

    *scoreA = 0;
    *scoreB = 0;

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
        *scoreA += args[i].localScoreA;
        *scoreB += args[i].localScoreB;
    }
}

// Requires: The player parameter ('A' or 'B'), and initialized global 2D arrays horizontal, vertical, and box with proper dimensions [ROWS+1][COLS+1] for horizontal, [ROWS][COLS+1] for vertical, and [ROWS][COLS] for box, initially set to ' '.
// Effect: Checks all boxes in the grid. If a box is completed (surrounded by lines), it marks it with the player's character and sets completedBox to true. If no boxes are completed, the method does nothing.
bool checkAndMarkBox(char player)
{
    bool completedBox = false;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (horizontal[i][j] == '-' && horizontal[i + 1][j] == '-' &&
                vertical[i][j] == '|' && vertical[i][j + 1] == '|' && box[i][j] == ' ')
            {
                box[i][j] = player;
                completedBox = true;
            }
        }
    }
    return completedBox;
}

// Requires: Initialized box array with dimensions [ROWS][COLS], where each element represents the state of a box (' ' for empty, 'A' or 'B' for occupied).
// Effect: Checks if all boxes are filled with 'A' or 'B'. Returns false if any box is empty, indicating the game is not finished; returns true if all boxes are filled, signaling the game has ended.
bool gameEnd()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (box[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Requires: Initialized horizontal and vertical arrays with dimensions [ROWS+1][COLS] and [ROWS][COLS+1], representing the grid state with ' ' (empty) or '-' (horizontal) and '|' (vertical) lines.
// Effect: Validates if the move at (row1, col1) and (row2, col2) forms a valid horizontal or vertical connection and checks if the corresponding line is unoccupied (' ').
bool isValidMove(int row1, int col1, int row2, int col2)
{
    if (row1 == row2)
    { // horizontal line
        int min_col = (col1 < col2) ? col1 : col2;
        return row1 >= 0 && row1 <= ROWS && min_col >= 0 && min_col < COLS && horizontal[row1][min_col] == ' ';
    }
    else if (col1 == col2)
    { // vertical line
        int min_row = (row1 < row2) ? row1 : row2;
        return col1 >= 0 && col1 <= COLS && min_row >= 0 && min_row < ROWS && vertical[min_row][col1] == ' ';
    }
    return false;
}

// Requires: No parameters. The function assumes the game board is represented by a box array, where 'A' and 'B' represent boxes owned by the players. It also assumes the checkAndMarkBox function marks completed boxes. The game state must be correctly initialized with no completed boxes at the start.
// Effect: The function repeatedly calls checkAndMarkBox for both players ('A' and 'B') in a loop until no more boxes can be completed. It tracks whether any box was completed, and the loop terminates when no more boxes can be marked. This function ensures that all possible boxes are completed before the game transitions to the next phase.
void finalizeBoard()
{
    bool change;
    do
    {
        bool changeA = checkAndMarkBox('A');
        bool changeB = checkAndMarkBox('B');
        change = changeA || changeB;
    } while (change);
}

