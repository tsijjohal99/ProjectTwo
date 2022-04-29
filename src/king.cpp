#include "king.h"

#include <list>
#include <string>

#include "pieceColourType.h"

King::King(int square[2], PieceColourType colour) : Queen(square, colour) {
    symbol = 'K';
    maxMovement = 2;
}

void King::checkCastle(std::list<std::string> &whereMove, std::vector<std::vector<ChessPiece *>> &grid) {
    if (moveCounter == 0) {
        int y = (getPieceColour() == PieceColourType::WHITE) ? 0 : 7;
        if (grid[0][y]->getSymbol() == 'R') {
            if (grid[0][y]->getMoveCounter() == 0 && grid[1][y]->getPieceColour() == PieceColourType::UNASSIGNED && grid[2][y]->getPieceColour() == PieceColourType::UNASSIGNED && grid[3][y]->getPieceColour() == PieceColourType::UNASSIGNED) {
                whereMove.push_back("0-0-0");
            }
        }
        if (grid[7][y]->getSymbol() == 'R') {
            if (grid[7][y]->getMoveCounter() == 0 && grid[6][y]->getPieceColour() == PieceColourType::UNASSIGNED && grid[5][y]->getPieceColour() == PieceColourType::UNASSIGNED) {
                whereMove.push_back("0-0");
            }
        }
    }
}

std::list<std::string> King::possibleMoves(std::vector<std::vector<ChessPiece *>> &grid, bool second) {
    std::list<std::string> whereMove = Queen::possibleMoves(grid, second);
    if (symbol == 'K') {
        checkCastle(whereMove, grid);
    }

    return whereMove;
}