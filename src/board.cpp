#include "board.h"
#include <vector>
#include <iostream>

Board::Board(int size) {
    boardSize = size;
    grid.resize(size, std::vector<char> (size, ' '));
}

int Board::getBoardSize() {
    return boardSize;
}

std::vector<std::vector<char>> Board::getGrid() {
    return grid;
}

void Board::setBoardSize(int size) {
    boardSize = size;
}

void Board::setGrid(std::vector<std::vector<char>> theGrid) {
    grid == theGrid;
}

void Board::displayBoard() {
    std::cout << std::endl;
    for(int i = 0; i <= 2*boardSize; i++) {
        for(int j = 0; j <= 2*boardSize; j++){
            if(i%2==0) {
                if(j%2==0)
                    std::cout << " ";
                else std::cout<<"---";
            } else {
                if(j%2==0)
                    std::cout<<"|";
                else {
                    std::cout << " " << grid[(i-1)/2][(j-1)/2] << " ";
                }
            }
        }
        std::cout << std::endl;
    }
}

bool Board::checkCheck() {
    
}

bool Board::checkCheckmate() {
    
}

std::list<std::string> Board::legalMoves() {
    
}

void Board::makeMove(std::string move) {

}

void Board::createPiece(std::string create) {

}

void Board::removePiece(std::string remove) {

}