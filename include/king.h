#pragma once
#include <list>
#include <memory>

#include "pieceColourType.h"
#include "queen.h"

class King : public Queen {
   public:
    King(std::pair<int, int> square, PieceColourType colour);

    void checkCastle(std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> &whereMove, std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid);
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> possibleMoves(std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, bool second) override;
};