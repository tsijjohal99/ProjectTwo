#pragma once
#include "pieceColourType.h"
#include "queen.h"

class Bishop : public Queen {

    protected:
        bool movementStraight = false;

    public:
        Bishop(int square[2], PieceColourType colour);

        std::string constructMoveEmpty(int look[], std::vector<std::vector<ChessPiece*>> &grid);
        std::string constructMoveEnemy(int look[], std::vector<std::vector<ChessPiece*>> &grid);
    
};