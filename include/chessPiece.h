#pragma once
#include <iostream>
#include <list>
#include <tuple>
#include <utility>
#include <vector>

#include "pieceColourType.h"

class ChessPiece {
   protected:
    std::pair<int, int> location;
    char symbol = ' ';
    PieceColourType pieceColour;
    bool enPassant = false;
    int moveCounter = 0;

   public:
    ChessPiece(std::pair<int, int> square, PieceColourType colour);

    void setLocation(std::pair<int, int> loc);
    void setPieceColour(PieceColourType colour);
    void increaseMoveCounter();
    void decreaseMoveCounter();
    std::pair<int, int> getLocation();
    char getSymbol();
    bool getEnPassant();
    void setEnPassant(bool en_passant);
    PieceColourType getPieceColour();
    int getMoveCounter();

    virtual std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> possibleMoves(std::vector<std::vector<ChessPiece *>> &grid, bool second);
    bool spaceEmpty(std::vector<std::vector<ChessPiece *>> &grid, std::pair<int, int> look);
    bool spaceEnemy(std::vector<std::vector<ChessPiece *>> &grid, std::pair<int, int> look);
    virtual std::string constructMove(std::pair<int, int> look, std::vector<std::vector<ChessPiece *>> &grid, bool enemy, bool second);
};