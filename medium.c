#include "header.h"

// Requires: A valid GameState pointer with grid data and valid indices i, j for a box in the grid.
// Effect: Checks if the box at (i, j) has exactly three completed sides. Returns true if three sides are filled, false otherwise. The state object is not modified.
static bool boxHasThreeSidesState(GameState *state, int i, int j)
{
    int count = 0;
    if (state->horizontal[i][j] == '-')
        count++; // top
    if (state->horizontal[i + 1][j] == '-')
        count++; // bottom
    if (state->vertical[i][j] == '|')
        count++; // left
    if (state->vertical[i][j + 1] == '|')
        count++; // right
    return (count == 3);
}

// Requires: Valid indices i and j for a box, with grid structure containing horizontal and vertical arrays.
// Effect: Checks if the box at (i, j) has three of its four sides drawn (using '-' for horizontal and '|' for vertical lines). Returns true if three sides are present, otherwise false.
bool boxHasThreeSides(int i, int j)
{
    int count = 0;
    if (horizontal[i][j] == '-')
        count++; // top
    if (horizontal[i + 1][j] == '-')
        count++; // bottom
    if (vertical[i][j] == '|')
        count++; // left
    if (vertical[i][j + 1] == '|')
        count++; // right
    return (count == 3);
}

// Requires: Valid indices i and j for a box, with grid structure including horizontal, vertical, and box arrays.
// Effect: Completes one incomplete side of the box at (i, j), drawing it with '-' or '|'. After drawing, marks the box as completed for the bot ('B') and prints the move.
void completeBox(int i, int j)
{
    if (horizontal[i][j] == ' ')
    {
        horizontal[i][j] = '-';
        printf("Bot made move: %d %d %d %d\n", i, j, i, j + 1);
    }
    else if (horizontal[i + 1][j] == ' ')
    {
        horizontal[i + 1][j] = '-';
        printf("Bot made move: %d %d %d %d\n", i + 1, j, i + 1, j + 1);
    }
    else if (vertical[i][j] == ' ')
    {
        vertical[i][j] = '|';
        printf("Bot made move: %d %d %d %d\n", i, j, i + 1, j);
    }
    else if (vertical[i][j + 1] == ' ')
    {
        vertical[i][j + 1] = '|';
        printf("Bot made move: %d %d %d %d\n", i, j + 1, i + 1, j + 1);
    }
    box[i][j] = 'B';
}

// Requires: The box array must be initialized with values ' ', 'A', or 'B'. The function boxHasThreeSides(i, j) must correctly detect boxes with three sides, and completeBox(i, j) must mark the box for the bot.
// Effect: The method scans all boxes. If an unclaimed box with three sides is found, it claims it for the bot, prints "Bot made a move!", and returns true. If none are found, it returns false.
bool greedyCompleteAvailableBox()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (box[i][j] == ' ' && boxHasThreeSides(i, j))
            {
                completeBox(i, j);
                printf("Bot made a move!\n");
                return true;
            }
        }
    }
    return false;
}

// Requires: Indices r1, c1, r2, c2 representing valid move endpoints, a properly initialized GameState, and functions to copy the current state and apply the move.
// Effect: Simulates a move on a temporary state copy. Checks if the move completes three sides of any adjacent boxes. Returns true if a three-sided box is created, false otherwise.
bool createsThreeSidedBox(int r1, int c1, int r2, int c2)
{
    GameState temp;
    Move mv = {r1, c1, r2, c2};
    copyRealToState(&temp); // copy current board into temp
    // apply the move (we don’t care here if it actually completes a box)
    bool completed;
    applyMoveState(&temp, mv, 'B', &completed);

    // check only the boxes adjacent to that edge
    if (r1 == r2)
    {
        int c = (c1 < c2 ? c1 : c2);
        if (r1 > 0 && boxHasThreeSidesState(&temp, r1 - 1, c)) // above
            return true;
        if (r1 < ROWS && boxHasThreeSidesState(&temp, r1, c)) // box below
            return true;
    }
    else
    {
        // vertical line at col = c1, row = min(r1,r2)
        int r = (r1 < r2 ? r1 : r2);
        if (c1 > 0 && boxHasThreeSidesState(&temp, r, c1 - 1)) // box to left
            return true;
        if (c1 < COLS && boxHasThreeSidesState(&temp, r, c1)) // box to right
            return true;
    }
    return false;
}

// Requires: The game state must be initialized using copyRealToState, and getAvailableMoves must be functional to list legal moves. The function depends on createsThreeSidedBox to identify risky moves and assumes that allMoves and safeMoves arrays can store up to 100 moves.
// Effect: The method collects all legal moves and filters out those that create three-sided boxes. If safe moves are found, it returns one at random; otherwise, it randomly returns any legal move, guaranteeing a valid move is selected.
Move pickRandomSafeMove()
{
    GameState current;
    copyRealToState(&current);

    Move allMoves[100];
    int nAll = getAvailableMoves(&current, allMoves, 100);
    Move safeMoves[100];
    int nSafe = 0;
    for (int i = 0; i < nAll; i++)
    {
        if (!createsThreeSidedBox(
                allMoves[i].row1,
                allMoves[i].col1,
                allMoves[i].row2,
                allMoves[i].col2))
        {
            safeMoves[nSafe++] = allMoves[i];
        }
    }

    if (nSafe > 0)
    {
        return safeMoves[rand() % nSafe];
    }
    else
    {
        return allMoves[rand() % nAll]; // no safe moves=> just pick any random legal move
    }
}
