#include "board.h"
#include "pieceColourType.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "chessPiece.h"
#include <vector>
#include <iostream>

Board::Board(int size) {
    boardSize = size;
    grid.resize(size, std::vector<ChessPiece*> (size));
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            int square[] = {i, j};
            PieceColourType colour;
            if (j < 2) {
                colour = PieceColourType::WHITE;
            } else if (j > 5) {
                colour = PieceColourType::BLACK;
            } else {
                colour = PieceColourType::UNASSIGNED;
            }
            if ((i == 0 || i == 7) && (j == 0 || j == 7)) {
                grid[i][j] = new Rook(square, colour);
            } else if ((i == 1 || i == 6) && (j == 0 || j == 7)) {
                grid[i][j] = new Knight(square, colour);
            } else if ((i == 2 || i == 5) && (j == 0 || j == 7)) {
                grid[i][j] = new Bishop(square, colour);
            } else if (i == 3 && (j == 0 || j == 7)) {
                grid[i][j] = new Queen(square, colour);
            } else if (i == 4 && (j == 0 || j == 7)) {
                grid[i][j] = new King(square, colour);
                if (colour == PieceColourType::WHITE) {
                    whiteKing[0] = square[0];
                    whiteKing[1] = square[1];
                } else {
                    blackKing[0] = square[0];
                    blackKing[1] = square[1];
                }
            } else if (j == 1 || j == 6) {
                grid[i][j] = new Pawn(square, colour);
            } else {
                grid[i][j] = new ChessPiece(square, colour);
            }
        }
    }
    whoseTurn = PieceColourType::WHITE;
}

int Board::getBoardSize() {
    return boardSize;
}

std::vector<std::vector<ChessPiece*>> Board::getGrid() {
    return grid;
}

void Board::setBoardSize(int size) {
    boardSize = size;
}

void Board::setGrid(std::vector<std::vector<ChessPiece*>> theGrid) {
    grid == theGrid;
}

void Board::displayBoard() {
    std::cout << std::endl;
    for(int i = 0; i <= 2*boardSize; i++) {
        if(i % 2 != 0)
            std::cout << 8 - i/2;
        for(int j = 0; j <= 2*boardSize; j++){
            if(i % 2 == 0) {
                if(j % 2 == 0)
                    std::cout << " ";
                else std::cout<<"---";
            } else {
                if(j % 2 == 0)
                    std::cout<<"|";
                else {
                    std::cout << " " <<grid[(j-1)/2][(i-1)/2]->getSymbol() << " ";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout<<" ";
    for(int j = 0; j <= 4*boardSize; j++){
        if(j % 4 == 2)
            std::cout<<(char)(j/4 +'A');
        else {
            std::cout<<" ";
        }
    }
    std::cout << std::endl;
}

bool Board::checkCheck() {

}

bool Board::checkCheckmate() {
    
}

std::list<std::string> Board::legalMoves() {
    
}

void Board::makeMove(std::string move) {
    try {
        std::list<std::string> theLegalMoves = legalMoves();
        for (std::string a : theLegalMoves) {
            if (move == a) {
                if (checkCheck())
            }
        }
    } catch (std::invalid_argument) {
        throw("That move isn't possible.");
    }
}

void Board::createPiece(std::string create) {

}

void Board::removePiece(std::string remove) {

}