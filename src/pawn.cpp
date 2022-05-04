#include "pawn.h"

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <tuple>
#include <utility>

#include "board.h"
#include "pieceColourType.h"

Pawn::Pawn(std::pair<int, int> square, PieceColourType colour) : ChessPiece(square, colour) {
    symbol = 'P';
}

std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> Pawn::possibleMoves(std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, bool second) {
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> whereMove;
    int start, end, neg;
    if (pieceColour == PieceColourType::WHITE) {
        start = 1;
        end = 7;
        neg = 1;
    } else {
        start = 6;
        end = 0;
        neg = -1;
    }
    std::pair<int, int> look = {location.first, location.second + neg * 1};
    std::pair<int, int> lookLeft;
    std::pair<int, int> lookRight;
    if (location.second != end) {
        if (spaceEmpty(grid, look)) {
            whereMove.push_back(std::make_tuple(constructMove(look, grid, false, second), location, look));
            look.second += neg * 1;
            if (location.second == start && spaceEmpty(grid, look)) {
                whereMove.push_back(std::make_tuple(constructMove(look, grid, false, second), location, look));
            }
            look.second -= neg * 1;
        }
        if (location.first != 0) {
            lookLeft = std::make_pair(look.first - 1, look.second);
            if (spaceEnemy(grid, lookLeft)) {
                whereMove.push_back(std::make_tuple(constructMove(lookLeft, grid, true, second), location, lookLeft));
            }
            lookLeft.second = lookLeft.second - neg * 1;
            if (spaceEnemy(grid, lookLeft) && grid[lookLeft.first][lookLeft.second]->getEnPassant()) {
                lookLeft.second = lookLeft.second + neg * 1;
                whereMove.push_back(std::make_tuple(constructMove(lookLeft, grid, true, second), location, lookLeft));
            }
        }
        if (location.first != 7) {
            lookRight = std::make_pair(look.first + 1, look.second);
            if (spaceEnemy(grid, lookRight)) {
                whereMove.push_back(std::make_tuple(constructMove(lookRight, grid, true, second), location, lookRight));
            }
            lookRight.second = lookRight.second - neg * 1;
            if (spaceEnemy(grid, lookRight) && grid[lookRight.first][lookRight.second]->getEnPassant()) {
                lookRight.second = lookRight.second + neg * 1;
                whereMove.push_back(std::make_tuple(constructMove(lookRight, grid, true, second), location, lookRight));
            }
        }
    }
    return whereMove;
}

std::string Pawn::constructMove(std::pair<int, int> look, std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, bool enemy, bool second) {
    std::string theMove = "";
    if (enemy) {
        theMove += char('a' + location.first);
        theMove += 'x';
    }
    theMove += char('a' + look.first);
    theMove += char('1' + look.second);

    int end = (pieceColour == PieceColourType::WHITE) ? 7 : 0;

    if (look.second == end) {
        theMove += "=Q";
        // theMove += "=R";
        // theMove += "=B";
        // theMove += "=N";
    }

    if (!second) {
        std::pair<int, int> tempLocation = location;
        location = look;
        std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> checkForCheck;

        if (theMove[theMove.size() - 2] != '=') {
            checkForCheck = possibleMoves(grid, true);
        } else {
            Board temp;
            temp.setGrid(grid);
            temp.setWhoseTurn(pieceColour);
            temp.movingPiece(theMove, tempLocation, location);
            std::vector<std::vector<std::shared_ptr<ChessPiece>>> tempGrid = temp.getGrid();
            tempGrid[location.first][location.second]->setPieceColour(pieceColour);
            PieceColourType colour = tempGrid[location.first][location.second]->getPieceColour();
            checkForCheck = tempGrid[location.first][location.second]->possibleMoves(tempGrid, true);
            // temp.deleteBoard();
        }
        for (std::tuple move : checkForCheck) {
            int square[2];
            if (std::get<0>(move)[std::get<0>(move).size() - 2] == '=') {
                square[0] = int(std::get<0>(move)[std::get<0>(move).size() - 4] - 'a');
                square[1] = int(std::get<0>(move)[std::get<0>(move).size() - 3] - '1');
            } else {
                square[0] = int(std::get<0>(move)[std::get<0>(move).size() - 2] - 'a');
                square[1] = int(std::get<0>(move)[std::get<0>(move).size() - 1] - '1');
            }
            if (grid[square[0]][square[1]]->getSymbol() == 'K' && grid[square[0]][square[1]]->getPieceColour() != pieceColour) {
                theMove += '+';
                break;
            }
        }
        location.first = tempLocation.first;
        location.second = tempLocation.second;
    }
    return theMove;
}