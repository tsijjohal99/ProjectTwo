#pragma once
#include "pieceColourType.h"
#include "queen.h"

class Rook : public Queen {
   public:
    Rook(int square[2], PieceColourType colour);
};