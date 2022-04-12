#pragma once
#include "pieceColourType.h"
#include <iostream>
#include <vector>

class ChessPiece {

    protected:
        int location[2];
        char symbol = ' ';
        PieceColourType pieceColour;

    public:
        ChessPiece(int square[2], PieceColourType colour);

        void setLocation(std::string square);
        int * getLocation();
        char getSymbol();
        virtual bool getHasMoved();
        PieceColourType getPieceColour();

        void move(int square[2], std::vector<std::vector<ChessPiece*>> &grid);
        virtual std::vector<std::vector<bool>> possibleMoves(std::vector<std::vector<ChessPiece*>> grid);
        bool spaceEmpty(std::vector<std::vector<ChessPiece*>> &grid, int look[]);
        bool spaceEnemy(std::vector<std::vector<ChessPiece*>> &grid, int look[]);
};