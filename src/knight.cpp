#include "knight.h"
#include "pieceColourType.h"
#include <cmath>
#include <string>
#include <iostream>

Knight::Knight(int square[2], PieceColourType colour) : ChessPiece(square, colour) {
    symbol = 'N';
}

std::list<std::string> Knight::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid) {
    std::list<std::string> whereMove;
    for (int i = -2; i < 3; i++) {
        for (int j = -2; j < 3; j++) {
            int look[] = {location[0] + i, location[1] + j};
            if (pow(i,2) + pow(j,2) == 5 
            && look[0] >= 0 && look[1] >= 0
            && look[0] < 8 && look[1] < 8) {
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

std::string Knight::constructMoveEmpty(int look[], std::vector<std::vector<ChessPiece*>> &grid) {
    std::string theMove = "";
    bool secondPiece = false;
    for (int i = -2; !secondPiece, i < 3; i++) {
        for (int j = -2; !secondPiece, j < 3; j++) {
            if (pow(i,2) + pow(j,2) == 5 && look[0] + i>= 0 && look[1] + j >= 0
            && look[0] + i < 8 && look[1] + j < 8
            && grid[look[0] + i][look[1] + j]->getPieceColour() == pieceColour
            && grid[look[0] + i][look[1] + j]->getSymbol() == symbol
            && look[0] + i != location[0]
            && look[1] + j != location[1]) {
                if (location[0] == look[0] + i) {
                    theMove += symbol;
                    theMove += char('1' + location[1]);
                    theMove += char('a' + look[0]);
                    theMove += char('1' + look[1]);
                } else {
                    theMove += symbol;
                    theMove += char('a' + location[0]);
                    theMove += char('a' + look[0]);
                    theMove += char('1' + look[1]);
                }
                secondPiece = true;
            }
        }
    }
    if (!secondPiece) {
        theMove += symbol;
        theMove += char('a' + look[0]);
        theMove += char('1' + look[1]);
    }
    return theMove;
}

std::string Knight::constructMoveEnemy(int look[], std::vector<std::vector<ChessPiece*>> &grid) {
    std::string theMove = "";
    bool secondPiece = false;
    for (int i = -2; !secondPiece, i < 3; i++) {
        for (int j = -2; !secondPiece, j < 3; j++) {
            if (pow(i,2) + pow(j,2) == 5 && look[0] + i>= 0 && look[1] + j >= 0
            && look[0] + i < 8 && look[1] + j < 8
            && grid[look[0] + i][look[1] + j]->getPieceColour() == pieceColour
            && grid[look[0] + i][look[1] + j]->getSymbol() == symbol
            && look[0] + i != location[0]
            && look[1] + j != location[1]) {
                if (location[0] == look[0] + i) {
                    theMove += symbol;
                    theMove += char('1' + location[1]);
                    theMove += 'x';
                    theMove += char('a' + look[0]);
                    theMove += char('1' + look[1]);
                } else {
                    theMove += symbol;
                    theMove += char('a' + location[0]);
                    theMove += 'x';
                    theMove += char('a' + look[0]);
                    theMove += char('1' + look[1]);
                }
                secondPiece = true;
            }
        }
    }
    if (!secondPiece) {
        theMove += symbol;
        theMove += 'x';
        theMove += char('a' + look[0]);
        theMove += char('1' + look[1]);
    }
    return theMove;
}