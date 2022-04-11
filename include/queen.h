#pragma once
#include "chessPiece.h"

class Queen : public ChessPiece {

    protected:
        bool movementStraight = true;
        bool movementDiag = true;
        int maxMovement = 8;

    public:
        bool getMovementStraight();
        bool getMovementDiag();
        std::vector<std::vector<bool>> possibleMoves(std::vector<std::vector<char>> grid);
    
};