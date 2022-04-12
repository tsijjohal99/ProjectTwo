#pragma once
#include "chessPiece.h"
#include <vector>
#include <list>

class Board {
    private:
        int boardSize = 8;
        std::vector<std::vector<ChessPiece*>> grid;
        bool isCheck;
        bool isCheckmate;
        PieceColourType whoseTurn;
        int blackKing[2];
        int whiteKing[2];

    public:
        Board(int size);

        int getBoardSize();
        std::vector<std::vector<ChessPiece*>> getGrid();
        void setBoardSize(int size);
        void setGrid(std::vector<std::vector<ChessPiece*>> theGrid);

        void displayBoard();
        bool checkCheck();
        bool checkCheckmate();
        std::list<std::string> legalMoves();
        void makeMove(std::string move);
        void createPiece(std::string create);
        void removePiece(std::string remove);
};