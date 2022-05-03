#pragma once
#include <list>

#include "chessPiece.h"
#include "pieceColourType.h"

class Knight : public ChessPiece {
   public:
    Knight(int square[2], PieceColourType colour);

    std::list<std::string> possibleMoves(std::vector<std::vector<ChessPiece *>> &grid, bool second) override;
    std::string constructMove(int look[], std::vector<std::vector<ChessPiece *>> &grid, bool enemy, bool second) override;
};