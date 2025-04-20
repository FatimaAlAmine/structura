
#include "header.h"

// Requires: A valid GameState pointer with properly sized arrays. Global arrays horizontal, vertical, and box must be initialized.
// Effect: Copies the current game board (global arrays) into the state object for safe use without affecting the real game.
void copyRealToState(GameState *state)
{
    for (int i = 0; i <= ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            state->horizontal[i][j] = horizontal[i][j];
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j <= COLS; j++)
        {
            state->vertical[i][j] = vertical[i][j];
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            state->box[i][j] = box[i][j];
        }
    }
}

// Requires: Two valid GameState pointers. src holds the original game state; dest must have space to copy it.
// Effect: Copies all data from src to dest, making an exact duplicate. Useful for simulations or undoing moves safely.
void copyState(GameState *dest, GameState *src)
{
    for (int i = 0; i <= ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            dest->horizontal[i][j] = src->horizontal[i][j];
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j <= COLS; j++)
        {
            dest->vertical[i][j] = src->vertical[i][j];
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            dest->box[i][j] = src->box[i][j];
        }
    }
}

// Requires: A valid GameState pointer and four integers representing move coordinates.
// Effect: Returns true if the move is legal (within bounds, horizontal/vertical, and unoccupied), false otherwise.
bool isValidMoveState(GameState *state, int row1, int col1, int row2, int col2)
{
    if (row1 == row2)
    {
        int min_col = (col1 < col2) ? col1 : col2;
        if (row1 < 0 || row1 > ROWS || min_col < 0 || min_col >= COLS)
            return false;
        return state->horizontal[row1][min_col] == ' ';
    }
    else if (col1 == col2)
    {
        int min_row = (row1 < row2) ? row1 : row2;
        if (col1 < 0 || col1 > COLS || min_row < 0 || min_row >= ROWS)
            return false;
        return state->vertical[min_row][col1] == ' ';
    }
    return false;
}

// Requires: A valid GameState pointer, a Move with start/end coordinates, a player character, and a bool pointer.
// Effect: Applies the move to the state, updates the board, and sets boxCompleted to true if a box is completed.
void applyMoveState(GameState *state, Move mv, char player, bool *boxCompleted)
{
    *boxCompleted = false;
    if (mv.row1 == mv.row2)
    { // horizontal move
        int min_col = (mv.col1 < mv.col2) ? mv.col1 : mv.col2;
        state->horizontal[mv.row1][min_col] = '-';
    }
    else
    { // vertical move
        int min_row = (mv.row1 < mv.row2) ? mv.row1 : mv.row2;
        state->vertical[min_row][mv.col1] = '|';
    }
    // Check boxes affected by the move.
    if (mv.row1 == mv.row2)
    {
        int r = mv.row1;
        int c = (mv.col1 < mv.col2) ? mv.col1 : mv.col2;
        if (r > 0)
        {
            int filled = 0;
            if (state->horizontal[r - 1][c] == '-')
                filled++;
            if (state->horizontal[r][c] == '-')
                filled++;
            if (state->vertical[r - 1][c] == '|')
                filled++;
            if (state->vertical[r - 1][c + 1] == '|')
                filled++;
            if (filled == 4 && state->box[r - 1][c] == ' ')
            {
                state->box[r - 1][c] = player;
                *boxCompleted = true;
            }
        }
        if (r < ROWS)
        {
            int filled = 0;
            if (state->horizontal[r][c] == '-')
                filled++;
            if (state->horizontal[r + 1][c] == '-')
                filled++;
            if (state->vertical[r][c] == '|')
                filled++;
            if (state->vertical[r][c + 1] == '|')
                filled++;
            if (filled == 4 && state->box[r][c] == ' ')
            {
                state->box[r][c] = player;
                *boxCompleted = true;
            }
        }
    }
    if (mv.col1 == mv.col2)
    {
        int c = mv.col1;
        int r = (mv.row1 < mv.row2) ? mv.row1 : mv.row2;
        if (c > 0)
        {
            int filled = 0;
            if (state->vertical[r][c - 1] == '|')
                filled++;
            if (state->vertical[r][c] == '|')
                filled++;
            if (state->horizontal[r][c - 1] == '-')
                filled++;
            if (state->horizontal[r + 1][c - 1] == '-')
                filled++;
            if (filled == 4 && state->box[r][c - 1] == ' ')
            {
                state->box[r][c - 1] = player;
                *boxCompleted = true;
            }
        }
        if (c < COLS)
        {
            int filled = 0;
            if (state->vertical[r][c] == '|')
                filled++;
            if (state->vertical[r][c + 1] == '|')
                filled++;
            if (state->horizontal[r][c] == '-')
                filled++;
            if (state->horizontal[r + 1][c] == '-')
                filled++;
            if (filled == 4 && state->box[r][c] == ' ')
            {
                state->box[r][c] = player;
                *boxCompleted = true;
            }
        }
    }
}

// Requires: A valid GameState pointer with a populated box array containing 'A', 'B', or ' '.
// Effect: Returns the difference in score between bot and player by counting claimed boxes.
int evaluateState(GameState *state)
{
    int scoreBot = 0, scorePlayer = 0;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
        {
            if (state->box[i][j] == 'B')
                scoreBot++;
            else if (state->box[i][j] == 'A')
                scorePlayer++;
        }
    return scoreBot - scorePlayer;
}

// Requires: A valid GameState pointer with a populated box array containing 'A', 'B', or ' '.
// Effect: Returns true if all boxes are claimed, false if there are still unclaimed boxes.
bool gameEndState(GameState *state)
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (state->box[i][j] == ' ')
                return false;
    return true;
}

