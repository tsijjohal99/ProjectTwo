#include "chessPiece.h"
#include "pieceColourType.h"
#include <iostream>
#include <vector>
#include <cmath>

ChessPiece::ChessPiece(int square[2], PieceColourType colour) {
    location[0] = square[0];
    location[1] = square[1];
    pieceColour = colour;
    symbol = ' ';
}

void ChessPiece::setLocation(std::string square) {
    location[1] = square[1] - 1;
    location[0] = int(char(square[0])) - int('a');
}

int *ChessPiece::getLocation() {
    return location;
}

char ChessPiece::getSymbol() {
    return symbol;
}

bool ChessPiece::getHasMoved() {
    return hasMoved;
}

bool ChessPiece::getEnPassant() {
    return enPassant;
}

void ChessPiece::setHasMoved(bool has_moved) {
    hasMoved = has_moved;
}

void ChessPiece::setEnPassant(bool en_passant) {
    enPassant = en_passant;
}

PieceColourType ChessPiece::getPieceColour() {
    return pieceColour;
}

std::list<std::string> ChessPiece::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid) {
    std::list<std::string> empty;
    return empty;
}

bool ChessPiece::spaceEmpty(std::vector<std::vector<ChessPiece*>> &grid, int look[]) {
    return (grid[look[0]][look[1]]->getPieceColour() == PieceColourType::UNASSIGNED);
}

bool ChessPiece::spaceEnemy(std::vector<std::vector<ChessPiece*>> &grid, int look[]) {
    int s = int(grid[look[0]][look[1]]->getSymbol());
    if ((pieceColour == PieceColourType::WHITE 
    && grid[look[0]][look[1]]->getPieceColour() == PieceColourType::BLACK)
    || (pieceColour == PieceColourType::BLACK 
    && grid[look[0]][look[1]]->getPieceColour() == PieceColourType::WHITE)) {
        return true;
    } else {
        return false;
    }
}

std::string ChessPiece::constructMoveEmpty(int look[], std::vector<std::vector<ChessPiece*>> &grid) {
    std::string theMove = "";

    if (symbol == 'R') {
        if (look[0] == location[0]) {
            if (look[1] < location[1] ) {
                for (int i = look[1] - 1; i >= 0; i--) {
                    if (grid[look[0]][i]->getPieceColour() == pieceColour 
                    && grid[look[0]][i]->getSymbol() == 'R') {
                        theMove.push_back(symbol + char(location[1] + 1) + char('a' + look[0]) + char(look[1] + 1));
                        break;
                    } else if (grid[look[0]][i]->spaceEmpty(grid, look)) {
                        continue;
                    } else {
                        bool foundSecond = false;
                        for (int j = look[0] + 1;!foundSecond, look[0] <= 7; j++) {
                            if (grid[look[j]][1]->getPieceColour() == pieceColour 
                            && grid[look[j]][1]->getSymbol() == 'R') {
                                theMove.push_back(symbol + char(location[0] + 'a') + char('a' + look[0]) + char(look[1] + 1));
                                foundSecond = true;
                            } else if (grid[look[j]][i]->spaceEmpty(grid, look)) {
                                continue;
                            } else {
                                break;
                            }
                        }
                        for (int j = look[0] - 1;!foundSecond, look[0] >= 0; j--) {
                            if (grid[look[j]][1]->getPieceColour() == pieceColour 
                            && grid[look[j]][1]->getSymbol() == 'R') {
                                theMove.push_back(symbol + char(location[0] + 'a') + char('a' + look[0]) + char(look[1] + 1));
                                foundSecond = true;
                            } else if (grid[look[j]][i]->spaceEmpty(grid, look)) {
                                continue;
                            } else {
                                break;
                            }
                        } 
                        break;
                    }
                }
            } else if (look[1] > location[1]) {
                for (int i = look[1] + 1; i <= 7; i++) {
                    if (grid[look[0]][i]->getPieceColour() == pieceColour 
                    && grid[look[0]][i]->getSymbol() == 'R') {
                        theMove.push_back(symbol + char(location[1] + 1) + char('a' + look[0]) + char(look[1] + 1));
                        break;
                    } else if (grid[look[0]][i]->spaceEmpty(grid, look)) {
                        continue;
                    } else {
                        bool foundSecond = false;
                        for (int j = look[0] + 1;!foundSecond, look[0] <= 7; j++) {
                            if (grid[look[j]][1]->getPieceColour() == pieceColour 
                            && grid[look[j]][1]->getSymbol() == 'R') {
                                theMove.push_back(symbol + char(location[0] + 'a') + char('a' + look[0]) + char(look[1] + 1));
                                foundSecond = true;
                            } else if (grid[look[j]][i]->spaceEmpty(grid, look)) {
                                continue;
                            } else {
                                break;
                            }
                        }
                        for (int j = look[0] - 1;!foundSecond, look[0] >= 0; j--) {
                            if (grid[look[j]][1]->getPieceColour() == pieceColour 
                            && grid[look[j]][1]->getSymbol() == 'R') {
                                theMove.push_back(symbol + char(location[0] + 'a') + char('a' + look[0]) + char(look[1] + 1));
                                foundSecond = true;
                            } else if (grid[look[j]][i]->spaceEmpty(grid, look)) {
                                continue;
                            } else {
                                break;
                            }
                        } 
                        break;
                    }
                }
            }
        } 
    } else if (symbol == 'N') {
        bool secondPiece = false;
        for (int i = -2; !secondPiece, i < 3; i++) {
            for (int j = -2; !secondPiece, i < 3; j++) {
                if (pow(i,2) + pow(j,2) == 3 
                && grid[look[0] + i][look[1] + j]->getSymbol() == 'R'
                && grid[look[0] + i][look[1] + j]->getPieceColour() == pieceColour) {
                    if (location[0] == look[0] + i) {
                        theMove.push_back(symbol + char(location[1] + 1) + char('a' + look[0]) + char(look[1] + 1));
                    } else {
                        theMove.push_back(symbol + char(location[0] + 'a') + char('a' + look[0]) + char(look[1] + 1));
                    }
                    secondPiece = true;
                }
            }
        }
    } else {
        theMove.push_back(symbol + char('a' + look[0]) + char(look[1] + 1));
    }
    return theMove;
}

