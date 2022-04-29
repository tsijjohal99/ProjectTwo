#include "rook.h"

#include "pieceColourType.h"

Rook::Rook(int square[2], PieceColourType colour) : Queen(square, colour) {
    symbol = 'R';
}