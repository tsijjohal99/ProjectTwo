#include <iostream>
#include "board.h"
#include "pieceColourType.h"

void createNewGame() {
    Board game;
    bool playGame = true;
    while (playGame) {
        std::cout << "" << std::endl;
        game.displayBoard();
        std::cout << "" << std::endl;
        if (game.getWhoseTurn() == PieceColourType::WHITE) {
            std::cout << "White's Turn" << std::endl;
        } else {
            std::cout << "Black's Turn" << std::endl;
        }
        std::cout << "Please enter a legal move." << std::endl;
        std::cout << "Press 1 to list the possible moves. " << std::endl;
        std::cout << "Press 2 to undo the previous move." << std::endl;
        std::cout << "Press 3 to display all moves made." << std::endl;
        std::cout << "Press 0 to quit game. " << std::endl;
        std::string input;
        std::cin >> input;
        try {
            if (input == "0") {
                playGame = false;
                system("cls");
            } else if (input == "1") {
                system("cls");
                game.displayLegalMoves();
            } else if (input == "2") {
                system("cls");
                game.undoMove();
            } else if (input == "3") {
                system("cls");
                game.displayMovesMade();
            } else {
                system("cls");
                playGame = game.makeMove(input);
            }
        } catch (const std::overflow_error& e) {}
        catch (const std::runtime_error& e) {}
        catch (const std::exception& e) {}
        catch (...) {}
    }
    game.deleteBoard();
}

bool displayMenu() {
    char menuChoice;
    std::cout << "Welcome to Jeevan's Chess Simulator!" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Press a key to continue." << std::endl;
    std::cout << "1. Play a new game." << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cin >> menuChoice;
    switch (menuChoice) {
        case '1': {
            system("cls");
            createNewGame();
            break;
        }
        case '2': {
            return false;
        }
        default: {
            system("cls");
            std::cout << "Oh no, that didn't compute, try inputting something useful." << std::endl;
        }
    }
    return true;
}

int main() {
    std::cout << std::unitbuf;

    bool menu = true;
    while (menu) {
        menu = displayMenu();
    }
    return 0;
}