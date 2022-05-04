#pragma once
#include <list>
#include <memory>

#include "chessPiece.h"

class Pawn : public ChessPiece {
   public:
    Pawn(std::pair<int, int> square, PieceColourType colour);

    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> possibleMoves(std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, bool second) override;
    std::string constructMove(std::pair<int, int> look, std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, bool enemy, bool second) override;
};