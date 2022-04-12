#pragma once
#include "pieceColourType.h"
#include "queen.h"

class King : public Queen {
    
    protected:
        int maxMovement = 2;
        bool hasMoved = false;
    
    public:
        King(int square[2], PieceColourType colour);

        bool getHasMoved();
        void setHasMoved(bool newMove);

        void checkCastle(std::vector<std::vector<bool>> &whereMove, std::vector<std::vector<ChessPiece*>> &grid);
        std::vector<std::vector<bool>> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid);
};