#pragma once
#include <iostream>
#include <list>
#include <vector>

#include "chessPiece.h"

class Board {
   private:
    int boardSize = 8;
    std::vector<std::vector<ChessPiece *>> grid;
    bool isCheck = false;
    bool isCheckmate = false;
    PieceColourType whoseTurn;
    std::pair<int, int> blackKing;
    std::pair<int, int> whiteKing;
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> listOfMoves;
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> legalMoves;

   public:
    Board();
    ~Board();

    int getBoardSize();
    std::vector<std::vector<ChessPiece *>> &getGrid();
    PieceColourType getWhoseTurn();
    bool getIsCheck();
    std::pair<int, int> getBlackKing();
    std::pair<int, int> getWhiteKing();
    void setBoardSize(int size);
    void setGrid(std::vector<std::vector<ChessPiece *>> theGrid);
    void setWhoseTurn(PieceColourType colour);
    void setIsCheck(bool check);

    void addMove(std::tuple<std::string, std::pair<int, int>, std::pair<int, int>> move);
    void createBoard();
    void displayBoard();
    void displayMovesMade();
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> updateCheck(std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> theLegalMoves);
    bool checkCheck();
    bool checkCheckmate();
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> calculateLegalMoves(bool first);
    void displayLegalMoves();
    void findPiece(std::string move);
    void movingPiece(std::string move, int i, int j);
    void movingPiece(std::string move, std::pair<int, int> original, std::pair<int, int> target);
    void undoMove();
    bool makeMove(std::string move);
    bool makeMove(std::tuple<std::string, std::pair<int, int>, std::pair<int, int>> moveInfo);
    void createPiece(ChessPiece *piece, std::pair<int, int> location);
    void removePiece(ChessPiece *piece);
    void deleteBoard();
};