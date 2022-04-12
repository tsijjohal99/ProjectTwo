#pragma once
#include "chessPiece.h"

class Pawn : public ChessPiece {
    protected:
        bool hasMoved = false;

    public:
        Pawn(int square[2], PieceColourType colour);

        std::vector<std::vector<bool>> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid);

};