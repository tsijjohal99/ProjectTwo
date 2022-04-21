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

const int tile_size{64};

void resize_sprite(sf::Sprite& piece_sprite, int width, int height) {
  auto size = piece_sprite.getTexture()->getSize();
  piece_sprite.setScale((float)width/size.x, (float)height/size.y);
}

int main(int argc, char* argv[]) {
  Board game;
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

  while(window.isOpen()) {
    sf::Event Event;

    while(window.pollEvent(Event)) {
      if (Event.type == sf::Event::Closed)
        window.close();

      if (Event.type == sf::Event::KeyPressed) {
        if (Event.key.code == sf::Keyboard::Escape)
          window.close();
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
            chess_piece->getPieceColour() == PieceColourType::WHITE ?
              while_tile_texture_map : black_tile_texture_map;

          sf::Sprite piece_sprite(texture_map.at(chess_piece->getSymbol()));

          resize_sprite(piece_sprite, tile_size, tile_size);
          piece_sprite.setPosition(c * tile_size, r * tile_size);
          window.draw(piece_sprite);
        }
      }
    }

    window.display();

  }
  
  return 0;
}