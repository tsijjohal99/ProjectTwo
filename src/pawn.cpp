#include "pawn.h"
#include "pieceColourType.h"
#include "board.h"
#include <list>
#include <string>

Pawn::Pawn(int square[2], PieceColourType colour) : ChessPiece(square, colour) {
    symbol = 'P';
}

std::list<std::string> Pawn::possibleMoves(std::vector<std::vector<ChessPiece*>> &grid, bool second) {
    std::list<std::string> whereMove;
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
    int look[] = {location[0], location[1] + neg*1};
    int lookLeft[2];
    int lookRight[2];
    if (location[1] != end) {
        if (spaceEmpty(grid, look)) {
            whereMove.push_back(constructMove(look, grid, false, second));
            look[1] += neg*1;
            if (location[1] == start && spaceEmpty(grid, look)) {
                whereMove.push_back(constructMove(look, grid, false, second));
            }
            look[1] -= neg*1;
        }
        if (location[0] > 0) {
            lookLeft[0] = look[0] - 1;
            lookLeft[1] = look[1];
            if (spaceEnemy(grid, lookLeft)) {
                whereMove.push_back(constructMove(lookLeft, grid, true, second));
            }
            if (spaceEnemy(grid, lookLeft) && grid[lookLeft[0]][lookLeft[1] - neg*1]->getEnPassant()) {
                whereMove.push_back(constructMove(lookLeft, grid, true, second));
            }
        }
        if (location[0] < 7) {
            lookRight[0] = look[0] + 1;
            lookRight[1] = look[1];
            if (spaceEnemy(grid, lookRight)) {
                whereMove.push_back(constructMove(lookRight, grid, true, second));
            }
            if (spaceEnemy(grid, lookRight) && grid[lookRight[0]][lookRight[1] - neg*1]->getEnPassant()) {
                whereMove.push_back(constructMove(lookRight, grid, true, second));
            }
        }
    }
    return whereMove;
}

std::string Pawn::constructMove(int look[], std::vector<std::vector<ChessPiece*>> &grid, bool enemy, bool second) {
    std::string theMove = "";
    if (enemy) {
        theMove += char('a' + location[0]);
        theMove += 'x';
    }
    theMove += char('a' + look[0]);
    theMove += char('1' + look[1]);
    
    int end = (pieceColour == PieceColourType::WHITE) ? 7 : 0;

    if (look[1] == end) {
        theMove += "=Q";
        //theMove += "=R";
        //theMove += "=B";
        //theMove += "=N";
    }

    if (!second) {
        int tempLocation[] = {location[0], location[1]};
        location[0] = look[0];
        location[1] = look[1];
        std::list<std::string> checkForCheck;

        if (theMove[theMove.size() - 2] != '=') {
            checkForCheck = possibleMoves(grid, true);
        } else {
            Board temp;
            temp.setGrid(grid);
            temp.setWhoseTurn(pieceColour);
            temp.movingPiece(theMove, tempLocation[0], tempLocation[1]);
            std::vector<std::vector<ChessPiece*>> tempGrid = temp.getGrid();
            tempGrid[location[0]][location[1]]->setPieceColour(pieceColour);
            PieceColourType colour = tempGrid[location[0]][location[1]]->getPieceColour();
            checkForCheck = tempGrid[location[0]][location[1]]->possibleMoves(tempGrid, true);
            temp.deleteBoard();
        }
        for (std::string move : checkForCheck) {
            int square[2];
            if (move[move.size() - 2] == '=') {
                square[0] = int(move[move.size() - 4] - 'a');
                square[1] = int(move[move.size() - 3] - '1');
            } else {
                square[0] = int(move[move.size() - 2] - 'a');
                square[1] = int(move[move.size() - 1] - '1');
            }
            if (grid[square[0]][square[1]]->getSymbol() == 'K' && grid[square[0]][square[1]]->getPieceColour() != pieceColour) {
                theMove += '+';
                break;
            }
        }
        location[0] = tempLocation[0];
        location[1] = tempLocation[1];
    }
    return theMove;
}