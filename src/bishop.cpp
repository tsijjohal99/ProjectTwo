#include "bishop.h"
#include "pieceColourType.h"
#include <string>

Bishop::Bishop(int square[2], PieceColourType colour) : Queen(square, colour) {
    symbol = 'B';
}