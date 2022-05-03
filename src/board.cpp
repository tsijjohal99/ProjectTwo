#include "board.h"

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
    grid.resize(boardSize, std::vector<ChessPiece *>(boardSize));
    createBoard();
    whoseTurn = PieceColourType::WHITE;
}

int Board::getBoardSize() {
    return boardSize;
}

std::vector<std::vector<ChessPiece *>> &Board::getGrid() {
    return grid;
}

PieceColourType Board::getWhoseTurn() {
    return whoseTurn;
}

bool Board::getIsCheck() {
    return isCheck;
}

int *Board::getBlackKing() {
    return blackKing;
}

int *Board::getWhiteKing() {
    return whiteKing;
}

void Board::setBoardSize(int size) {
    boardSize = size;
}

void Board::setGrid(std::vector<std::vector<ChessPiece *>> theGrid) {
    grid == theGrid;
}

void Board::setWhoseTurn(PieceColourType colour) {
    whoseTurn = colour;
}

void Board::setIsCheck(bool check) {
    isCheck = check;
}

void Board::addMove(std::string move) {
    movesMade.push_back(move);
}

void Board::createBoard() {
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
    for (std::string move : movesMade) {
        if (i % 2 != 0) {
            std::cout << (i + 1) / 2 << ". ";
        }
        std::cout << move << " ";
        if (i % 2 == 0) {
            std::cout << "." << std::endl;
        }
        i++;
    }
}

std::list<std::string> Board::updateCheck(std::list<std::string> theLegalMoves) {
    std::list<std::string> movesToRemove;
    for (std::string myMove : theLegalMoves) {
        findPiece(myMove);
        movesMade.push_back(myMove);
        whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
        isCheck = false;
        std::list<std::string> oppositionLegalMoves = legalMoves(false);
        whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
        isCheck = true;
        for (std::string aMove : oppositionLegalMoves) {
            bool remove = false;
            if (int(aMove[aMove.size() - 2] - 'a') == whiteKing[0] && int(aMove[aMove.size() - 1] - '1') == whiteKing[1] && whoseTurn == PieceColourType::WHITE) {
                remove = true;
            } else if (int(aMove[aMove.size() - 2] - 'a') == blackKing[0] && int(aMove[aMove.size() - 1] - '1') == blackKing[1] && whoseTurn == PieceColourType::BLACK) {
                remove = true;
            }
            if (remove) {
                movesToRemove.push_back(myMove);
            }
        }
        whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
        undoMove();
    }
    for (std::string move : movesToRemove) {
        std::list<std::string>::iterator it = theLegalMoves.begin();
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
    std::list<std::string> withoutCheck = legalMoves(false);
    isCheck = true;
    std::list<std::string> withCheck = updateCheck(withoutCheck);  // this line is messing up somehow
    whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
    isCheck = checkTemp;
    return (withCheck.size() < withoutCheck.size());
}

bool Board::checkCheckmate() {
    bool checkTemp = isCheck;
    whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
    std::list<std::string> withoutCheck = legalMoves(false);
    isCheck = true;
    std::list<std::string> withCheck = updateCheck(withoutCheck);  // this line is messing up somehow
    whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
    isCheck = checkTemp;
    return (withCheck.size() == 0);
}

std::list<std::string> Board::legalMoves(bool first) {
    std::list<std::string> movesToRemove;
    std::list<std::string> theLegalMoves;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (grid[i][j]->getPieceColour() == whoseTurn) {
                std::list<std::string> theMoves = grid[i][j]->possibleMoves(grid, false);
                for (std::string move : theMoves) {
                    if (move[move.size() - 1] == '+' && first) {
                        movingPiece(move, i, j);
                        movesMade.push_back(move);
                        if (checkCheckmate()) {
                            movesToRemove.push_back(move);
                            move.pop_back();
                            move += '#';
                            theLegalMoves.push_back(move);
                        }
                        whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
                        undoMove();
                    }
                }
                theLegalMoves.insert(theLegalMoves.end(), theMoves.begin(), theMoves.end());
            }
        }
    }
    for (std::string move : movesToRemove) {
        std::list<std::string>::iterator it = theLegalMoves.begin();
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
    std::list<std::string> theLegalMoves = legalMoves(true);
    for (std::string move : theLegalMoves) {
        std::cout << move << " ";
    }
    std::cout << std::endl;
}

void Board::findPiece(std::string move) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (grid[i][j]->getPieceColour() == whoseTurn) {
                std::list<std::string> theMoves = grid[i][j]->possibleMoves(grid, false);
                std::list<std::string>::iterator it2;
                it2 = std::find(theMoves.begin(), theMoves.end(), move);
                if (it2 != theMoves.end()) {
                    movingPiece(move, i, j);
                }
            }
        }
    }
}

