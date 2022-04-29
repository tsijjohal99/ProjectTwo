#include "chessPiece.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "pieceColourType.h"

ChessPiece::ChessPiece(int square[2], PieceColourType colour) {
    location[0] = square[0];
    location[1] = square[1];
    pieceColour = colour;
    symbol = ' ';
}

void ChessPiece::setLocation(int a, int b) {
    location[1] = b;
    location[0] = a;
}

void ChessPiece::setPieceColour(PieceColourType colour) {
    pieceColour = colour;
}

void ChessPiece::setEnPassant(bool en_passant) {
    enPassant = en_passant;
}

void ChessPiece::increaseMoveCounter() {
    moveCounter++;
}

void ChessPiece::decreaseMoveCounter() {
    moveCounter--;
}

int *ChessPiece::getLocation() {
    return location;
}

char ChessPiece::getSymbol() {
    return symbol;
}

bool ChessPiece::getEnPassant() {
    return enPassant;
}

PieceColourType ChessPiece::getPieceColour() {
    return pieceColour;
}

int ChessPiece::getMoveCounter() {
    return moveCounter;
}

std::list<std::string> ChessPiece::possibleMoves(std::vector<std::vector<ChessPiece *>> &grid, bool second) {
    std::list<std::string> empty;
    return empty;
}

bool ChessPiece::spaceEmpty(std::vector<std::vector<ChessPiece *>> &grid, int look[]) {
    return (grid[look[0]][look[1]]->getPieceColour() == PieceColourType::UNASSIGNED);
}

bool ChessPiece::spaceEnemy(std::vector<std::vector<ChessPiece *>> &grid, int look[]) {
    if ((pieceColour == PieceColourType::WHITE && grid[look[0]][look[1]]->getPieceColour() == PieceColourType::BLACK) || (pieceColour == PieceColourType::BLACK && grid[look[0]][look[1]]->getPieceColour() == PieceColourType::WHITE)) {
        return true;
    } else {
        return false;
    }
}

std::string ChessPiece::constructMove(int look[], std::vector<std::vector<ChessPiece *>> &grid, bool enemy, bool second) {
    std::string theMove = "";
    theMove += symbol;
    if (enemy) {
        theMove += 'x';
    }
    theMove += char('a' + look[0]);
    theMove += char('1' + look[1]);
    return theMove;
}