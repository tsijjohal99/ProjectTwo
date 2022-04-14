
#include "pawn.h"
#include "pieceColourType.h"
#include <list>

Pawn::Pawn(int square[2], PieceColourType colour) : ChessPiece(square, colour) {
    symbol = 'P';
}

std::list<std::string> Pawn::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid) {
    std::list<std::string> whereMove;
    int start, end, neg;
    if (getPieceColour() == PieceColourType::WHITE) {
        start = 1;
        end = 7;
        neg = 1;
    } else {
        start = 6;
        end = 0;
        neg = -1;
    }
    int look[] = {getLocation()[0], getLocation()[1] + neg*1};
    int lookLeft[2];
    int lookRight[2];
    if (getLocation()[1] != end) {
        if (spaceEmpty(grid, look)) {
            whereMove.push_back(constructMoveEmpty(look));
            promotion(look, end, whereMove, constructMoveEmpty(look));
            look[1] += neg*1;
            if (getLocation()[1] == start || spaceEmpty(grid, look)) {
                promotion(look, end, whereMove, constructMoveEmpty(look));
            }
            look[1] -= neg*1;
        }
        if (getLocation()[0] > 0) {
            lookLeft[0] = look[0] - 1;
            lookLeft[1] = look[1];
            if (spaceEnemy(grid, lookLeft)) {
                promotion(look, end, whereMove, constructMoveEnemy(lookLeft));
            }
            if (spaceEnemy(grid, lookLeft) && grid[lookLeft[0]][lookLeft[1] - neg*1]->getEnPassant()) {
                promotion(look, end, whereMove, constructMoveEnemy(lookLeft));
            }
        }
        if (getLocation()[0] < 7) {
            lookRight[0] = look[0] + 1;
            lookRight[1] = look[1];
            if (spaceEnemy(grid, lookRight)) {
                promotion(look, end, whereMove, constructMoveEnemy(lookRight));
            }
            if (spaceEnemy(grid, lookRight) && grid[lookRight[0]][lookRight[1] - neg*1]->getEnPassant()) {
                promotion(look, end, whereMove, constructMoveEnemy(lookRight));
            }
        }
    }
    return whereMove;
}

std::string Pawn::constructMoveEmpty(int look[]) {
    std::string theMove = "";
    theMove.push_back(char('a' + look[0]));
    theMove.push_back(char(look[1] + 1));
    return theMove;
}

std::string Pawn::constructMoveEnemy(int look[]) {
    std::string theMove = "";
    theMove.push_back(char(location[0] + 'a'));
    theMove.push_back('x');
    theMove.push_back(char('a' + look[0]));
    theMove.push_back(char(look[1] + 1));
    return theMove;
}

void Pawn::promotion(int look[], int end, std::list<std::string> &whereMove, std::string move) {
    if (look[1] == end) {
        whereMove.push_back(move + '=' + 'Q');
        whereMove.push_back(move + '=' + 'B');
        whereMove.push_back(move + '=' + 'R');
        whereMove.push_back(move + '=' + 'N');
    } else {
        whereMove.push_back(move);
    }
}