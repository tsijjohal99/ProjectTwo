#include "king.h"
#include "pieceColourType.h"
#include <list>

King::King(int square[2], PieceColourType colour) : Queen(square, colour) {
    symbol = 'K';
}

void King::checkCastle(std::list<std::string> &whereMove, std::vector<std::vector<ChessPiece*>> &grid) {
    if (!hasMoved) {
        char rookSymbol = 'R';
        int y = (getPieceColour() == PieceColourType::WHITE) ? 0 : 7;
        if (grid[0][y]->getSymbol() == rookSymbol) {
            if (!grid[0][y]->getHasMoved() 
            && grid[1][y]->getPieceColour() == PieceColourType::UNASSIGNED
            && grid[2][y]->getPieceColour() == PieceColourType::UNASSIGNED
            && grid[3][y]->getPieceColour() == PieceColourType::UNASSIGNED) { 
                whereMove.push_back("0-0-0");
            }
        }
        if (grid[7][y]->getSymbol() == rookSymbol) {
            if (!grid[7][y]->getHasMoved() 
            && grid[6][y]->getPieceColour() == PieceColourType::UNASSIGNED
            && grid[5][y]->getPieceColour() == PieceColourType::UNASSIGNED) {
                whereMove.push_back("0-0");
            }
        }
    }
}

std::list<std::string> King::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid) {
    std::list<std::string> whereMove = Queen::possibleMoves(grid);
    if (symbol == 'K') {
        checkCastle(whereMove, grid);
    }
    return whereMove;
}