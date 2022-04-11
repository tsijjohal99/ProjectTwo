#include "chessPiece.h"
#include <iostream>
#include <vector>

void ChessPiece::setLocation(std::string square) {
    location[1] = square[1] - 1;
    location[0] = int(char(square[0])) - int('a');
}

int * ChessPiece::getLocation() {
    return location;
}

char ChessPiece::getSymbol() {
    return symbol;
}

bool ChessPiece::getWhite() {
    return white;
}

void ChessPiece::move(int square[2], std::vector<std::vector<char>> &grid) {
    std::vector<std::vector<bool>> wherePossible = ChessPiece::possibleMoves(grid);
    bool canMove = false;
    for (int i = 0; i < grid[0].size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (wherePossible[square[0]][square[1]]) {
                canMove = true;
            }
        }
    }
    grid[square[0]][square[1]] = symbol;
}

bool ChessPiece::spaceEmpty(std::vector<std::vector<char>> grid, int look[]) {
    return (grid[look[0]][look[1]] == ' ');
}

bool ChessPiece::spaceEnemy(std::vector<std::vector<char>> grid, int look[]) {
    if (white) {
        return (int(grid[look[0]][look[1]]) <= int('z') && int(grid[look[0]][look[1]]) >= int('a'));
    } else {
        return (int(grid[look[0]][look[1]]) <= int('Z') && int(grid[look[0]][look[1]]) >= int('A'));
    }
}