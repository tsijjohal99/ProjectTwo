#include "king.h"
#include "pieceColourType.h"

King::King(int square[2], PieceColourType colour) : Queen(square, colour) {
    symbol = (pieceColour == PieceColourType::WHITE) ? 'K' : 'k';
}

bool King::getHasMoved() {
    return hasMoved;
}

void King::setHasMoved(bool newMove) {
    hasMoved = newMove;
}

void King::checkCastle(std::vector<std::vector<bool>> &whereMove, std::vector<std::vector<ChessPiece*>> &grid) {
    if (!hasMoved) {
        int y;
        char rookSymbol;
        if (getPieceColour() == PieceColourType::WHITE) {
            y = 0;
            rookSymbol = 'R';
        } else {
            y = 7;
            rookSymbol = 'r';
        }
        if (grid[0][y]->getSymbol() == rookSymbol) {
            if (!grid[0][y]->getHasMoved() 
            && !hasMoved 
            && grid[1][y]->getPieceColour() == PieceColourType::UNASSIGNED
            && grid[2][y]->getPieceColour() == PieceColourType::UNASSIGNED
            && grid[3][y]->getPieceColour() == PieceColourType::UNASSIGNED) {
                whereMove[2][y] == true;
            }
        }
        if (grid[7][y]->getSymbol() == rookSymbol) {
            if (!grid[7][y]->getHasMoved() 
            && !hasMoved 
            && grid[6][y]->getPieceColour() == PieceColourType::UNASSIGNED
            && grid[5][y]->getPieceColour() == PieceColourType::UNASSIGNED) {
                whereMove[6][y] == true;
            }
        }
    }
}

std::vector<std::vector<bool>> King::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid) {
    std::vector<std::vector<bool>> whereMove = Queen::possibleMoves(grid);
    if (getSymbol() == 'K' || getSymbol() == 'k') {
        checkCastle(whereMove, grid);
    }
}