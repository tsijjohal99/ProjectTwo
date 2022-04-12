#include "bishop.h"
#include "pieceColourType.h"

Bishop::Bishop(int square[2], PieceColourType colour) : Queen(square, colour) {
    symbol = (pieceColour == PieceColourType::WHITE) ? 'B' : 'b';
}