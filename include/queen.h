#pragma once
#include "pieceColourType.h"
#include "chessPiece.h"
#include <list>

class Queen : public ChessPiece {

    protected:
        int maxMovement;

    public:
        Queen(int square[2], PieceColourType colour);
        
        std::list<std::string> slide(std::vector<std::vector<ChessPiece*>> &grid, int direction[], bool second);
        std::list<std::string> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid, bool second);
        bool constructMoveSlide(std::string &theMove, int look[], std::vector<std::vector<ChessPiece*>> &grid, int direction[]);
        std::string constructMove(int look[], std::vector<std::vector<ChessPiece*>> &grid, bool enemy, bool second);
    
}; 