#pragma once
#include "pieceColourType.h"
#include "chessPiece.h"

class Knight : public ChessPiece {
    public:
        Knight(int square[2], PieceColourType colour);

        std::vector<std::vector<bool>> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid);
};