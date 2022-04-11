#include "rook.h"

Rook::Queen::ChessPiece::ChessPiece(int square[2], bool colour) {
    location[0] = square[0];
    location[1] = square[1];
    white = colour;
    symbol = (white) ? 'R' : 'r';
}