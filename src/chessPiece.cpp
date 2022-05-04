#include "chessPiece.h"

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "pieceColourType.h"

ChessPiece::ChessPiece(std::pair<int, int> square, PieceColourType colour) {
    location = square;
    pieceColour = colour;
    symbol = ' ';
}

void ChessPiece::setLocation(std::pair<int, int> loc) {
    location = loc;
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

std::pair<int, int> ChessPiece::getLocation() {
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

std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> ChessPiece::possibleMoves(std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, bool second) {
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> empty;
    return empty;
}

bool ChessPiece::spaceEmpty(std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, std::pair<int, int> look) {
    return (grid[look.first][look.second]->getPieceColour() == PieceColourType::UNASSIGNED);
}

bool ChessPiece::spaceEnemy(std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, std::pair<int, int> look) {
    if ((pieceColour == PieceColourType::WHITE && grid[look.first][look.second]->getPieceColour() == PieceColourType::BLACK) || (pieceColour == PieceColourType::BLACK && grid[look.first][look.second]->getPieceColour() == PieceColourType::WHITE)) {
        return true;
    } else {
        return false;
    }
}

std::string ChessPiece::constructMove(std::pair<int, int> look, std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, bool enemy, bool second) {
    std::string theMove = "";
    theMove += symbol;
    if (enemy) {
        theMove += 'x';
    }
    theMove += char('a' + look.first);
    theMove += char('1' + look.second);
    return theMove;
}