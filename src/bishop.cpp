#include "bishop.h"
#include "pieceColourType.h"
#include <string>

Bishop::Bishop(int square[2], PieceColourType colour) : Queen(square, colour) {
    symbol = 'B';
}

std::string Bishop::constructMoveEmpty(int look[], std::vector<std::vector<ChessPiece*>> &grid) {
    std::string theMove = "";
    theMove += symbol;
    theMove += char('a' + look[0]);
    theMove += char('1' + look[1]);
    return theMove;
}

std::string Bishop::constructMoveEnemy(int look[], std::vector<std::vector<ChessPiece*>> &grid) {
    std::string theMove = "";
    theMove.push_back(symbol);
    theMove.push_back('x');
    theMove.push_back(char('a' + look[0]));
    theMove.push_back(char(int(look[1] + 1))); 
    return theMove;
}