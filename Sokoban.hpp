// Copyright 2024 Sharvani Bhavanam

#pragma once

#include <iostream>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

namespace SB {
enum class Direction {
    Up, Down, Left, Right
};

class Sokoban : public sf::Drawable {
 public:
    static const int TILE_SIZE = 64;

    Sokoban();
    explicit Sokoban(const std::string&);  // Optional

    unsigned int pixelHeight() const;  // Optional
    unsigned int pixelWidth() const;   // Optional

    unsigned int height() const;
    unsigned int width() const;

    sf::Vector2u playerLoc() const;

    bool isWon() const;

    void movePlayer(Direction dir);
    void reset();

    void undo();  // Optional extra credit
    void redo();  // Optional extra credit

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    void loadTextures();
    void loadLevel(const std::string& filename);

    std::map<std::string, sf::Texture> textures;
    std::vector<std::vector<char>> grid;
    unsigned int gridHeight = 0;
    unsigned int gridWidth = 0;
    sf::Vector2u playerPosition;

    friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
    friend std::istream& operator>>(std::istream& in, Sokoban& s);
};
}  // namespace SB