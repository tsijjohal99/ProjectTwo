#pragma once
#include "pieceColourType.h"
#include "chessPiece.h"
#include <list>

class Knight : public ChessPiece {
    public:
        Knight(int square[2], PieceColourType colour);

        std::list<std::string> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid);
        std::string constructMoveEmpty(int look[], std::vector<std::vector<ChessPiece*>> &grid);
        std::string constructMoveEnemy(int look[], std::vector<std::vector<ChessPiece*>> &grid);
};