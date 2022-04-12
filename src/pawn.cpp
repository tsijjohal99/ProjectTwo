
#include "pawn.h"
#include "pieceColourType.h"

Pawn::Pawn(int square[2], PieceColourType colour) : ChessPiece(square, colour) {
    symbol = (pieceColour == PieceColourType::WHITE) ? 'P' : 'p';
}

std::vector<std::vector<bool>> Pawn::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid) {
    std::vector<std::vector<bool>> whereMove(grid[0].size(), std::vector<bool>(grid.size(), false));
    int start, end, neg;
    if (getPieceColour() == PieceColourType::WHITE) {
        start = 1;
        end = 7;
        neg = 1;
    } else {
        start = 6;
        end = 0;
        neg = -1;
    }
    int look[2];
    int lookLeft[2];
    int lookRight[2];
    if (getLocation()[1] != end) {
        look[0] = getLocation()[0];
        look[1] = getLocation()[1] + neg*1;
        if (getLocation()[0] > 0) {
            lookLeft[0] = look[0] - 1;
            lookLeft[1] = look[1];
        }
        if (getLocation()[1] < 7) {
            lookRight[0] = look[0] + 1;
            lookRight[1] = look[1];
        } 
    }

    if (spaceEmpty(grid, look)) {
        whereMove[look[0]][look[1]] = true;
        look[1] += neg*1;
        if (getLocation()[1] == start || spaceEmpty(grid, look)) {
            whereMove[look[0]][look[1]] = true;
        }
    }
    if (spaceEnemy(grid, lookLeft)) {
        whereMove[lookLeft[0]][lookLeft[1]] = true;
    }
    if (spaceEnemy(grid, lookRight)) {
        whereMove[lookRight[0]][lookRight[1]] = true;
    }
    
    return whereMove;
}