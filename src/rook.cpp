#include "rook.h"
#include "pieceColourType.h"

Rook::Rook(int square[2], PieceColourType colour) : Queen(square, colour) {
    symbol = (pieceColour == PieceColourType::WHITE) ? 'R' : 'r';
}

bool Rook::getHasMoved() {
    return hasMoved;
}

void Rook::setHasMoved(bool newMove) {
    hasMoved == newMove;
}