std::string ChessPiece::constructMoveEnemy(int look[], std::vector<std::vector<ChessPiece*>> &grid) {
    std::string theMove = "";

        if (symbol == 'R') {
        if (look[0] == location[0]) {
            if (look[1] < location[1] ) {
                for (int i = look[1] - 1; i >= 0; i--) {
                    if (grid[look[0]][i]->getPieceColour() == pieceColour 
                    && grid[look[0]][i]->getSymbol() == 'R') {
                        theMove.push_back(symbol + char(location[1] + 1) + 'x' + char('a' + look[0]) + char(look[1] + 1));
                        break;
                    } else if (grid[look[0]][i]->spaceEmpty(grid, look)) {
                        continue;
                    } else {
                        bool foundSecond = false;
                        for (int j = look[0] + 1;!foundSecond, look[0] <= 7; j++) {
                            if (grid[look[j]][1]->getPieceColour() == pieceColour 
                            && grid[look[j]][1]->getSymbol() == 'R') {
                                theMove.push_back(symbol + char(location[0] + 'a') + 'x' + char('a' + look[0]) + char(look[1] + 1));
                                foundSecond = true;
                            } else if (grid[look[j]][i]->spaceEmpty(grid, look)) {
                                continue;
                            } else {
                                break;
                            }
                        }
                        for (int j = look[0] - 1;!foundSecond, look[0] >= 0; j--) {
                            if (grid[look[j]][1]->getPieceColour() == pieceColour 
                            && grid[look[j]][1]->getSymbol() == 'R') {
                                theMove.push_back(symbol + char(location[0] + 'a') + 'x' + char('a' + look[0]) + char(look[1] + 1));
                                foundSecond = true;
                            } else if (grid[look[j]][i]->spaceEmpty(grid, look)) {
                                continue;
                            } else {
                                break;
                            }
                        } 
                        break;
                    }
                }
            } else if (look[1] > location[1]) {
                for (int i = look[1] + 1; i <= 7; i++) {
                    if (grid[look[0]][i]->getPieceColour() == pieceColour 
                    && grid[look[0]][i]->getSymbol() == 'R') {
                        theMove.push_back(symbol + char(location[1] + 1) + 'x' + char('a' + look[0]) + char(look[1] + 1));
                        break;
                    } else if (grid[look[0]][i]->spaceEmpty(grid, look)) {
                        continue;
                    } else {
                        bool foundSecond = false;
                        for (int j = look[0] + 1;!foundSecond, look[0] <= 7; j++) {
                            if (grid[look[j]][1]->getPieceColour() == pieceColour 
                            && grid[look[j]][1]->getSymbol() == 'R') {
                                theMove.push_back(symbol + char(location[0] + 'a') + 'x' + char('a' + look[0]) + char(look[1] + 1));
                                foundSecond = true;
                            } else if (grid[look[j]][i]->spaceEmpty(grid, look)) {
                                continue;
                            } else {
                                break;
                            }
                        }
                        for (int j = look[0] - 1;!foundSecond, look[0] > 0; j--) {
                            if (grid[look[j]][1]->getPieceColour() == pieceColour 
                            && grid[look[j]][1]->getSymbol() == 'R') {
                                theMove.push_back(symbol + char(location[0] + 'a') + 'x' + char('a' + look[0]) + char(look[1] + 1));
                                foundSecond = true;
                            } else if (grid[look[j]][i]->spaceEmpty(grid, look)) {
                                continue;
                            } else {
                                break;
                            }
                        } 
                        break;
                    }
                }
            }
        } 
    } else if (symbol == 'N') {
        bool secondPiece = false;
        for (int i = -2; !secondPiece, i < 3; i++) {
            for (int j = -2; !secondPiece, i < 3; j++) {
                if (pow(i,2) + pow(j,2) == 3 
                && grid[look[0] + i][look[1] + j]->getSymbol() == 'R'
                && grid[look[0] + i][look[1] + j]->getPieceColour() == pieceColour) {
                    if (location[0] == look[0] + i) {
                        theMove.push_back(symbol + char(location[1] + 1) + 'x' + char('a' + look[0]) + char(look[1] + 1));
                    } else {
                        theMove.push_back(symbol + char(location[0] + 'a') + 'x' + char('a' + look[0]) + char(look[1] + 1));
                    }
                    secondPiece = true;
                }
            }
        }
    } else {
        theMove.push_back(symbol + 'x' + char('a' + look[0]) + char(look[1] + 1));
    }
    return theMove;
}