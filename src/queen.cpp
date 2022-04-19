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

std::list<std::string> Queen::slide(std::vector<std::vector<ChessPiece*>> &grid, int direction[]) {
    std::list<std::string> whereMove;
    int look[2] = {location[0], location[1]}; 
    for (int i = 1; location[0] + i*direction[0] < 8 && location[0] + i*direction[0] >= 0 && location[1] + i*direction[1] < 8 && location[1] + i*direction[1] >= 0 && i < maxMovement; i++) {
        look[0] = location[0] + i*direction[0];
        look[1] = location[1] + i*direction[1];
        if (ChessPiece::spaceEmpty(grid, look)) {
            whereMove.push_back(constructMoveEmpty(look, grid));
        } else if (ChessPiece::spaceEnemy(grid, look)) { 
            whereMove.push_back(constructMoveEnemy(look, grid));
            break;
        } else {
            break;
        }
    }
    return whereMove;
}

std::list<std::string> Queen::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid) {
    int square[2] = {Queen::getLocation()[0], Queen::getLocation()[1]};
    std::list<std::string> whereMove;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int direction[] = {i,j};
            if (i != 0 && j != 0) {
                if ((i == -j || i == j) && symbol != 'R') {
                    std::list<std::string> moves = slide(grid, direction);
                    whereMove.insert(whereMove.end(), moves.begin(), moves.end());
                } else if (i != j & symbol != 'B') {
                    std::list<std::string> moves = slide(grid, direction);
                    whereMove.insert(whereMove.end(), moves.begin(), moves.end());
                }
            }
        }
    }

    return whereMove;
}

/*bool constructMoveSlide(int look[], std::vector<std::vector<ChessPiece*>> &grid, bool enemy, bool found second) {

}

std::string Queen::constructMove(int look[], std::vector<std::vector<ChessPiece*>> &grid, bool enemy) {
    std::string theMove = "";
    bool foundSecond = false;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int direction[] = {i,j};
            if (i != 0 && j != 0) {
                if ((i == -j || i == j) && symbol != 'R') {
                    foundSecond = constructMoveSlide(look, grid, enemy);
                } else if (i != j & symbol != 'B') {
                    std::list<std::string> moves = slide(grid, direction);
                    whereMove.insert(whereMove.end(), moves.begin(), moves.end());
                }
            }
        }
    }
}*/

std::string Queen::constructMoveEmpty(int look[], std::vector<std::vector<ChessPiece*>> &grid) {
    std::string theMove = "";
    theMove += symbol;
    theMove += char('a' + look[0]);
    theMove += char('1' + look[1]);
    return theMove;
}

std::string Queen::constructMoveEnemy(int look[], std::vector<std::vector<ChessPiece*>> &grid) {
    std::string theMove = "";
    theMove += symbol;
    theMove += 'x';
    theMove += char('a' + look[0]);
    theMove += char('1' + look[1]);
    return theMove;
}