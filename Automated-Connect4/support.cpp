
#include "support.h"
// get opponenet color
int opp(int color) {
    if (color == BLACK)
        return RED;
    else
        return BLACK;
    
}

// get checker at a specific position (return VACANT if out of bounds)
int getCheckerAt(const Scaffold& board, int totalCols, int totalLevels, int col, int row) {
    if (col < 1 || col > totalCols || row < 1 || row > totalLevels)
        return VACANT;
    return board.checkerAt(col, row);
}

//  see if game is terminated (win or a tie)
bool isDone(const Scaffold& board, int N, int& winner) {
    int numCols = board.cols();    // number of columns
    int numRows = board.levels();  // number of rows

    // directions right (1,0), up (0,1), up-right (1,1), down-right (1,-1)
    const int dCol[4] = {1, 0, 1, 1};  // column step
    const int dRow[4] = {0, 1, 1, -1}; // row step

    // Go through all cells in board
    for (int col = 1; col <= numCols; col++) {
        for (int row = 1; row <= numRows; row++) {
            int startColor = getCheckerAt(board, numCols, numRows, col, row);
            if (startColor == VACANT)
                continue;  // Skip the empty cells

            // Check in each of the four directions
            for (int dir = 0; dir < 4; dir++) {
                int matchCount = 1;
                for (int step = 1; step < N; step++) {
                    int newCol = col + dCol[dir] * step;
                    int newRow = row + dRow[dir] * step;
                    if (getCheckerAt(board, numCols, numRows, newCol, newRow) == startColor)
                        matchCount++;
                    else
                        break;
                }
                if (matchCount == N) {
                    winner = startColor;
                    return true;  // Game over with a win
                }
            }
        }
    }

    // If all spaces are filled and no winner, it's a tie
    if (board.numberEmpty() == 0) {
        winner = TIE_GAME;
        return true;
    }

    return false;  // Game is not over yet
}


