#pragma once
#include "pieceColourType.h"
#include "chessPiece.h"
#include <list>

class Queen : public ChessPiece {

    protected:
        bool movementStraight = true;
        bool movementDiag = true;
        int maxMovement = 8;

    public:
        Queen(int square[2], PieceColourType colour);

        bool getMovementStraight();
        bool getMovementDiag();
        
        std::list<std::string> straight(std::vector<std::vector<ChessPiece*>> &grid, int index);
        std::list<std::string> diagonal(std::vector<std::vector<ChessPiece*>> &grid, int neg);
        std::list<std::string> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid);
    
}; 