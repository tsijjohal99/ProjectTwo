#pragma once
#include "pieceColourType.h"
#include "queen.h"

class Bishop : public Queen {
   public:
    Bishop(int square[2], PieceColourType colour);
};