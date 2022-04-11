#pragma once
#include <vector>
#include <list>

class Board {
    private:
        int boardSize;
        std::vector<std::vector<char>> grid;
        bool isCheck;
        bool isCheckmate;

    public:
        Board(int size);

        int getBoardSize();
        std::vector<std::vector<char>> getGrid();
        void setBoardSize(int size);
        void setGrid(std::vector<std::vector<char>> theGrid);

        void displayBoard();
        bool checkCheck();
        bool checkCheckmate();
        std::list<std::string> legalMoves();
        void makeMove(std::string move);
        void createPiece(std::string create);
        void removePiece(std::string remove);
};