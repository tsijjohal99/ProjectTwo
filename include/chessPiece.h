#pragma once
#include "pieceColourType.h"
#include <iostream>
#include <vector>
#include <list>

class ChessPiece {

    protected:
        int location[2];
        char symbol = ' ';
        PieceColourType pieceColour;
        bool hasMoved = false;
        bool enPassant = false;

    public:
        ChessPiece(int square[2], PieceColourType colour);

        void setLocation(int a, int b);
        int *getLocation();
        char getSymbol();
        bool getHasMoved();
        bool getEnPassant();
        void setHasMoved(bool has_moved);
        void setEnPassant(bool en_passant);
        PieceColourType getPieceColour();

        virtual std::list<std::string> possibleMoves(std::vector<std::vector<ChessPiece*>> &grid);
        bool spaceEmpty(std::vector<std::vector<ChessPiece*>> &grid, int look[]);
        bool spaceEnemy(std::vector<std::vector<ChessPiece*>> &grid, int look[]);
        virtual std::string constructMove(int look[], std::vector<std::vector<ChessPiece*>> &grid, bool enemy);
        virtual std::string constructMoveEmpty(int look[], std::vector<std::vector<ChessPiece*>> &grid);
        virtual std::string constructMoveEnemy(int look[], std::vector<std::vector<ChessPiece*>> &grid);
};