#pragma once
#include "pieceColourType.h"
#include "queen.h"
#include <list>

class King : public Queen {
    
    protected:
        int maxMovement = 2;
        bool hasMoved = false;
    
    public:
        King(int square[2], PieceColourType colour);

        void checkCastle(std::list<std::string> &whereMove, std::vector<std::vector<ChessPiece*>> &grid);
        std::list<std::string> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid);
};