// Requires: A valid GameState pointer with populated horizontal and vertical arrays representing move locations. The moves array must be large enough to hold up to maxMoves.
// Effect: Iterates through the horizontal and vertical lines, finding empty spaces for valid moves and populating the moves array. Returns the number of available moves, stopping when maxMoves is reached.
int getAvailableMoves(GameState *state, Move moves[], int maxMoves)
{
    int count = 0;
    for (int i = 0; i <= ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (state->horizontal[i][j] == ' ' && count < maxMoves)
            {
                moves[count].row1 = i;
                moves[count].col1 = j;
                moves[count].row2 = i;
                moves[count].col2 = j + 1;
                count++;
            }
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j <= COLS; j++)
        {
            if (state->vertical[i][j] == ' ' && count < maxMoves)
            {
                moves[count].row1 = i;
                moves[count].col1 = j;
                moves[count].row2 = i + 1;
                moves[count].col2 = j;
                count++;
            }
        }
    }
    return count;
}

// Shuffle an array of Move structs using Fisher–Yates shuffle.
// Requires: An array of Move structures (moves[]) and an integer count, representing the number of moves to shuffle. Count should be positive and not exceed the array size.
// Effect: Randomly shuffles the moves array using the Fisher-Yates algorithm, modifying the array to have moves in a random order.
void shuffleMoves(Move moves[], int count)
{
    for (int i = count - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Move temp = moves[i];
        moves[i] = moves[j];
        moves[j] = temp;
    }
}

// Minimax with alpha–beta pruning. If depth == 0 or terminal, return evaluation value.
// Requires: A GameState pointer (state), an integer depth for the search tree, a boolean isMaximizing for determining whose turn it is (true for bot, false for player), and integers alpha and beta for alpha-beta pruning. The depth must be a positive integer, and the state must be a valid pointer.
// Effect: Performs the minimax algorithm with alpha-beta pruning to evaluate the best possible move for the current player. It recursively explores the game tree up to the given depth, maximizing the bot's score and minimizing the player's score.
int minimax(GameState *state, int depth, bool isMaximizing, int alpha, int beta)
{
    if (depth == 0 || gameEndState(state))
        return evaluateState(state);

    Move movesList[100];
    int numMoves = getAvailableMoves(state, movesList, 100);

    if (isMaximizing)
    {
        int maxEval = -INF;
        for (int i = 0; i < numMoves; i++)
        {
            GameState newState;
            copyState(&newState, state);
            bool completed;
            applyMoveState(&newState, movesList[i], 'B', &completed);
            int eval;
            if (completed)
                eval = minimax(&newState, depth - 1, true, alpha, beta);
            else
                eval = minimax(&newState, depth - 1, false, alpha, beta);
            if (eval > maxEval)
                maxEval = eval;
            if (maxEval > alpha)
                alpha = maxEval;
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else
    {
        int minEval = INF;
        for (int i = 0; i < numMoves; i++)
        {
            GameState newState;
            copyState(&newState, state);
            bool completed;
            applyMoveState(&newState, movesList[i], 'A', &completed);
            int eval;
            if (completed)
                eval = minimax(&newState, depth - 1, false, alpha, beta);
            else
                eval = minimax(&newState, depth - 1, true, alpha, beta);
            if (eval < minEval)
                minEval = eval;
            if (minEval < beta)
                beta = minEval;
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

// Requires: An integer depth representing the search tree depth for the minimax algorithm. The current game state must be valid, and available moves must be determined by the getAvailableMoves function. The minimax function must be available for move evaluation, and shuffleMoves is used for randomizing move order.
// Effect: Finds the best move for the maximizing player (the bot) by applying the minimax algorithm with alpha-beta pruning. It copies the current game state, retrieves all available moves, randomizes their order, and evaluates each move using minimax. The move with the highest evaluation value is returned as the best move, which maximizes the bot's score.
Move findBestMove(int depth)
{
    GameState currentState;
    copyRealToState(&currentState);

    Move movesList[100];
    int numMoves = getAvailableMoves(&currentState, movesList, 100);

    // Randomize the order of available moves for unpredictability.
    shuffleMoves(movesList, numMoves);

    Move bestMove = movesList[0];
    int bestValue = -INF;
    for (int i = 0; i < numMoves; i++)
    {
        GameState newState;
        copyState(&newState, &currentState);
        bool completed;
        applyMoveState(&newState, movesList[i], 'B', &completed);
        int moveValue;
        if (completed)
            moveValue = minimax(&newState, depth - 1, true, -INF, INF);
        else
            moveValue = minimax(&newState, depth - 1, false, -INF, INF);
        if (moveValue > bestValue)
        {
            bestValue = moveValue;
            bestMove = movesList[i];
        }
    }
    return bestMove;
}

// Requires: No parameters. The function relies on the findBestMove function to determine the best move for the bot based on the current game state. It assumes a valid game state with initialized horizontal and vertical arrays. The bot is represented by 'B' and moves by the Move structure.
// Effect: Computes the best move for the bot using findBestMove with a depth of 4. The game state is updated based on the best move (horizontal or vertical), and the bot's move is printed in the format: "Bot made move: row1 col1 row2 col2". The function modifies the game state and performs the bot's move.
void hardBotMove()
{
    int searchDepth = 4; // Adjust the search depth as needed.
    Move best = findBestMove(searchDepth);
    if (best.row1 == best.row2)
    { // Horizontal move
        horizontal[best.row1][(best.col1 < best.col2 ? best.col1 : best.col2)] = '-';
    }
    else
    { // Vertical move
        vertical[(best.row1 < best.row2 ? best.row1 : best.row2)][best.col1] = '|';
    }
    printf("Bot made move: %d %d %d %d\n", best.row1, best.col1, best.row2, best.col2);
}
