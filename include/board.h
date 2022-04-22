#pragma once
#include "chessPiece.h"
#include <vector>
#include <list>
#include <iostream>

class Board {
    private:
        int boardSize = 8;
        std::vector<std::vector<ChessPiece*>> grid;
        bool isCheck = false;
        bool isCheckmate = false;
        PieceColourType whoseTurn;
        int blackKing[2];
        int whiteKing[2];
        std::list<std::string> movesMade;

    public:
        Board();

        int getBoardSize();
        std::vector<std::vector<ChessPiece*>>& getGrid();
        PieceColourType getWhoseTurn();
        bool getIsCheck();
        void setBoardSize(int size);
        void setGrid(std::vector<std::vector<ChessPiece*>> theGrid);
        void setWhoseTurn(PieceColourType colour);

        void addMove(std::string move);
        void createBoard();
        void displayBoard();
        void displayMovesMade();
        std::list<std::string> updateCheck(std::list<std::string> theLegalMoves);
        int *checkCheck();
        bool checkCheckmate();
        std::list<std::string> legalMoves(bool first);
        void displayLegalMoves();
        void findPiece(std::string move);
        void movingPiece(std::string move, int i, int j);
        void undoMove();
        bool makeMove(std::string move);
        void createPiece(ChessPiece *piece, int a, int b);
        void removePiece(ChessPiece *piece);
        void deleteBoard();
};