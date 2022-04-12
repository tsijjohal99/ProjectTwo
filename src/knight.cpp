#include "knight.h"
#include "pieceColourType.h"
#include <cmath>

Knight::Knight(int square[2], PieceColourType colour) : ChessPiece(square, colour) {
    symbol = (pieceColour == PieceColourType::WHITE) ? 'N' : 'n';
}

std::vector<std::vector<bool>> Knight::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid) {
    std::vector<std::vector<bool>> whereMove(grid[0].size(), std::vector<bool>(grid.size(), false));
    for (int i = -2; i < 3; i++) {
        for (int j = -2; i < 3; j++) {
            if (pow(i,2) + pow(j,2) == 3) {
                int look[] = {Knight::getLocation()[0] + i, Knight::getLocation()[1] + j};
                if (Knight::spaceEmpty(grid, look) || Knight::spaceEnemy(grid, look)) {
                    whereMove[look[0]][look[1]] = true;
                }
            }
        }
    }
    return whereMove;
}