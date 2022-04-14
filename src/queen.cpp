#include "queen.h"
#include "pieceColourType.h"
#include <vector>
#include <list>
#include <iostream>

Queen::Queen(int square[2], PieceColourType colour) : ChessPiece(square, colour) {
    symbol = 'Q';
}

bool Queen::getMovementStraight() {
    return movementStraight;
}

bool Queen::getMovementDiag() {
    return movementDiag;
}

std::list<std::string> Queen::straight(std::vector<std::vector<ChessPiece*>> &grid, int index) {
    std::list<std::string> whereMove;
    int look[2] = {location[0], location[1]};
    for (int i = 1; location[index] + i < 8 && i < maxMovement; i++) {
        look[index] = location[index] + i;
        if (ChessPiece::spaceEmpty(grid, look) && look[index] < 7) {
            whereMove.push_back(constructMoveEmpty(look, grid));
        } else {
            if (ChessPiece::spaceEnemy(grid, look)) {
                whereMove.push_back(constructMoveEnemy(look, grid));
            }
            for (int k = 0; k < i; k++) {
                look[index] = location[index] - k;
                if (ChessPiece::spaceEmpty(grid, look) && look[index] > 0) {
                    whereMove.push_back(constructMoveEmpty(look, grid));
                } else {
                    if (ChessPiece::spaceEnemy(grid, look)) {
                        whereMove.push_back(constructMoveEnemy(look, grid));
                    }
                    break;
                }     
            }
            break;
        }
    }
    return whereMove;
}

std::list<std::string> Queen::diagonal(std::vector<std::vector<ChessPiece*>> &grid, int neg) {
    std::list<std::string> whereMove;
    int x,y;
    if (neg == 1) {
        x = 7;
        y = 0;
    } else {
        x = 0;
        y = 7;
    }
    int look[2] = {location[0], location[1]};
    for (int i = 1; location[1] + neg*i >= 0 && location[1] + neg*i < 8 && location[0] + i < 8 && i < maxMovement; i++) {
        look[0] = location[0] + i;
        look[1] = location[1] + neg*i;
        if (ChessPiece::spaceEmpty(grid, look) && look[0] < 7 && look[1] != x) {
            whereMove.push_back(constructMoveEmpty(look, grid));
        } else {
            if (ChessPiece::spaceEnemy(grid, look)) {
                whereMove.push_back(constructMoveEnemy(look, grid));
            }
            for (int k = 0; k < i; k++) {
                look[0] = location[0] - k;
                look[1] = location[1] - neg*k;
                if (ChessPiece::spaceEmpty(grid, look) && look[0] > 0 && look[1] != y) {
                    whereMove.push_back(constructMoveEmpty(look, grid));
                } else {
                    if (ChessPiece::spaceEnemy(grid, look)) {
                        whereMove.push_back(constructMoveEnemy(look, grid));
                    }
                    break;
                }
            }
            break;
        }
    }
    return whereMove;
}

std::list<std::string> Queen::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid) {
    int square[2] = {Queen::getLocation()[0], Queen::getLocation()[1]};
    std::list<std::string> whereMove;
    if (symbol != 'B') {
        std::list<std::string> listA = straight(grid, 0);
        whereMove.insert(whereMove.end(), listA.begin(), listA.end());
        std::list<std::string> listB = straight(grid, 1);
        whereMove.insert(whereMove.end(), listB.begin(), listB.end());
    }
    if (symbol != 'R') {
        std::list<std::string> listA = diagonal(grid, 1);
        whereMove.insert(whereMove.end(), listA.begin(), listA.end());
        std::list<std::string> listB = diagonal(grid, -1);
        whereMove.insert(whereMove.end(), listB.begin(), listB.end());
    }
    return whereMove;
}