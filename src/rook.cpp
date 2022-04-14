#include "rook.h"
#include "pieceColourType.h"
#include <string>

Rook::Rook(int square[2], PieceColourType colour) : Queen(square, colour) {
    symbol = 'R';
}

bool Rook::constructRookVertical(int look[], std::vector<std::vector<ChessPiece*>> &grid, std::string &theMove, bool foundSecond, int i, bool enemy) {
    if (grid[look[0]][i]->getPieceColour() == pieceColour 
    && grid[look[0]][i]->getSymbol() == symbol) {
        theMove += symbol;
        theMove += char('1' + location[1]);
        if (enemy) {
            theMove += 'x';
        }
        theMove += char('a' + look[0]);
        theMove += char('1' + look[1]); 
        foundSecond = true;
    } else if (grid[look[0]][i]->spaceEnemy(grid, look)) {
        for (int j = look[0] + 1; look[0] <= 7; j++) {
            if (grid[look[j]][1]->getPieceColour() == pieceColour 
            && grid[look[j]][1]->getSymbol() == symbol) {
                theMove += symbol;
                theMove += char('a' + location[0]);
                if (enemy) {
                    theMove += 'x';
                }
                theMove += char('a' + look[0]);
                theMove += char('1' + look[1]); 
                foundSecond = true;
                break;
            } else if (grid[look[j]][i]->spaceEnemy(grid, look)) {
                break;
            }
        }
        for (int j = look[0] - 1; j >= 0; j--) {
            if (grid[look[j]][1]->getPieceColour() == pieceColour 
            && grid[look[j]][1]->getSymbol() == symbol) {
                theMove += symbol;
                theMove += char('a' + location[0]);
                if (enemy) {
                    theMove += 'x';
                }
                theMove += char('a' + look[0]);
                theMove += char('1' + look[1]); 
                foundSecond = true;
                break;
            } else if (grid[look[j]][i]->spaceEnemy(grid, look)) {
                break;
            }
        } 
    }
    return foundSecond;
}

bool Rook::constructRookHorizontal(int look[], std::vector<std::vector<ChessPiece*>> &grid, std::string &theMove, bool foundSecond, int i, bool enemy) {
    if (grid[i][look[1]]->getPieceColour() == pieceColour 
    && grid[i][look[1]]->getSymbol() == symbol) {
        theMove += symbol;
        theMove += char('a' + location[0]);
        if (enemy) {
            theMove += 'x';
        }
        theMove += char('a' + look[0]);
        theMove += char('1' + look[1]); 
        foundSecond = true;
    } else if (grid[i][look[1]]->spaceEnemy(grid, look)) {
        for (int j = look[1] + 1; look[1] <= 7; j++) {
            if (grid[look[0]][j]->getPieceColour() == pieceColour 
            && grid[look[0]][j]->getSymbol() == symbol) {
                theMove += symbol;
                theMove += char('1' + location[1]);
                if (enemy) {
                    theMove += 'x';
                }
                theMove += char('a' + look[0]);
                theMove += char('1' + look[1]); 
                foundSecond = true;
                break;
            } else if (grid[i][j]->spaceEnemy(grid, look)) {
                break;
            }
        }
        for (int j = look[1] - 1; j >= 0; j--) {
            if (grid[look[0]][j]->getPieceColour() == pieceColour 
            && grid[look[0]][j]->getSymbol() == symbol) {
                theMove += symbol;
                theMove += char('1' + location[1]);
                if (enemy) {
                    theMove += 'x';
                }
                theMove += char('a' + look[0]);
                theMove += char('1' + look[1]); 
                foundSecond = true;
                break;
            } else if (grid[i][j]->spaceEnemy(grid, look)) {
                break;
            }
        } 
    }
    return foundSecond;
}

std::string Rook::constructMoveEmpty(int look[], std::vector<std::vector<ChessPiece*>> &grid) {
    std::string theMove = "";
    bool foundSecond = false;
    if (look[0] == location[0]) {
        if (look[1] < location[1] ) {
            for (int i = look[1] - 1; !foundSecond, i >= 0; i--) {
                foundSecond = constructRookVertical(look, grid, theMove, foundSecond, i, false);
            }
        } else if (look[1] > location[1]) {
            for (int i = look[1] + 1; !foundSecond, i <= 7; i++) {
                foundSecond = constructRookVertical(look, grid, theMove, foundSecond, i, false);
            }
        }
    } else {
        if (look[0] < location[0] ) {
            for (int i = look[0] - 1; !foundSecond, i >= 0; i--) {
                foundSecond = constructRookHorizontal(look, grid, theMove, foundSecond, i, false);
            }
        } else if (look[0] > location[0]) {
            for (int i = look[0] + 1; !foundSecond, i <= 7; i++) {
                foundSecond = constructRookHorizontal(look, grid, theMove, foundSecond, i, false);
            }
        }
    }
    if (!foundSecond) {
        theMove += symbol;
        theMove += char('a' + look[0]);
        theMove += char('1' + look[1]);   
    }

    return theMove;
}

std::string Rook::constructMoveEnemy(int look[], std::vector<std::vector<ChessPiece*>> &grid) {
    std::string theMove = "";
    bool foundSecond = false;
    if (look[0] == location[0]) {
        if (look[1] < location[1] ) {
            for (int i = look[1] - 1; !foundSecond, i >= 0; i--) {
                foundSecond = constructRookVertical(look, grid, theMove, foundSecond, i, true);
            }
        } else if (look[1] > location[1]) {
            for (int i = look[1] + 1; !foundSecond, i <= 7; i++) {
                foundSecond = constructRookVertical(look, grid, theMove, foundSecond, i, true);
            }
        }
    } else {
        if (look[0] < location[0] ) {
            for (int i = look[0] - 1; !foundSecond, i >= 0; i--) {
                foundSecond = constructRookHorizontal(look, grid, theMove, foundSecond, i, true);
            }
        } else if (look[0] > location[0]) {
            for (int i = look[0] + 1; !foundSecond, i <= 7; i++) {
                foundSecond = constructRookHorizontal(look, grid, theMove, foundSecond, i, true);
            }
        }
    }
    if (!foundSecond) {
        theMove += symbol;
        theMove += 'x';
        theMove += char('a' + look[0]);
        theMove += char('1' + look[1]);  
    }

    return theMove;
}