void Board::movingPiece(std::string move, int i, int j) {
    switch (move[move.size() - 1]) {
        case '+': {
            move.pop_back();
            break;
        }
    }
    if (move == "0-0-0") {
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
        createPiece(grid[4][j], 2, j);
        grid[2][j]->increaseMoveCounter();
        int square[2] = {4, j};
        createPiece(new ChessPiece(square, PieceColourType::UNASSIGNED), 4, j);
        createPiece(grid[0][j], 3, j);
        grid[3][j]->increaseMoveCounter();
        square[0] = 0;
        createPiece(new ChessPiece(square, PieceColourType::UNASSIGNED), 0, j);

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
        createPiece(grid[4][j], 6, j);
        grid[6][j]->increaseMoveCounter();
        int square[2] = {4, j};
        createPiece(new ChessPiece(square, PieceColourType::UNASSIGNED), 4, j);
        createPiece(grid[7][j], 5, j);
        grid[5][j]->increaseMoveCounter();
        square[0] = 7;
        createPiece(new ChessPiece(square, PieceColourType::UNASSIGNED), 7, j);
    } else if (move[move.size() - 2] == '=') {
        int look[] = {int(move[move.size() - 4] - 'a'), int(move[move.size() - 3] - '1')};
        switch (move[move.size() - 1]) {
            case 'Q': {
                createPiece(new Queen(look, grid[i][j]->getPieceColour()), look[0], look[1]);
                break;
            }
            case 'R': {
                createPiece(new Rook(look, grid[i][j]->getPieceColour()), look[0], look[1]);
                break;
            }
            case 'B': {
                createPiece(new Bishop(look, grid[i][j]->getPieceColour()), look[0], look[1]);
                break;
            }
            case 'N': {
                createPiece(new Knight(look, grid[i][j]->getPieceColour()), look[0], look[1]);
                break;
            }
        }
        grid[look[0]][look[1]]->increaseMoveCounter();
        int originalLocation[] = {i, j};
        createPiece(new ChessPiece(originalLocation, PieceColourType::UNASSIGNED), i, j);
    } else {
        int look[] = {int(move[move.size() - 2] - 'a'), int(move[move.size() - 1] - '1')};
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
        } else if (grid[i][j]->getSymbol() == 'P') {
            if (move.size() == 2) {  // normal pawn movement
                if (grid[i][j]->getMoveCounter() == 0 && (look[1] == 3 || look[1] == 4)) {
                    grid[i][j]->setEnPassant(true);
                }
            } else {
                if (grid[i][j]->spaceEmpty(grid, look)) {
                    look[1] -= (grid[i][j]->getPieceColour() == PieceColourType::WHITE) ? 1 : -1;
                    createPiece(new ChessPiece(look, PieceColourType::UNASSIGNED), look[0], look[1]);
                    look[1] += (grid[i][j]->getPieceColour() == PieceColourType::WHITE) ? 1 : -1;
                }
            }
        }

        createPiece(grid[i][j], look[0], look[1]);
        grid[look[0]][look[1]]->increaseMoveCounter();
        int square[] = {i, j};
        createPiece(new ChessPiece(square, PieceColourType::UNASSIGNED), i, j);
    }
}

void Board::undoMove() {
    try {
        std::string moveToRemove = movesMade.back();
        if (moveToRemove.empty()) {
            throw std::logic_error("No moves to undo");
        }

        switch (moveToRemove[moveToRemove.size() - 1]) {
            case '+': {
                moveToRemove.pop_back();
                break;
            }
            case '#': {
                moveToRemove.pop_back();
                break;
            }
        }

        if (moveToRemove == "0-0") {
            grid[5][whoseTurn == PieceColourType::WHITE ? 7 : 0]->decreaseMoveCounter();
            grid[6][whoseTurn == PieceColourType::WHITE ? 7 : 0]->decreaseMoveCounter();
        } else if (movesMade.back() == "0-0-0") {
            grid[2][whoseTurn == PieceColourType::WHITE ? 7 : 0]->decreaseMoveCounter();
            grid[3][whoseTurn == PieceColourType::WHITE ? 7 : 0]->decreaseMoveCounter();
        } else if (char(moveToRemove[moveToRemove.size() - 2]) == '=') {
            grid[int(moveToRemove[moveToRemove.size() - 4] - 'a')][int(moveToRemove[moveToRemove.size() - 3] - '1')]->decreaseMoveCounter();
        } else {
            grid[int(moveToRemove[moveToRemove.size() - 2] - 'a')][int(moveToRemove[moveToRemove.size() - 1] - '1')]->decreaseMoveCounter();
        }

        movesMade.pop_back();
        deleteBoard();
        createBoard();
        PieceColourType colourTurn = whoseTurn;
        whoseTurn = PieceColourType::WHITE;
        for (std::string move : movesMade) {
            findPiece(move);
            whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
        }
        whoseTurn = (colourTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;
        if (isCheck) {
            isCheck = false;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

bool Board::makeMove(std::string move) {
    bool plus = false, hash = false;
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
    bool moveCompleted = false;

    if (hash) {
        move.pop_back();
        move += '+';
    }

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (grid[i][j]->getPieceColour() == whoseTurn && !moveCompleted) {
                std::list<std::string> theMoves = grid[i][j]->possibleMoves(grid, false);
                std::list<std::string>::iterator it2;
                it2 = std::find(theMoves.begin(), theMoves.end(), move);

                if (it2 != theMoves.end()) {
                    isCheck = false;

                    if (hash) {
                        isCheckmate = true;
                        std::cout << "Checkmate!" << std::endl;
                    }

                    movingPiece(move, i, j);

                    if (plus) {
                        isCheck = true;
                        std::cout << "Check!" << std::endl;
                    }

                    moveCompleted = true;

                    if (movesMade.back().size() == 2) {
                        grid[int(movesMade.back()[0] - 'a')][int(movesMade.back()[1] - '1')]->setEnPassant(false);
                    }
                }
            }
        }
    }
    movesMade.push_back(move);
    whoseTurn = (whoseTurn == PieceColourType::WHITE) ? PieceColourType::BLACK : PieceColourType::WHITE;

    if (!isCheck) {
        if (legalMoves(false).empty()) {
            std::cout << "Stalemate!" << std::endl;
            isCheckmate = true;
        }
    }
    return !isCheckmate;
}

void Board::createPiece(ChessPiece *piece, int a, int b) {
    grid[a][b] = &*piece;
    piece->setLocation(a, b);
}

void Board::removePiece(ChessPiece *piece) {
    delete piece;
}

void Board::deleteBoard() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            removePiece(grid[i][j]);
        }
    }
}