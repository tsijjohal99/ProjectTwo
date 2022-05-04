#pragma once
#include <list>

#include "chessPiece.h"
#include "pieceColourType.h"

class Queen : public ChessPiece {
   protected:
    int maxMovement;

   public:
    Queen(std::pair<int, int> square, PieceColourType colour);

    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> slide(std::vector<std::vector<ChessPiece *>> &grid, int direction[], bool second);
    virtual std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> possibleMoves(std::vector<std::vector<ChessPiece *>> &grid, bool second) override;
    bool constructMoveSlide(std::string &theMove, std::pair<int, int> look, std::vector<std::vector<ChessPiece *>> &grid, int direction[]);
    std::string constructMove(std::pair<int, int> look, std::vector<std::vector<ChessPiece *>> &grid, bool enemy, bool second) override;
};