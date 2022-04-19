#pragma once
#include "chessPiece.h"
#include <list>

class Pawn : public ChessPiece {

    public:
        Pawn(int square[2], PieceColourType colour);

        std::list<std::string> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid, bool second);
        std::string constructMove(int look[], std::vector<std::vector<ChessPiece*>> &grid, bool enemy, bool second);
        void promotion(int look[], int end, std::list<std::string> &whereMove, std::string move);
};