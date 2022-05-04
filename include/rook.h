#pragma once
#include "pieceColourType.h"
#include "queen.h"

class Rook : public Queen {
   public:
    Rook(std::pair<int, int> square, PieceColourType colour);
};