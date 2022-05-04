#pragma once
#include <iostream>
#include <list>

#include "chessPiece.h"
#include "pieceColourType.h"

class Knight : public ChessPiece {
   public:
    Knight(std::pair<int, int> square, PieceColourType colour);

    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> possibleMoves(std::vector<std::vector<ChessPiece *>> &grid, bool second) override;
    std::string constructMove(std::pair<int, int> look, std::vector<std::vector<ChessPiece *>> &grid, bool enemy, bool second) override;
};