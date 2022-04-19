#include "queen.h"
#include "pieceColourType.h"
#include <vector>
#include <list>
#include <iostream>
#include <string>

Queen::Queen(int square[2], PieceColourType colour) : ChessPiece(square, colour) {
    symbol = 'Q';
    maxMovement = 8;
}

std::list<std::string> Queen::slide(std::vector<std::vector<ChessPiece*>> &grid, int direction[], bool second) {
    std::list<std::string> whereMove;
    int look[2] = {location[0], location[1]}; 
    for (int i = 1; location[0] + i*direction[0] < 8 && location[0] + i*direction[0] >= 0 && location[1] + i*direction[1] < 8 && location[1] + i*direction[1] >= 0 && i < maxMovement; i++) {
        look[0] = location[0] + i*direction[0];
        look[1] = location[1] + i*direction[1];
        if (ChessPiece::spaceEmpty(grid, look)) {
            whereMove.push_back(constructMove(look, grid, false, second));
        } else if (ChessPiece::spaceEnemy(grid, look)) { 
            whereMove.push_back(constructMove(look, grid, true, second));
            break;
        } else {
            break;
        }
    }
    return whereMove;
}

std::list<std::string> Queen::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid, bool second) {
    int square[2] = {Queen::getLocation()[0], Queen::getLocation()[1]};
    std::list<std::string> whereMove;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int direction[] = {i,j};
            if (i != 0 && j != 0) {
                if ((i == -j || i == j) && symbol != 'R') {
                    std::list<std::string> moves = slide(grid, direction, second);
                    whereMove.insert(whereMove.end(), moves.begin(), moves.end());
                } else if (i != j & symbol != 'B') {
                    std::list<std::string> moves = slide(grid, direction, second);
                    whereMove.insert(whereMove.end(), moves.begin(), moves.end());
                }
            }
        }
    }

    return whereMove;
}

bool Queen::constructMoveSlide(std::string &theMove, int look[], std::vector<std::vector<ChessPiece*>> &grid, int direction[]) {
    for (int i = 1; look[0] + i*direction[0] < 8 && look[0] + i*direction[0] >= 0 && look[1] + i*direction[1] < 8 && look[1] + i*direction[1] >= 0 && i < maxMovement; i++) {
        if (grid[look[0] + i*direction[0]][look[1] + i*direction[1]]->getPieceColour() == pieceColour 
        && grid[look[0] + i*direction[0]][look[1] + i*direction[1]]->getSymbol() == symbol
        && (look[0] + i*direction[0] != location[0] && look[1] + i*direction[1] != location[1]) ) {
            if (look[0] == location[0]) {
                theMove += char('a' + location[0]);
            } else {
                theMove += char('1' + location[1]);
            }
            return true;
        }
    }
}

std::string Queen::constructMove(int look[], std::vector<std::vector<ChessPiece*>> &grid, bool enemy, bool second) {
    std::string theMove = "";
    bool foundSecond = false;
    theMove += symbol;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int direction[] = {i,j};
            if (i != 0 && j != 0 && !foundSecond) {
                if ((i == -j || i == j) && symbol != 'R') {
                    foundSecond = constructMoveSlide(theMove, look, grid, direction);
                } else if (i != j & symbol != 'B') {
                    foundSecond = constructMoveSlide(theMove, look, grid, direction);
                }
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