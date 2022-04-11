#include "queen.h"
#include <vector>
#include <iostream>

Queen::ChessPiece::ChessPiece(int square[2], bool colour) {
    location[0] = square[0];
    location[1] = square[1];
    white = colour;
    symbol = (white) ? 'Q' : 'q';
}

bool Queen::getMovementStraight() {
    return movementStraight;
}

bool Queen::getMovementDiag() {
    return movementDiag;
}

std::vector<std::vector<bool>> Queen::possibleMoves(std::vector<std::vector<char>> grid) {
    int square[2] = {Queen::getLocation()[0], Queen::getLocation()[1]};
    std::vector<std::vector<bool>> whereMove(grid[0].size(), std::vector<bool>(grid.size(), false));
    if (movementStraight) {
        for (int i = 1; i < maxMovement; i++) {
            int look[] = {square[0] + i, square[1]};
            if (ChessPiece::spaceEmpty(grid, look) && look[0] < 7) {
                whereMove[look[0]][look[1]] = true;
            } else if (ChessPiece::spaceEnemy(grid, look) || look[0] == 7) {
                whereMove[look[0]][look[1]] = true;
                for (int k = 0; k < i; k++) {
                    look[0] = square[0] - k;
                    if (ChessPiece::spaceEmpty(grid, look) && look[0] > 0) {
                        whereMove[look[0]][look[1]] = true;
                    } else if (ChessPiece::spaceEnemy(grid, look) || look[0] == 0) {
                        whereMove[look[0]][look[1]] = true;
                        break;
                    }
                }
                break;
            }
        }
        for (int j = 1; j < maxMovement; j++) {
            int look[] = {square[0], square[1] + j};
            if (ChessPiece::spaceEmpty(grid, look) && look[1] < 7) {
                whereMove[look[0]][look[1]] = true;
            } else if (ChessPiece::spaceEnemy(grid, look) || look[1] == 7) {
                whereMove[look[0]][look[1]] = true;
                for (int l = 0; l < j; l++) {
                    look[1] = square[1] - l;
                    if (ChessPiece::spaceEmpty(grid, look) && look[1] > 0) {
                        whereMove[look[0]][look[1]] = true;
                    } else if (ChessPiece::spaceEnemy(grid, look) || look[1] == 0) {
                        whereMove[look[0]][look[1]] = true;
                        break;
                    }
                }
                break;
            }
        }
    }
    if (movementDiag) {
        for (int i = 1; i < maxMovement; i++) {
            int look[] = {square[0] + i, square[1] + i};
            if (ChessPiece::spaceEmpty(grid, look) && look[0] < 7 && look[1] < 7) {
                whereMove[look[0]][look[1]] = true;
            } else if (ChessPiece::spaceEnemy(grid, look) || look[0] == 7 || look[1] ==7) {
                whereMove[look[0]][look[1]] = true;
                for (int k = 0; k < i; k++) {
                    look[0] = square[0] - k;
                    look[1] = square[1] - k;
                    if (ChessPiece::spaceEmpty(grid, look) && look[0] > 0 && look[1] > 0) {
                        whereMove[look[0]][look[1]] = true;
                    } else if (ChessPiece::spaceEnemy(grid, look) || look[0] == 0 || look[1] == 0) {
                        whereMove[look[0]][look[1]] = true;
                        break;
                    }
                }
                break;
            }
        }
        for (int j = 1; j < maxMovement; j++) {
            int look[] = {square[0] + j, square[1] - j};
            if (ChessPiece::spaceEmpty(grid, look) && look[0] < 7 && look[1] > 0) {
                whereMove[look[0]][look[1]] = true;
            } else if (ChessPiece::spaceEnemy(grid, look) || look[0] == 7 || look[1] == 0) {
                whereMove[look[0]][look[1]] = true;
                for (int l = 0; l < j; l++) {
                    look[0] = square[0] - l;
                    look[1] = square[1] + l;
                    if (ChessPiece::spaceEmpty(grid, look) && look[0] > 0 && look[1] < 7) {
                        whereMove[look[0]][look[1]] = true;
                    } else if (ChessPiece::spaceEnemy(grid, look) || look[0] == 0 || look[1] == 7) {
                        whereMove[look[0]][look[1]] = true;
                        break;
                    }
                }
                break;
            }
        }
    }
    return whereMove;
}