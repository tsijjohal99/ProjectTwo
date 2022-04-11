#pragma once
#include "chessPiece.h"

class Knight : public ChessPiece {
    public:
        std::vector<std::vector<bool>> possibleMoves(std::vector<std::vector<char>> grid);
};