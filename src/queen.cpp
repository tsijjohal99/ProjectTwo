#include "queen.h"

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "pieceColourType.h"

Queen::Queen(std::pair<int, int> square, PieceColourType colour) : ChessPiece(square, colour) {
    symbol = 'Q';
    maxMovement = 8;
}

std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> Queen::slide(std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, int direction[], bool second) {
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> whereMove;
    std::pair<int, int> look = location;
    for (int i = 1; location.first + i * direction[0] < 8 && location.first + i * direction[0] >= 0 && location.second + i * direction[1] < 8 && location.second + i * direction[1] >= 0 && i < maxMovement; i++) {
        look.first = location.first + i * direction[0];
        look.second = location.second + i * direction[1];
        if (ChessPiece::spaceEmpty(grid, look)) {
            bool kissingKings = false;
            if (symbol == 'K' && !second) {
                std::pair<int, int> tempLocation = location;
                location = look;
                std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> checkForKissingKings = possibleMoves(grid, true);
                for (std::tuple move : checkForKissingKings) {
                    if (std::get<0>(move) != "0-0" && std::get<0>(move) != "0-0-0") {
                        int square[] = {int(std::get<0>(move)[std::get<0>(move).size() - 2] - 'a'), int(std::get<0>(move)[std::get<0>(move).size() - 1] - '1')};
                        if (grid[square[0]][square[1]]->getSymbol() == 'K' && grid[square[0]][square[1]]->getPieceColour() != pieceColour) {
                            kissingKings = true;
                        }
                    }
                }
                location = tempLocation;
            }
            if (!kissingKings) {
                whereMove.push_back(std::make_tuple(constructMove(look, grid, false, second), location, look));
            }
        } else if (ChessPiece::spaceEnemy(grid, look)) {
            whereMove.push_back(std::make_tuple(constructMove(look, grid, true, second), location, look));
            break;
        } else {
            break;
        }
    }
    return whereMove;
}

std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> Queen::possibleMoves(std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, bool second) {
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> whereMove;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i != 0 || j != 0) {
                int direction[] = {i, j};
                if ((i == -j || i == j) && symbol != 'R') {
                    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> moves = slide(grid, direction, second);
                    whereMove.insert(whereMove.end(), moves.begin(), moves.end());
                } else if (i != j && symbol != 'B') {
                    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> moves = slide(grid, direction, second);
                    whereMove.insert(whereMove.end(), moves.begin(), moves.end());
                }
            }
        }
    }

    return whereMove;
}

bool Queen::constructMoveSlide(std::string &theMove, std::pair<int, int> look, std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, int direction[]) {
    for (int i = 1; look.first + i * direction[0] < 8 && look.first + i * direction[0] >= 0 && look.second + i * direction[1] < 8 && look.second + i * direction[1] >= 0 && i < maxMovement; i++) {
        if (grid[look.first + i * direction[0]][look.second + i * direction[1]]->getPieceColour() == pieceColour && grid[look.first + i * direction[0]][look.second + i * direction[1]]->getSymbol() == symbol && (look.first + i * direction[0] != location.first && look.second + i * direction[1] != location.second)) {
            if (look.first == location.first) {
                theMove += char('a' + location.first);
            } else {
                theMove += char('1' + location.second);
            }
            return true;
        }
    }
    return false;
}

std::string Queen::constructMove(std::pair<int, int> look, std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, bool enemy, bool second) {
    std::string theMove = "";
    bool foundSecond = false;
    theMove += symbol;
    for (int i = -1; !foundSecond && i < 2; i++) {
        for (int j = -1; !foundSecond && j < 2; j++) {
            if ((i != 0 || j != 0) && !foundSecond) {  // XOR
                int direction[] = {i, j};
                if ((i == -j || i == j) && symbol != 'R') {
                    foundSecond = constructMoveSlide(theMove, look, grid, direction);
                } else if (i != j && symbol != 'B') {
                    foundSecond = constructMoveSlide(theMove, look, grid, direction);
                }
            }
        }
    }
    if (enemy) {
        theMove += 'x';
    }
    theMove += char('a' + look.first);
    theMove += char('1' + look.second);
    if (!second && symbol != 'K') {
        std::pair<int, int> tempLocation = location;
        location = look;
        std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> checkForCheck = possibleMoves(grid, true);
        for (std::tuple move : checkForCheck) {
            if (std::get<0>(move) != "0-0" && std::get<0>(move) != "0-0-0") {
                int square[] = {int(std::get<0>(move)[std::get<0>(move).size() - 2] - 'a'), int(std::get<0>(move)[std::get<0>(move).size() - 1] - '1')};
                if (grid[square[0]][square[1]]->getSymbol() == 'K' && grid[square[0]][square[1]]->getPieceColour() != pieceColour) {
                    theMove += '+';
                }
            }
        }
        location = tempLocation;
    }
    return theMove;
}