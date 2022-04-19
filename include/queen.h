#pragma once
#include "pieceColourType.h"
#include "chessPiece.h"
#include <list>

class Queen : public ChessPiece {

    protected:
        int maxMovement;

    public:
        Queen(int square[2], PieceColourType colour);
        
        std::list<std::string> slide(std::vector<std::vector<ChessPiece*>> &grid, int direction[]);
        std::list<std::string> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid);
        bool constructMoveSlide(int look[], std::vector<std::vector<ChessPiece*>> &grid, bool enemy);
        std::string constructMove(int look[], std::vector<std::vector<ChessPiece*>> &grid, bool enemy);
        virtual std::string constructMoveEmpty(int look[], std::vector<std::vector<ChessPiece*>> &grid);
        virtual std::string constructMoveEnemy(int look[], std::vector<std::vector<ChessPiece*>> &grid);
    
}; 