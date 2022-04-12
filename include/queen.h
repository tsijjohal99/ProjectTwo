#pragma once
#include "pieceColourType.h"
#include "chessPiece.h"

class Queen : public ChessPiece {

    protected:
        bool movementStraight = true;
        bool movementDiag = true;
        int maxMovement = 8;

    public:
        Queen(int square[2], PieceColourType colour);

        bool getMovementStraight();
        bool getMovementDiag();
        
        void Queen::straight(std::vector<std::vector<bool>> &whereMove, std::vector<std::vector<ChessPiece*>> &grid, int index);
        void Queen::diagonal(std::vector<std::vector<bool>> &whereMove, std::vector<std::vector<ChessPiece*>> &grid, int neg);
        std::vector<std::vector<bool>> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid);
    
}; 