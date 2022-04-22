#include "config.h"
#include "board.h"
#include "chessPiece.h"
#include "pieceColourType.h"

#include <vector>
#include <unordered_map>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

#define TILE_MAP_SIZE 8

void resize_sprite(sf::Sprite& piece_sprite, int width, int height) {
  	auto size = piece_sprite.getTexture()->getSize();
  	piece_sprite.setScale((float)width/size.x, (float)height/size.y);
}

int main(int argc, char* argv[]) {
	Board game;
	bool playGame = true;
	const int tile_size = 64;
	const int window_size = game.getBoardSize() * tile_size;

	sf::RenderWindow window(
		sf::VideoMode(window_size, window_size), "Wicked Chess Game"
	);

	const std::string tile_dir = "resources/tiles/";
	std::map<char, sf::Texture> while_tile_texture_map{};
	std::map<char, sf::Texture> black_tile_texture_map{};
	
	sf::Texture white_bg;
	sf::Texture black_bg;

	white_bg.loadFromFile(tile_dir + "w.png");
	black_bg.loadFromFile(tile_dir + "b.png");

	const std::vector<char> tiles = {'R','N','B','Q','K','P'};

	for (const auto& tile : tiles) {
		sf::Texture white_texture;
		sf::Texture black_texture;

		auto tile_path = [&tile_dir, &tile](std::string colour) {
		return tile_dir + colour + '/' + tile + ".png";
		};

		white_texture.loadFromFile(tile_path("white"));
		black_texture.loadFromFile(tile_path("black"));
		
		while_tile_texture_map.insert({tile, white_texture});
		black_tile_texture_map.insert({tile, black_texture});
	}

	ChessPiece *selected_piece{};
	std::pair<int, int> clicked_pos{};
	bool piece_is_selected{false};

	std::vector<std::pair<int, int>> posssible_moves_pos{};
	std::vector<std::string> possible_moves_str{};

	while(window.isOpen() & playGame) {
		sf::Event Event;
		// bool clicked{false};

		while(window.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				window.close();

			if (Event.type == sf::Event::KeyPressed) {
				if (Event.key.code == sf::Keyboard::Escape) {
					piece_is_selected = false;
					posssible_moves_pos.clear();
				} else if (Event.key.code == sf::Keyboard::Left) {
					game.undoMove();
					piece_is_selected = false;
					posssible_moves_pos.clear();
				}
			}

			if (Event.type == sf::Event::MouseButtonPressed) {
				if (Event.mouseButton.button == sf::Mouse::Left) {
					// std::cout << "mouse x: " << Event.mouseButton.x << std::endl;
					// std::cout << "mouse y: " << Event.mouseButton.y << std::endl;

					//std::cout << "col: " << int(Event.mouseButton.x / tile_size) << std::endl;
					//std::cout << "row: " << game.getBoardSize() - 1 -int(Event.mouseButton.y / tile_size) << std::endl;
					
					if (!piece_is_selected) {
						clicked_pos.first = Event.mouseButton.x / tile_size;
						clicked_pos.second = game.getBoardSize() - 1 - int(Event.mouseButton.y / tile_size);

						piece_is_selected = true;
						ChessPiece *selected_piece = game.getGrid()[clicked_pos.first][clicked_pos.second];
						// std::cout << "piece clicked: " << chess_piece->getSymbol() << std::endl;
						// const std::string colour = (chess_piece->getPieceColour() == PieceColourType::WHITE) ? "white" : "black";
						// std::cout << "colour clicked: " << colour << std::endl;

						if (selected_piece->getPieceColour() == game.getWhoseTurn()) {

							std::list<std::string> posssible_moves = selected_piece->possibleMoves(game.getGrid(), false);
							std::list<std::string> posssible_moves_with_check;

							for (const auto& move : posssible_moves) {
								std::string updatedMove = move;

								if (updatedMove[updatedMove.size()-1] == '+') {
									game.movingPiece(updatedMove, clicked_pos.first, clicked_pos.second);
									game.addMove(updatedMove);
									if (game.checkCheckmate()) {
										updatedMove.pop_back();
										updatedMove += '#';
									}
									game.setWhoseTurn((game.getWhoseTurn() == PieceColourType::WHITE) ? PieceColourType::BLACK :PieceColourType::WHITE);
									game.undoMove();
								}

								posssible_moves_with_check.push_back(updatedMove);
							}

							if (game.getIsCheck()) {
								posssible_moves_with_check = game.updateCheck(posssible_moves_with_check);
							}

							for (const auto& move : posssible_moves_with_check) {
								std::string updatedMove = move;

								possible_moves_str.push_back(updatedMove);
								std::pair<int, int> pos{}; 
								
								switch(updatedMove[updatedMove.size() - 1]) {
									case '+': {
										updatedMove.pop_back();
										break;
									} case '#': {
										updatedMove.pop_back();
										break;
									}
								}

								if (updatedMove == "0-0") {
									pos = {6, selected_piece->getPieceColour() == PieceColourType::WHITE ? 0 : 7};
								} else if (updatedMove == "0-0-0") {
									pos = {2, selected_piece->getPieceColour() == PieceColourType::WHITE ? 0 : 7};
								} else if (char(updatedMove[updatedMove.size() - 2]) == '=') {
									pos = {int(updatedMove[updatedMove.size() - 4] - 'a'), int(updatedMove[updatedMove.size() - 3] - '1')};
								} else {
									pos = {int(updatedMove[updatedMove.size() - 2] - 'a'), int(updatedMove[updatedMove.size() - 1] - '1')};
								}

								//std::cout << pos.first << ", " << pos.second << std::endl;

								posssible_moves_pos.push_back(pos);
							}
						}
					} else {
						std::pair<int, int> new_clicked_pos{};

						new_clicked_pos.first = Event.mouseButton.x / tile_size;
						new_clicked_pos.second = game.getBoardSize() - 1 -int(Event.mouseButton.y / tile_size);

						for (int i = 0; i < posssible_moves_pos.size(); i++) {
							if (new_clicked_pos == posssible_moves_pos[i]) {
								playGame = game.makeMove(possible_moves_str[i]);
								
								break;
							}
						}
						piece_is_selected = false;
						posssible_moves_pos.clear();
						possible_moves_str.clear();

					}

				}
			}
		}

		window.clear(sf::Color::Black);

		for (int r = 0; r < game.getBoardSize(); r++) {
			for (int c = 0; c < game.getBoardSize(); c++) {
				ChessPiece *chess_piece = game.getGrid()[c][game.getBoardSize() - 1 - r];

				sf::Sprite bg_sprite;

				if ((r + c) % 2 != 0)
					bg_sprite.setTexture(black_bg);
				else
					bg_sprite.setTexture(white_bg);

				resize_sprite(bg_sprite, tile_size, tile_size);
				bg_sprite.setPosition(c * tile_size, r * tile_size);

				window.draw(bg_sprite);

				if (chess_piece->getSymbol() != ' ') {
					const std::map<char, sf::Texture>& texture_map =
						chess_piece->getPieceColour() == PieceColourType::WHITE ? while_tile_texture_map : black_tile_texture_map;

					sf::Sprite piece_sprite(texture_map.at(chess_piece->getSymbol()));

					resize_sprite(piece_sprite, tile_size, tile_size);
					piece_sprite.setPosition(c * tile_size, r * tile_size);
					window.draw(piece_sprite);
				}
			}
		}

		if (piece_is_selected) {
			sf::RectangleShape rectangle(sf::Vector2f(tile_size, tile_size));
			rectangle.setFillColor(sf::Color(0, 0, 0, 0));
			rectangle.setOutlineThickness(-5);
			rectangle.setOutlineColor(sf::Color(0, 0, 0));
			rectangle.setPosition(clicked_pos.first * tile_size, (game.getBoardSize() - 1 - clicked_pos.second) * tile_size);
			window.draw(rectangle);

			for (const auto& pos : posssible_moves_pos) {
				sf::RectangleShape rectangle2(sf::Vector2f(tile_size, tile_size));
				rectangle2.setFillColor(sf::Color(0, 0, 255, 100));
				rectangle2.setPosition(pos.first * tile_size, (game.getBoardSize() - 1 - pos.second) * tile_size);
				window.draw(rectangle2);
			}
		}

		if (game.getIsCheck()) {
			sf::RectangleShape rectangle2(sf::Vector2f(tile_size, tile_size));
			rectangle2.setFillColor(sf::Color(255, 0, 0, 100));
			int king[] = {game.getWhoseTurn() == PieceColourType::WHITE ? game.getWhiteKing()[0] : game.getBlackKing()[0],
				game.getWhoseTurn() == PieceColourType::WHITE ? game.getWhiteKing()[1] : game.getBlackKing()[1]};
			rectangle2.setPosition(king[0] * tile_size, (game.getBoardSize() - 1 - king[1]) * tile_size);
			window.draw(rectangle2);
		}

		window.display();

	}

	game.deleteBoard();
	
	return 0;
}