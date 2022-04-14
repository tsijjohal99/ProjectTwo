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
#include <list>
#include <iostream>
#include <cctype>
#include <algorithm>

Board::Board() {
    grid.resize(boardSize, std::vector<ChessPiece*> (boardSize));
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
                if (j == 0) {
                    std::cout << " ";
                }
                if(j % 2 == 0)
                    std::cout << " ";
                else std::cout<<"---";
            } else {
                if(j % 2 == 0)
                    std::cout<<"|";
                else {
                    std::cout << " ";
                    if (grid[(j-1)/2][7 - (i-1)/2]->getPieceColour() == PieceColourType::BLACK) {
                        std::cout << char(grid[(j-1)/2][(i-1)/2]->getSymbol() -'A' + 'a');
                    } else {
                        std::cout << grid[(j-1)/2][(i-1)/2]->getSymbol();
                    }
                    std::cout << " ";
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

void Board::checkCheck(std::list<std::string> &theLegalMoves) {
    whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
    isCheck = false;
    std::list<std::string> oppositionLegalMoves = legalMoves();
    whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
    isCheck = true;
    for (std::string myMove : theLegalMoves) {
        for (std::string aMove :oppositionLegalMoves) {
            if (aMove[aMove.size() -1] == '#') {
                theLegalMoves.remove(myMove);
            }
        }
    }
}

void Board::checkCheckmate(std::list<std::string> &theLegalMoves) {
    
}

std::list<std::string> Board::legalMoves() {
    std::list<std::string> theLegalMoves;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (grid[i][j]->getPieceColour() == whoseTurn) {
                std::list<std::string> theMoves = grid[i][j]->possibleMoves(grid);
                theLegalMoves.insert(theLegalMoves.end(), theMoves.begin(), theMoves.end());
            }
        }
    }
    if (isCheck) {
        checkCheck(theLegalMoves);
    }
    
    return theLegalMoves;
}

