#pragma once
#include "queen.h"
#include "pieceColourType.h"

class Rook : public Queen {

    protected:
        bool movementDiag = false;
        bool hasMoved = false;
    
    public:
        Rook(int square[2], PieceColourType colour);

};