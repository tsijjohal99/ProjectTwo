#include "knight.h"

#include <cmath>
#include <iostream>
#include <string>
#include <tuple>

#include "pieceColourType.h"

Knight::Knight(std::pair<int, int> square, PieceColourType colour) : ChessPiece(square, colour) {
    symbol = 'N';
}

std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> Knight::possibleMoves(std::vector<std::vector<ChessPiece *>> &grid, bool second) {
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> whereMove;
    for (int i = -2; i < 3; i++) {
        for (int j = -2; j < 3; j++) {
            std::pair<int, int> look = {location.first + i, location.second + j};
            if (pow(i, 2) + pow(j, 2) == 5 && look.first >= 0 && look.second >= 0 && look.first < 8 && look.second < 8) {
                if (Knight::spaceEmpty(grid, look)) {
                    whereMove.push_back(std::make_tuple(constructMove(look, grid, false, second), location, look));
                } else if (Knight::spaceEnemy(grid, look)) {
                    whereMove.push_back(std::make_tuple(constructMove(look, grid, true, second), location, look));
                }
            }
        }
    }
    return whereMove;
}

std::string Knight::constructMove(std::pair<int, int> look, std::vector<std::vector<ChessPiece *>> &grid, bool enemy, bool second) {
    std::string theMove = "";
    bool secondPiece = false;
    theMove += symbol;
    for (int i = -2; !secondPiece, i < 3; i++) {
        for (int j = -2; !secondPiece, j < 3; j++) {
            if (pow(i, 2) + pow(j, 2) == 5 && look.first + i >= 0 && look.second + j >= 0 && look.first + i < 8 && look.second + j < 8 && grid[look.first + i][look.second + j]->getPieceColour() == pieceColour && grid[look.first + i][look.second + j]->getSymbol() == symbol && look.first + i != location.first && look.second + j != location.second) {
                if (location.first == look.first + i) {
                    theMove += char('1' + location.second);
                } else {
                    theMove += char('a' + location.first);
                }
                secondPiece = true;
            }
        }
    }
    if (enemy) {
        theMove += 'x';
    }
    theMove += char('a' + look.first);
    theMove += char('1' + look.second);
    if (!second) {
        std::pair<int, int> tempLocation = location;
        location = look;
        std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> checkForCheck = possibleMoves(grid, true);
        for (std::tuple move : checkForCheck) {
            int square[] = {int(std::get<0>(move)[std::get<0>(move).size() - 2] - 'a'), int(std::get<0>(move)[std::get<0>(move).size() - 1] - '1')};
            if (grid[square[0]][square[1]]->getSymbol() == 'K' && grid[square[0]][square[1]]->getPieceColour() != pieceColour) {
                theMove += '+';
            }
        }
        location = tempLocation;
    }
    return theMove;
}