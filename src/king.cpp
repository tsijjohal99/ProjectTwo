#include "king.h"

#include <list>
#include <memory>
#include <string>
#include <tuple>

#include "pieceColourType.h"

King::King(std::pair<int, int> square, PieceColourType colour) : Queen(square, colour) {
    symbol = 'K';
    maxMovement = 2;
}

void King::checkCastle(std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> &whereMove, std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid) {
    if (moveCounter == 0) {
        int y = (getPieceColour() == PieceColourType::WHITE) ? 0 : 7;
        if (grid[0][y]->getSymbol() == 'R') {
            if (grid[0][y]->getMoveCounter() == 0 && grid[1][y]->getPieceColour() == PieceColourType::UNASSIGNED && grid[2][y]->getPieceColour() == PieceColourType::UNASSIGNED && grid[3][y]->getPieceColour() == PieceColourType::UNASSIGNED) {
                whereMove.push_back(std::make_tuple("0-0-0", location, std::make_pair(2, y)));
            }
        }
        if (grid[7][y]->getSymbol() == 'R') {
            if (grid[7][y]->getMoveCounter() == 0 && grid[6][y]->getPieceColour() == PieceColourType::UNASSIGNED && grid[5][y]->getPieceColour() == PieceColourType::UNASSIGNED) {
                whereMove.push_back(std::make_tuple("0-0", location, std::make_pair(6, y)));
            }
        }
    }
}

std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> King::possibleMoves(std::vector<std::vector<std::shared_ptr<ChessPiece>>> &grid, bool second) {
    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> whereMove = Queen::possibleMoves(grid, second);
    if (symbol == 'K') {
        checkCastle(whereMove, grid);
    }

    return whereMove;
}