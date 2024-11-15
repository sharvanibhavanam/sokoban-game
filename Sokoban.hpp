// Copyright 2024 Sharvani Bhavanam

#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


namespace SB {
enum class Direction { Up, Down, Left, Right };

struct GameState {
    sf::Vector2u playerPos;
    std::vector<std::vector<char>> grid;
};

class Sokoban : public sf::Drawable {
 public:
  static const int TILE_SIZE = 64;

  Sokoban();
  explicit Sokoban(const std::string&);

  unsigned int pixelHeight() const;
  unsigned int pixelWidth() const;

  unsigned int height() const;
  unsigned int width() const;

  sf::Vector2u playerLoc() const;
  sf::Clock& getGameClock() { return gameClock; }

  const sf::Vector2u& boxLoc(size_t index) const { return boxes[index]; }

  bool isWon() const;

  void movePlayer(Direction dir);
  void reset();

  void undo();
  void redo();

  void playVictorySound();
  sf::Music backgroundMusic;
  void playBackgroundSound();

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  std::string levelFilename;
  sf::Clock gameClock;

  void loadTextures();
  void loadLevel(const std::string& filename);

  std::map<std::string, sf::Texture> textures;
  std::vector<std::vector<char>> grid;

  std::vector<sf::Vector2u> boxes;

  unsigned int gridHeight = 0;
  unsigned int gridWidth = 0;
  sf::Vector2u pos;

  std::stack<GameState> undoStack;
  std::stack<GameState> redoStack;

  sf::SoundBuffer victorySoundBuffer;
  sf::Sound victorySound;

  sf::Texture* currentPlayerTexture;

  void saveState();

  friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
  friend std::istream& operator>>(std::istream& in, Sokoban& s);
};
}  // namespace SB
