#pragma once
#include "queen.h"
#include "pieceColourType.h"

class Rook : public Queen {

    protected:
        bool movementDiag = false;
        bool hasMoved = false;
    
    public:
        Rook(int square[2], PieceColourType colour);

        bool constructRookVertical(int look[], std::vector<std::vector<ChessPiece*>> &grid, std::string &theMove, bool foundSecond, int i, bool enemy);
        bool constructRookHorizontal(int look[], std::vector<std::vector<ChessPiece*>> &grid, std::string &theMove, bool foundSecond, int i, bool enemy);
        std::string constructMoveEmpty(int look[], std::vector<std::vector<ChessPiece*>> &grid);
        std::string constructMoveEnemy(int look[], std::vector<std::vector<ChessPiece*>> &grid);

};