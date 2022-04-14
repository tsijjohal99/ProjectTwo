#include "knight.h"
#include "pieceColourType.h"
#include <cmath>

Knight::Knight(int square[2], PieceColourType colour) : ChessPiece(square, colour) {
    symbol = 'N';
}

std::list<std::string> Knight::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid) {
    std::list<std::string> whereMove;
    for (int i = -2; i < 3; i++) {
        for (int j = -2; j < 3; j++) {
            int look[] = {location[0] + i, location[1] + j};
            if (pow(i,2) + pow(j,2) == 5 && look[0] >= 0 && look[1] >= 0) {
                if (Knight::spaceEmpty(grid, look)) {
                    whereMove.push_back(constructMoveEmpty(look, grid));
                } else if (Knight::spaceEnemy(grid, look)) {
                    whereMove.push_back(constructMoveEmpty(look, grid));
                }
            }
        }
    }
    return whereMove;
}