#include "bishop.h"

#include "pieceColourType.h"

Bishop::Bishop(std::pair<int, int> square, PieceColourType colour) : Queen(square, colour) {
    symbol = 'B';
}