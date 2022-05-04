#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "board.h"
#include "chessPiece.h"
#include "config.h"
#include "pieceColourType.h"

#define TILE_MAP_SIZE 8

void resize_sprite(sf::Sprite& piece_sprite, int width, int height) {
    auto size = piece_sprite.getTexture()->getSize();
    piece_sprite.setScale((float)width / size.x, (float)height / size.y);
}

int main(int argc, char* argv[]) {
    Board game;
    bool playGame = true;
    const int tile_size = 64;
    const int window_size = game.getBoardSize() * tile_size;
    int c_tile_size = 64;
    int c_window_size = game.getBoardSize() * c_tile_size;
    int r_tile_size = 64;
    int r_window_size = game.getBoardSize() * r_tile_size;

    sf::RenderWindow window(
        sf::VideoMode(c_window_size, r_window_size), "Wicked Chess Game");

    const std::string tile_dir = "resources/tiles/";
    std::map<char, sf::Texture> while_tile_texture_map{};
    std::map<char, sf::Texture> black_tile_texture_map{};

    sf::Texture white_bg;
    sf::Texture black_bg;

    white_bg.loadFromFile(tile_dir + "w.png");
    black_bg.loadFromFile(tile_dir + "b.png");

    const std::vector<char> tiles = {'R', 'N', 'B', 'Q', 'K', 'P'};

    for (const auto& tile : tiles) {
        sf::Texture white_texture;
        sf::Texture black_texture;

        auto tile_path = [&tile_dir, &tile](const std::string& colour) {
            return tile_dir + colour + '/' + tile + ".png";
        };

        white_texture.loadFromFile(tile_path("white"));
        black_texture.loadFromFile(tile_path("black"));

        while_tile_texture_map.insert({tile, white_texture});
        black_tile_texture_map.insert({tile, black_texture});
    }

    // ChessPiece* selected_piece{};
    std::pair<int, int> clicked_pos{};
    bool piece_is_selected{false};

    std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> posssible_moves_with_check;

    while (window.isOpen() & playGame) {
        sf::Event Event;
        // bool clicked{false};

        while (window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                window.close();

            /*if (Event.type == sf::Event::Resized) {
                    sf::Vector2u size = window.getSize();
                    unsigned int width = 64 * int(size.x / 64);
                    unsigned int height = 64 * int(size.y / 64);
                    sf::Style::Resize(width, height);
                    c_tile_size = width / game.getBoardSize();
                    r_tile_size = height / game.getBoardSize();
            }*/

            if (Event.type == sf::Event::KeyPressed) {
                if (Event.key.code == sf::Keyboard::Escape) {
                    piece_is_selected = false;
                    posssible_moves_with_check.clear();
                } else if (Event.key.code == sf::Keyboard::Left) {
                    game.undoMove();
                    piece_is_selected = false;
                    posssible_moves_with_check.clear();
                }
            }

            if (Event.type == sf::Event::MouseButtonPressed) {
                if (Event.mouseButton.button == sf::Mouse::Left) {
                    // std::cout << "mouse x: " << Event.mouseButton.x << std::endl;
                    // std::cout << "mouse y: " << Event.mouseButton.y << std::endl;

                    // std::cout << "col: " << int(Event.mouseButton.x / tile_size) << std::endl;
                    // std::cout << "row: " << game.getBoardSize() - 1 -int(Event.mouseButton.y / tile_size) << std::endl;

                    if (!piece_is_selected) {
                        bool check = game.getIsCheck();

                        clicked_pos.first = Event.mouseButton.x / tile_size;
                        clicked_pos.second = game.getBoardSize() - 1 - int(Event.mouseButton.y / tile_size);

                        piece_is_selected = true;
                        ChessPiece* selected_piece = game.getGrid()[clicked_pos.first][clicked_pos.second];
                        // std::cout << "piece clicked: " << chess_piece->getSymbol() << std::endl;
                        // const std::string colour = (chess_piece->getPieceColour() == PieceColourType::WHITE) ? "white" : "black";
                        // std::cout << "colour clicked: " << colour << std::endl;

                        if (selected_piece->getPieceColour() == game.getWhoseTurn()) {
                            std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> posssible_moves = selected_piece->possibleMoves(game.getGrid(), false);
                            // std::list<std::tuple<std::string, std::pair<int, int>, std::pair<int, int>>> posssible_moves_with_check;

                            for (const auto& move : posssible_moves) {
                                std::string updatedMove;
                                std::pair<int, int> original, target;
                                tie(updatedMove, original, target) = move;

                                if (updatedMove[updatedMove.size() - 1] == '+') {
                                    game.movingPiece(updatedMove, original, target);
                                    game.addMove(move);
                                    if (game.checkCheckmate()) {
                                        updatedMove.pop_back();
                                        updatedMove += '#';
                                    }
                                    game.setWhoseTurn(game.getWhoseTurn() == PieceColourType::WHITE ? PieceColourType::BLACK : PieceColourType::WHITE);
                                    game.undoMove();
                                }

                                posssible_moves_with_check.push_back(std::make_tuple(updatedMove, original, target));
                            }

                            if (game.getIsCheck()) {
                                posssible_moves_with_check = game.updateCheck(posssible_moves_with_check);
                            }
                        }
                        game.setIsCheck(check);

                        // delete selected_piece;

                    } else {
                        std::pair<int, int> new_clicked_pos{};

                        new_clicked_pos.first = Event.mouseButton.x / tile_size;
                        new_clicked_pos.second = game.getBoardSize() - 1 - int(Event.mouseButton.y / tile_size);

                        for (const auto moveInfo : posssible_moves_with_check) {
                            if (new_clicked_pos == std::get<2>(moveInfo)) {
                                playGame = game.makeMove(moveInfo);

                                break;
                            }
                        }
                        posssible_moves_with_check.clear();
                        piece_is_selected = false;
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        for (int r = 0; r < game.getBoardSize(); r++) {
            for (int c = 0; c < game.getBoardSize(); c++) {
                ChessPiece* chess_piece = game.getGrid()[c][game.getBoardSize() - 1 - r];

                sf::Sprite bg_sprite;

                if ((r + c) % 2 != 0)
                    bg_sprite.setTexture(black_bg);
                else
                    bg_sprite.setTexture(white_bg);

                resize_sprite(bg_sprite, c_tile_size, r_tile_size);
                bg_sprite.setPosition(c * c_tile_size, r * r_tile_size);

                window.draw(bg_sprite);

                if (chess_piece->getSymbol() != ' ') {
                    const std::map<char, sf::Texture>& texture_map =
                        chess_piece->getPieceColour() == PieceColourType::WHITE ? while_tile_texture_map : black_tile_texture_map;

                    sf::Sprite piece_sprite(texture_map.at(chess_piece->getSymbol()));

                    resize_sprite(piece_sprite, c_tile_size, r_tile_size);
                    piece_sprite.setPosition(c * c_tile_size, r * r_tile_size);
                    window.draw(piece_sprite);
                }
            }
        }

        if (piece_is_selected) {
            sf::RectangleShape rectangle(sf::Vector2f(c_tile_size, r_tile_size));
            rectangle.setFillColor(sf::Color(0, 0, 0, 0));
            rectangle.setOutlineThickness(-5);
            rectangle.setOutlineColor(sf::Color(0, 0, 0));
            rectangle.setPosition(clicked_pos.first * c_tile_size, (game.getBoardSize() - 1 - clicked_pos.second) * r_tile_size);
            window.draw(rectangle);

            for (const auto& moveInfo : posssible_moves_with_check) {
                sf::RectangleShape rectangle2(sf::Vector2f(c_tile_size, r_tile_size));
                rectangle2.setFillColor(sf::Color(0, 0, 255, 100));
                rectangle2.setPosition(std::get<2>(moveInfo).first * c_tile_size, (game.getBoardSize() - 1 - std::get<2>(moveInfo).second) * r_tile_size);
                window.draw(rectangle2);
            }
        }

        if (game.getIsCheck()) {
            sf::RectangleShape rectangle2(sf::Vector2f(c_tile_size, r_tile_size));
            rectangle2.setFillColor(sf::Color(255, 0, 0, 100));
            std::pair<int, int> king{game.getWhoseTurn() == PieceColourType::WHITE ? game.getWhiteKing().first : game.getBlackKing().first,
                                     game.getWhoseTurn() == PieceColourType::WHITE ? game.getWhiteKing().second : game.getBlackKing().second};
            rectangle2.setPosition(king.first * c_tile_size, (game.getBoardSize() - 1 - king.second) * r_tile_size);
            window.draw(rectangle2);
        }

        window.display();
    }

    return 0;
}