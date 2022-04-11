#pragma once
#include <iostream>
#include <vector>

class ChessPiece {

    private:
        int location[2];
        char symbol;
        bool white;

    public:
        ChessPiece(int square[2], bool colour);

        void setLocation(std::string square);
        int * getLocation();
        char getSymbol();
        bool getWhite();

        void move(int square[2], std::vector<std::vector<char>> &grid);
        std::vector<std::vector<bool>> possibleMoves(std::vector<std::vector<char>> grid);
        bool spaceEmpty(std::vector<std::vector<char>> grid, int look[]);
        bool spaceEnemy(std::vector<std::vector<char>> grid, int look[]);
};