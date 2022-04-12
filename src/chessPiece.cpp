#include "chessPiece.h"
#include "pieceColourType.h"
#include <iostream>
#include <vector>

ChessPiece::ChessPiece(int square[2], PieceColourType colour) {
    location[0] = square[0];
    location[1] = square[1];
    pieceColour == colour;
    symbol = ' ';
}

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

PieceColourType ChessPiece::getPieceColour() {
    return pieceColour;
}

void ChessPiece::move(int square[2], std::vector<std::vector<ChessPiece*>> &grid) {
    std::vector<std::vector<bool>> wherePossible = ChessPiece::possibleMoves(grid);
    bool canMove = false;
    for (int i = 0; i < grid[0].size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (wherePossible[square[0]][square[1]]) {
                canMove = true;
            }
        }
    }
    grid[square[0]][square[1]] = grid[location[0]][location[1]];
    //grid[location[0]][location[1]] = new ChessPiece::ChessPiece();
}

bool ChessPiece::spaceEmpty(std::vector<std::vector<ChessPiece*>> &grid, int look[]) {
    return (grid[look[0]][look[1]]->getSymbol() == ' ');
}

bool ChessPiece::spaceEnemy(std::vector<std::vector<ChessPiece*>> &grid, int look[]) {
    int s = int(grid[look[0]][look[1]]->getSymbol());
    if (pieceColour == PieceColourType::WHITE) {
        return (s <= int('z') && s >= int('a'));
    } else {
        return (s <= int('Z') && s >= int('A'));
    }
}