void Board::makeMove(std::string move) {
    std::list<std::string> theLegalMoves = legalMoves();
    std::list<std::string>::iterator it = std::find(theLegalMoves.begin(), theLegalMoves.end(), move);
    if (it != theLegalMoves.end()) {
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (grid[i][j]->getPieceColour() == whoseTurn) {
                    std::list<std::string> theMoves = grid[i][j]->possibleMoves(grid);
                    checkCheck(theMoves);
                    std::list<std::string>::iterator it2;
                    it2 = std::find(theMoves.begin(), theMoves.end(), move);
                    if (it2 != theLegalMoves.end()) {
                        if (move[move.size() - 1] == '#') {
                            isCheckmate = true;
                            break;
                        } else if (move[move.size() - 1] == '+') {
                            isCheck = true;
                            move.pop_back();
                        }
                        if (!grid[i][j]->getHasMoved()) {
                            grid[i][j]->setHasMoved(true);
                        }
                        if (move[0] == grid[i][j]->getSymbol()) {
                            int look[] = {int(move[move.size()-2] - 'a'), int(move[move.size()-1] - 1)};
                            if (grid[i][j]->getSymbol() == 'K') {
                                switch (grid[i][j]->getPieceColour()) {
                                    case PieceColourType::WHITE: {
                                        whiteKing[0] = look[0];
                                        whiteKing[1] = look[1];
                                        break;
                                    }
                                    case PieceColourType::BLACK: {
                                        blackKing[0] = look[0];
                                        blackKing[1] = look[1];
                                        break;
                                    }
                                }
                            }
                            removePiece(grid[int(move[move.size()-2] - 'a')][int(move[move.size()-1] - 1)]);
                            createPiece(grid[i][j], int(move[move.size()-2] - 'a'), int(move[move.size()-1] - 1));
                            removePiece(grid[i][j]);
                            int square[] = {i,j};
                            createPiece(new ChessPiece(square , PieceColourType::UNASSIGNED), i, j);
                        } else if (move == "0-0-0") {
                            if (grid[i][j]->getSymbol() == 'K') {
                                switch (grid[i][j]->getPieceColour()) {
                                    case PieceColourType::WHITE: {
                                        whiteKing[0] = 2;
                                        break;
                                    }
                                    case PieceColourType::BLACK: {
                                        blackKing[0] = 2;
                                        break;
                                    }
                                }
                            }
                            removePiece(grid[2][j]);
                            createPiece(grid[4][j], 2, j);
                            removePiece(grid[4][j]);
                            int square[2] = {4,j};
                            createPiece(new ChessPiece(square , PieceColourType::UNASSIGNED), 4, j);
                            removePiece(grid[3][j]);
                            createPiece(grid[0][j], 3, j);
                            removePiece(grid[0][j]);
                            square[0] = 0;
                            createPiece(new ChessPiece(square , PieceColourType::UNASSIGNED), 0, j);
                        } else if (move == "0-0") {
                            if (grid[i][j]->getSymbol() == 'K') {
                                switch (grid[i][j]->getPieceColour()) {
                                    case PieceColourType::WHITE: {
                                        whiteKing[0] = 6;
                                        break;
                                    }
                                    case PieceColourType::BLACK: {
                                        blackKing[0] = 6;
                                        break;
                                    }
                                }
                            }
                            removePiece(grid[6][j]);
                            createPiece(grid[4][j], 6, j);
                            removePiece(grid[4][j]);
                            int square[2] = {4,j};
                            createPiece(new ChessPiece(square , PieceColourType::UNASSIGNED), 4, j);
                            removePiece(grid[5][j]);
                            createPiece(grid[7][j], 5, j);
                            removePiece(grid[7][j]);
                            square[0] = 7;
                            createPiece(new ChessPiece(square , PieceColourType::UNASSIGNED), 7, j);
                        } else if (move[0] <= 'h' && move[0] >= 'a') {
                            if (move.size() == 2) {
                                if (!grid[i][j]->getHasMoved() && abs(int(move[1] - 1) - j) == 2) {
                                    grid[i][j]->setEnPassant(true);
                                } else {
                                    grid[i][j]->setEnPassant(false);
                                }
                                removePiece(grid[int(move[0] - 'a')][int(move[1] - 1)]);
                                createPiece(grid[i][j], int(move[0] - 'a'), int(move[1] - 1));
                                removePiece(grid[i][j]);
                                int square[] = {i,j};
                                createPiece(new ChessPiece(square , PieceColourType::UNASSIGNED), i, j);
                            } else if (move[move.size() - 2] == '=') {
                                int square[] = {int(move[move.size() - 4] - 'a'), int(move[move.size() - 3] - 1)};
                                removePiece(grid[square[0]][square[1]]);
                                switch (move[move.size() - 1]) {
                                    case 'Q': {
                                        createPiece(new Queen(square , grid[i][j]->getPieceColour()), square[0], square[1]);
                                        break;
                                    }
                                    case 'R': {
                                        createPiece(new Rook(square , grid[i][j]->getPieceColour()), square[0], square[1]);
                                        break;
                                    }
                                    case 'B': {
                                        createPiece(new Bishop(square , grid[i][j]->getPieceColour()), square[0], square[1]);
                                        break;
                                    }
                                    case 'N': {
                                        createPiece(new Knight(square , grid[i][j]->getPieceColour()), square[0], square[1]);
                                        break;
                                    }
                                }
                                int square2[] = {i,j};
                                createPiece(new ChessPiece(square2 , PieceColourType::UNASSIGNED), i, j);
                            } else {
                                int look[] = {int(move[move.size() - 2] - 'a'), int(move[move.size() - 1] - 1)};
                                if (grid[i][j]->spaceEmpty(grid, look)) {
                                    look[1] -= (grid[i][j]->getPieceColour() == PieceColourType::WHITE) ? 1 : -1;
                                    removePiece(grid[look[0]][look[1]]);
                                    createPiece(new ChessPiece(look, PieceColourType::UNASSIGNED), look[0], look[1]);
                                    look[1] += (grid[i][j]->getPieceColour() == PieceColourType::WHITE) ? 1 : -1;
                                }
                                removePiece(grid[look[0]][look[1]]);
                                createPiece(grid[i][j], i,j);
                                removePiece(grid[i][j]);
                                int square[] = {i,j};
                                createPiece(new ChessPiece(square, PieceColourType::UNASSIGNED), i ,j);
                            }
                        }
                    }
                }
            }
        }
    } else {
        std::cout << "That move isn't possible. Please try again." << std::endl;
    }
}

void Board::createPiece(ChessPiece *piece, int a, int b) {
    grid[a][b] = piece;
}

void Board::removePiece(ChessPiece *piece) {
    delete piece;
}

void Board::deleteBoard() {
    for (int i = 0; i < boardSize; i++ ) {
        for (int j = 0; j < boardSize; j++ ) {
            removePiece(grid[i][j]);
        }
    }
}