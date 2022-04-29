#pragma once
#include <iostream>
#include <list>
#include <vector>

#include "pieceColourType.h"

class ChessPiece {
   protected:
    int location[2];
    char symbol = ' ';
    PieceColourType pieceColour;
    bool enPassant = false;
    int moveCounter = 0;

   public:
    ChessPiece(int square[2], PieceColourType colour);

    void setLocation(int a, int b);
    void setPieceColour(PieceColourType colour);
    void increaseMoveCounter();
    void decreaseMoveCounter();
    int *getLocation();
    char getSymbol();
    bool getEnPassant();
    void setEnPassant(bool en_passant);
    PieceColourType getPieceColour();
    int getMoveCounter();

    virtual std::list<std::string> possibleMoves(std::vector<std::vector<ChessPiece *>> &grid, bool second);
    bool spaceEmpty(std::vector<std::vector<ChessPiece *>> &grid, int look[]);
    bool spaceEnemy(std::vector<std::vector<ChessPiece *>> &grid, int look[]);
    virtual std::string constructMove(int look[], std::vector<std::vector<ChessPiece *>> &grid, bool enemy, bool second);
};