#pragma once
#include "pieceColourType.h"
#include "queen.h"

class Bishop : public Queen {
   public:
    Bishop(std::pair<int, int> square, PieceColourType colour);
};