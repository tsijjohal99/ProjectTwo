#include "queen.h"
#include "pieceColourType.h"
#include <vector>
#include <iostream>

Queen::Queen(int square[2], PieceColourType colour) : ChessPiece(square, colour) {
    symbol = (pieceColour == PieceColourType::WHITE) ? 'Q' : 'q';
}

bool Queen::getMovementStraight() {
    return movementStraight;
}

bool Queen::getMovementDiag() {
    return movementDiag;
}

void Queen::straight(std::vector<std::vector<bool>> &whereMove, std::vector<std::vector<ChessPiece*>> &grid, int index) {
    for (int i = 1; i < maxMovement; i++) {
        int look[] = {Queen::getLocation()[0] + i, Queen::getLocation()[1]};
        if (ChessPiece::spaceEmpty(grid, look) && look[index] < 7) {
            whereMove[look[0]][look[1]] = true;
        } else if (ChessPiece::spaceEnemy(grid, look) || look[index] == 7) {
            whereMove[look[0]][look[1]] = true;
            for (int k = 0; k < i; k++) {
                look[index] = Queen::getLocation()[index] - k;
                if (ChessPiece::spaceEmpty(grid, look) && look[index] > 0) {
                    whereMove[look[0]][look[1]] = true;
                } else if (ChessPiece::spaceEnemy(grid, look) || look[index] == 0) {
                    whereMove[look[0]][look[1]] = true;
                    break;
                }
            }
            break;
        }
    }
}

void Queen::diagonal(std::vector<std::vector<bool>> &whereMove, std::vector<std::vector<ChessPiece*>> &grid, int neg) {
    int x,y;
    if (neg == 1) {
        x = 7;
        y = 0;
    } else {
        x = 0;
        y = 7;
    }
    for (int i = 1; i < maxMovement; i++) {
        int look[] = {Queen::getLocation()[0] + i, Queen::getLocation()[1] + neg*i};
        if (ChessPiece::spaceEmpty(grid, look) && look[0] < 7 && look[1] != x) {
            whereMove[look[0]][look[1]] = true;
        } else if (ChessPiece::spaceEnemy(grid, look) || look[0] == 7 || look[1] == x) {
            whereMove[look[0]][look[1]] = true;
            for (int k = 0; k < i; k++) {
                look[0] = Queen::getLocation()[0] - k;
                look[1] = Queen::getLocation()[1] - neg*k;
                if (ChessPiece::spaceEmpty(grid, look) && look[0] > 0 && look[1] != y) {
                    whereMove[look[0]][look[1]] = true;
                } else if (ChessPiece::spaceEnemy(grid, look) || look[0] == 0 || look[1] == y) {
                    whereMove[look[0]][look[1]] = true;
                    break;
                }
            }
            break;
        }
    }
}

std::vector<std::vector<bool>> Queen::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid) {
    int square[2] = {Queen::getLocation()[0], Queen::getLocation()[1]};
    std::vector<std::vector<bool>> whereMove(grid[0].size(), std::vector<bool>(grid.size(), false));
    if (movementStraight) {
        straight(whereMove, grid, 0);
        straight(whereMove, grid, 1);
    }
    if (movementDiag) {
        diagonal(whereMove, grid, 1);
        diagonal(whereMove, grid, -1);
    }
    return whereMove;
}