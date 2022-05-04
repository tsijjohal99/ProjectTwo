#include "rook.h"

#include "pieceColourType.h"

Rook::Rook(std::pair<int, int> square, PieceColourType colour) : Queen(square, colour) {
    symbol = 'R';
}