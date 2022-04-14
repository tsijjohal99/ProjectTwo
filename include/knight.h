#pragma once
#include "pieceColourType.h"
#include "chessPiece.h"
#include <list>

class Knight : public ChessPiece {
    public:
        Knight(int square[2], PieceColourType colour);

        std::list<std::string> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid);
};