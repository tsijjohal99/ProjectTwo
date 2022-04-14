#pragma once
#include "pieceColourType.h"
#include "chessPiece.h"
#include <list>

class Queen : public ChessPiece {

    protected:
        int maxMovement;

    public:
        Queen(int square[2], PieceColourType colour);
        
        std::list<std::string> straight(std::vector<std::vector<ChessPiece*>> &grid, int index);
        std::list<std::string> diagonal(std::vector<std::vector<ChessPiece*>> &grid, int neg);
        std::list<std::string> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid);
        virtual std::string constructMoveEmpty(int look[], std::vector<std::vector<ChessPiece*>> &grid);
        virtual std::string constructMoveEnemy(int look[], std::vector<std::vector<ChessPiece*>> &grid);
    
}; 