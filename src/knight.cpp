#include "knight.h"
#include "pieceColourType.h"
#include <cmath>
#include <string>
#include <iostream>

Knight::Knight(int square[2], PieceColourType colour) : ChessPiece(square, colour) {
    symbol = 'N';
}

std::list<std::string> Knight::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid, bool second) {
    std::list<std::string> whereMove;
    for (int i = -2; i < 3; i++) {
        for (int j = -2; j < 3; j++) {
            int look[] = {location[0] + i, location[1] + j};
            if (pow(i,2) + pow(j,2) == 5 
            && look[0] >= 0 && look[1] >= 0
            && look[0] < 8 && look[1] < 8) {
                if (Knight::spaceEmpty(grid, look)) {
                    whereMove.push_back(constructMove(look, grid, false, second));
                } else if (Knight::spaceEnemy(grid, look)) {
                    whereMove.push_back(constructMove(look, grid, true, second));
                }
            }
        }
    }
    return whereMove;
}

std::string Knight::constructMove(int look[], std::vector<std::vector<ChessPiece*>> &grid, bool enemy, bool second) {
    std::string theMove = "";
    bool secondPiece = false;
    theMove += symbol;
    for (int i = -2; !secondPiece && i < 3; i++) {
        for (int j = -2; !secondPiece && j < 3; j++) {
            if (pow(i,2) + pow(j,2) == 5 && look[0] + i>= 0 && look[1] + j >= 0
            && look[0] + i < 8 && look[1] + j < 8
            && grid[look[0] + i][look[1] + j]->getPieceColour() == pieceColour
            && grid[look[0] + i][look[1] + j]->getSymbol() == symbol
            && look[0] + i != location[0]
            && look[1] + j != location[1]) {
                if (location[0] == look[0] + i) {
                    theMove += char('1' + location[1]);
                } else {
                    theMove += char('a' + location[0]);
                }
                secondPiece = true;
            }
        }
    }
    if (enemy) {
        theMove += 'x';
    }
    theMove += char('a' + look[0]);
    theMove += char('1' + look[1]);
    if (!second) {
        int tempLocation[] = {location[0], location[1]};
        location[0] = look[0];
        location[1] = look[1];
        std::list<std::string> checkForCheck = possibleMoves(grid, true);
        for (std::string move : checkForCheck) {
            int square[] = {int(move[move.size() - 2] - 'a'), int(move[move.size() - 1] - '1')};
            if (grid[square[0]][square[1]]->getSymbol() == 'K' && grid[square[0]][square[1]]->getPieceColour() != pieceColour) {
                theMove += '+';
            }
        }
        location[0] = tempLocation[0];
        location[1] = tempLocation[1];
    }
    return theMove;
}