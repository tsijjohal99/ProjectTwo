#include "knight.h"
#include <cmath>

Knight::ChessPiece::ChessPiece(int square[2], bool colour) {
    location[0] = square[0];
    location[1] = square[1];
    white = colour;
    symbol = (white) ? 'N' : 'n';
}

std::vector<std::vector<bool>> Knight::possibleMoves(std::vector<std::vector<char>> grid) {
    std::vector<std::vector<bool>> whereMove(grid[0].size(), std::vector<bool>(grid.size(), false));
    for (int i = -2; i < 3; i++) {
        for (int j = -2; i < 3; j++) {
            if (pow(i,2) + pow(j,2) == 3) {
                int look[] = {Knight::getLocation()[0] + i, Knight::getLocation()[1] + j};
                if (Knight::spaceEmpty(grid, look)) {
                    whereMove[look[0]][look[1]] = true;
                } else if (Knight::spaceEnemy(grid, look)) {
                    whereMove[look[0]][look[1]] = true;
                }
            }
        }
    }
    return whereMove;
}