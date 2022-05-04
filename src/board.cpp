#include "board.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <cctype>
#include <exception>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "bishop.h"
#include "chessPiece.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "pieceColourType.h"
#include "queen.h"
#include "rook.h"

Board::Board() {
    grid.resize(boardSize, std::vector<std::shared_ptr<ChessPiece>>(boardSize));
    createBoard();
    whoseTurn = PieceColourType::WHITE;
}

Board::~Board() {
    // deleteBoard();
}

int Board::getBoardSize() {
    return boardSize;
}

std::vector<std::vector<std::shared_ptr<ChessPiece>>> &Board::getGrid() {
    return grid;
}

PieceColourType Board::getWhoseTurn() {
    return whoseTurn;
}

bool Board::getIsCheck() {
    return isCheck;
}

std::pair<int, int> Board::getBlackKing() {
    return blackKing;
}

std::pair<int, int> Board::getWhiteKing() {
    return whiteKing;
}

void Board::setBoardSize(int size) {
    boardSize = size;
}

void Board::setGrid(std::vector<std::vector<std::shared_ptr<ChessPiece>>> theGrid) {
    grid == theGrid;
}

void Board::setWhoseTurn(PieceColourType colour) {
    whoseTurn = colour;
}

void Board::setIsCheck(bool check) {
    isCheck = check;
}

void Board::addMove(std::tuple<std::string, std::pair<int, int>, std::pair<int, int>> move) {
    listOfMoves.push_back(move);
}

void Board::createBoard() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            std::pair<int, int> square = {i, j};
            PieceColourType colour;
            if (j < 2) {
                colour = PieceColourType::WHITE;
            } else if (j > 5) {
                colour = PieceColourType::BLACK;
            } else {
                colour = PieceColourType::UNASSIGNED;
            }
            if ((i == 0 || i == 7) && (j == 0 || j == 7)) {
                createPiece(std::make_shared<Rook>(square, colour), square);
            } else if ((i == 1 || i == 6) && (j == 0 || j == 7)) {
                createPiece(std::make_shared<Knight>(square, colour), square);
            } else if ((i == 2 || i == 5) && (j == 0 || j == 7)) {
                createPiece(std::make_shared<Bishop>(square, colour), square);
            } else if (i == 3 && (j == 0 || j == 7)) {
                createPiece(std::make_shared<Queen>(square, colour), square);
            } else if (i == 4 && (j == 0 || j == 7)) {
                createPiece(std::make_shared<King>(square, colour), square);
                if (colour == PieceColourType::WHITE) {
                    whiteKing = square;
                } else {
                    blackKing = square;
                }
            } else if (j == 1 || j == 6) {
                createPiece(std::make_shared<Pawn>(square, colour), square);
            } else {
                createPiece(std::make_shared<ChessPiece>(square, colour), square);
            }
        }
    }
}

