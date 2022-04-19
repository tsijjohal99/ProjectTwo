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
        PieceColourType getWhoseTurn();
        void setBoardSize(int size);
        void setGrid(std::vector<std::vector<ChessPiece*>> theGrid);

        void displayBoard();
        std::list<std::string> updateCheck(std::list<std::string> theLegalMoves);
        bool checkCheck();
        bool checkCheckmate();
        std::list<std::string> legalMoves();
        void displayLegalMoves();
        bool makeMove(std::string move);
        void createPiece(ChessPiece *piece, int a, int b);
        void removePiece(ChessPiece *piece);
        void deleteBoard();
};