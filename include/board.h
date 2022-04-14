#pragma once
#include "chessPiece.h"
#include <vector>
#include <list>

class Board {
    private:
        int boardSize = 8;
        std::vector<std::vector<ChessPiece*>> grid;
        bool isCheck = false;
        bool isCheckmate = false;
        PieceColourType whoseTurn;
        int blackKing[2];
        int whiteKing[2];

    public:
        Board();

        int getBoardSize();
        std::vector<std::vector<ChessPiece*>> getGrid();
        void setBoardSize(int size);
        void setGrid(std::vector<std::vector<ChessPiece*>> theGrid);

        void displayBoard();
        void checkCheck(std::list<std::string> &theLegalMoves);
        bool checkCheckmate();
        std::list<std::string> legalMoves();
        bool makeMove(std::string move);
        void createPiece(ChessPiece *piece, int a, int b);
        void removePiece(ChessPiece *piece);
        void deleteBoard();
};