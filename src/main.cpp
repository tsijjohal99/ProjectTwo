#include <iostream>
#include "board.h"

void createNewGame() {
    Board game;
    bool playGame = true;
    while (playGame) {
        std::cout << "" << std::endl;
        game.displayBoard();
        std::cout << "" << std::endl;
        std::cout << "Please enter a legal move or 0 to quit game. " << std::endl;
        std::string input;
        std::cin >> input;
        if (input == "0") {
            playGame = false;
            break;
        } else {
            system("cls");
            game.makeMove(input);
        }
    }
    game.deleteBoard();
}

bool displayMenu() {
    system("cls");
    char menuChoice;
    std::cout << "Welcome to Jeevan's Chess Simulator!" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Press a key to continue." << std::endl;
    std::cout << "1. Play a new game." << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cin >> menuChoice;
    switch (menuChoice) {
        case '1': {
            createNewGame();
            break;
        }
        case '2': {
            return false;
        }
        default: {
            std::cout << "Oh no, that didn't compute, try inputting something useful." << std::endl;
        }
    }
    return true;
}

int main() {
    bool menu = true;
    while (menu) {
        menu = displayMenu();
    }
    return 0;
}