void Board::displayBoard() {
    std::cout << std::endl;
    for (int i = 2 * boardSize; i >= 0; i--) {
        if (i % 2 != 0)
            std::cout << i / 2 + 1;
        for (int j = 0; j <= 2 * boardSize; j++) {
            if (i % 2 == 0) {
                if (j == 0) {
                    std::cout << " ";
                }
                if (j % 2 == 0)
                    std::cout << " ";
                else
                    std::cout << "---";
            } else {
                if (j % 2 == 0)
                    std::cout << "|";
                else {
                    std::cout << " ";
                    if (grid[(j - 1) / 2][(i - 1) / 2]->getPieceColour() == PieceColourType::BLACK) {
                        std::cout << char(grid[(j - 1) / 2][(i - 1) / 2]->getSymbol() - 'A' + 'a');
                    } else {
                        std::cout << grid[(j - 1) / 2][(i - 1) / 2]->getSymbol();
                    }
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << " ";
    for (int j = 0; j <= 4 * boardSize; j++) {
        if (j % 4 == 2)
            std::cout << (char)(j / 4 + 'A');
        else {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void Board::displayMovesMade() {
    int i = 1;
    for (std::tuple move : listOfMoves) {
        if (i % 2 != 0) {
            std::cout << (i + 1) / 2 << ". ";
        }
        std::cout << std::get<0>(move) << " ";
        if (i % 2 == 0) {
            std::cout << "." << std::endl;
        }
        i++;
    }
}

std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> Board::updateCheck(std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> theLegalMoves) {
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> movesToRemove;
    for (std::tuple myMove : theLegalMoves) {
        movingPiece(std::get<0>(myMove), std::get<1>(myMove), std::get<2>(myMove));
        listOfMoves.push_back(myMove);
        whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
        isCheck = false;
        std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> oppositionLegalMoves = calculateLegalMoves(false);
        whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
        isCheck = true;
        for (std::tuple aMove : oppositionLegalMoves) {
            bool remove = false;
            if (int(std::get<0>(aMove)[std::get<0>(aMove).size() - 2] - 'a') == whiteKing.first && int(std::get<0>(aMove)[std::get<0>(aMove).size() - 1] - '1') == whiteKing.second && whoseTurn == PieceColourType::WHITE) {
                remove = true;
            } else if (int(std::get<0>(aMove)[std::get<0>(aMove).size() - 2] - 'a') == blackKing.first && int(std::get<0>(aMove)[std::get<0>(aMove).size() - 1] - '1') == blackKing.second && whoseTurn == PieceColourType::BLACK) {
                remove = true;
            }
            if (remove) {
                movesToRemove.push_back(myMove);
            }
        }
        whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
        undoMove();
    }
    for (std::tuple move : movesToRemove) {
        std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>>::iterator it = theLegalMoves.begin();
        while (it != theLegalMoves.end()) {
            if (*it == move) {
                theLegalMoves.erase(it);
                break;
            } else {
                ++it;
            }
        }
    }
    return theLegalMoves;
}

bool Board::checkCheck() {
    bool checkTemp = isCheck;
    whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> withoutCheck = calculateLegalMoves(false);
    isCheck = true;
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> withCheck = updateCheck(withoutCheck);  // this line is messing up somehow
    whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
    isCheck = checkTemp;
    return (withCheck.size() < withoutCheck.size());
}

bool Board::checkCheckmate() {
    bool checkTemp = isCheck;
    whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
    isCheck = true;
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> withCheck = calculateLegalMoves(false);  // this line is messing up somehow
    whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
    isCheck = checkTemp;
    return (withCheck.size() == 0);
}

std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> Board::calculateLegalMoves(bool first) {
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> movesToRemove;
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> theLegalMoves;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (grid[i][j]->getPieceColour() == whoseTurn) {
                std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> theMoves = grid[i][j]->possibleMoves(grid, false);
                for (std::tuple move : theMoves) {
                    std::string moveString;
                    std::pair<int, int> original, target;
                    std::tie(moveString, original, target) = move;
                    if (moveString[moveString.size() - 1] == '+' && first) {
                        movingPiece(moveString, original, target);
                        listOfMoves.push_back(move);
                        if (checkCheckmate()) {
                            movesToRemove.push_back(move);
                            moveString.pop_back();
                            moveString += '#';
                            theLegalMoves.push_back(std::make_tuple(moveString, original, target));
                        }
                        whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
                        undoMove();
                    }
                }
                theLegalMoves.insert(theLegalMoves.end(), theMoves.begin(), theMoves.end());
            }
        }
    }
    for (std::tuple move : movesToRemove) {
        std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>>::iterator it = theLegalMoves.begin();
        while (it != theLegalMoves.end()) {
            if (*it == move) {
                theLegalMoves.erase(it);
                break;
            } else {
                ++it;
            }
        }
    }
    if (isCheck) {
        return updateCheck(theLegalMoves);
    } else {
        return theLegalMoves;
    }
}

void Board::displayLegalMoves() {
    if (legalMoves.empty()) {
        legalMoves = calculateLegalMoves(true);
    }
    for (std::tuple move : legalMoves) {
        std::cout << std::get<0>(move) << " ";
    }
    std::cout << std::endl;
}

void Board::movingPiece(std::string move, std::pair<int, int> original, std::pair<int, int> target) {
    switch (move[move.size() - 1]) {
        case '+': {
            move.pop_back();
            break;
        }
    }
    if (move == "0-0-0") {
        if (whoseTurn == PieceColourType::WHITE) {
            whiteKing.first = target.first;
        } else {
            blackKing.first = target.first;
        }
        createPiece(grid[original.first][original.second], target);

        createPiece(std::make_shared<ChessPiece>(original, PieceColourType::UNASSIGNED), original);
        createPiece(grid[0][target.second], std::make_pair(3, target.second));
        grid[3][target.second]->increaseMoveCounter();
        std::pair<int, int> emptySquare = {0, original.second};
        createPiece(std::make_shared<ChessPiece>(emptySquare, PieceColourType::UNASSIGNED), emptySquare);
    } else if (move == "0-0") {
        if (whoseTurn == PieceColourType::WHITE) {
            whiteKing.first = target.first;
        } else {
            blackKing.first = target.first;
        }
        createPiece(grid[original.first][original.second], target);
        createPiece(std::make_shared<ChessPiece>(original, PieceColourType::UNASSIGNED), original);

        createPiece(grid[7][target.second], std::make_pair(5, target.second));
        grid[5][target.second]->increaseMoveCounter();
        std::pair<int, int> emptySquare = {7, original.second};
        createPiece(std::make_shared<ChessPiece>(emptySquare, PieceColourType::UNASSIGNED), emptySquare);
    } else if (move[move.size() - 2] == '=') {
        switch (move[move.size() - 1]) {
            case 'Q': {
                createPiece(std::make_shared<Queen>(target, grid[original.first][original.second]->getPieceColour()), target);
                break;
            }
            case 'R': {
                createPiece(std::make_shared<Rook>(target, grid[original.first][original.second]->getPieceColour()), target);
                break;
            }
            case 'B': {
                createPiece(std::make_shared<Bishop>(target, grid[original.first][original.second]->getPieceColour()), target);
                break;
            }
            case 'N': {
                createPiece(std::make_shared<Knight>(target, grid[original.first][original.second]->getPieceColour()), target);
                break;
            }
        }
        createPiece(std::make_shared<ChessPiece>(original, PieceColourType::UNASSIGNED), original);
    } else {
        if (grid[original.first][original.second]->getSymbol() == 'K') {
            if (whoseTurn == PieceColourType::WHITE) {
                whiteKing = target;
            } else {
                blackKing = target;
            }
        } else if (grid[original.first][original.second]->getSymbol() == 'P') {
            if (move.size() == 2) {  // normal pawn movement
                if (grid[original.first][original.second]->getMoveCounter() == 0 && abs(target.second - original.second) == 2) {
                    grid[original.first][original.second]->setEnPassant(true);
                }
            } else {
                if (grid[original.first][original.second]->spaceEmpty(grid, target)) {
                    target.second -= (whoseTurn == PieceColourType::WHITE) ? 1 : -1;
                    createPiece(std::make_shared<ChessPiece>(target, PieceColourType::UNASSIGNED), target);
                    target.second += (whoseTurn == PieceColourType::WHITE) ? 1 : -1;
                }
            }
        }

        createPiece(grid[original.first][original.second], target);
        createPiece(std::make_shared<ChessPiece>(original, PieceColourType::UNASSIGNED), original);
    }
    grid[target.first][target.second]->increaseMoveCounter();
}

void Board::undoMove() {
    try {
        if (listOfMoves.empty()) {
            throw std::logic_error("No moves to undo");
        }

        listOfMoves.pop_back();
        // deleteBoard();
        createBoard();
        PieceColourType colourTurn = whoseTurn;
        whoseTurn = PieceColourType::WHITE;
        std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> tempList = listOfMoves;
        for (const auto &moveInfo : tempList) {
            makeMove(moveInfo);
            listOfMoves.pop_back();
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

bool Board::makeMove(std::tuple<std::string, std::pair<int, int>, std::pair<int, int>> moveInfo) {
    std::string move;
    std::pair<int, int> original, target;
    tie(move, original, target) = moveInfo;
    bool plus = false, hash = false;
    isCheck = false;
    switch (move[move.size() - 1]) {
        case '+': {
            plus = true;
            break;
        }
        case '#': {
            hash = true;
            break;
        }
    }

    if (hash) {
        move.pop_back();
        move += '+';
        isCheckmate = true;
    }

    movingPiece(move, original, target);

    if (plus) {
        isCheck = true;
        // std::cout << "Check!" << std::endl;
    } else if (hash) {
        move.pop_back();
        move += '#';
    }

    if (std::get<0>(listOfMoves.back()).size() == 2) {
        grid[std::get<2>(listOfMoves.back()).first][std::get<2>(listOfMoves.back()).second]->setEnPassant(false);
    }

    listOfMoves.push_back(std::make_tuple(move, original, target));
    whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;

    if (!isCheck) {
        if (calculateLegalMoves(false).empty()) {
            std::cout << "Stalemate!" << std::endl;
            isCheckmate = true;
        }
    }
    return !isCheckmate;
}

void Board::createPiece(std::shared_ptr<ChessPiece> piece, std::pair<int, int> location) {
    grid[location.first][location.second] = piece;
    piece->setLocation(location);
}

/*void Board::removePiece(std::shared_ptr<ChessPiece> piece) {
    delete piece;
}*/

/*void Board::deleteBoard() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            removePiece(grid[i][j]);
        }
    }
}*/