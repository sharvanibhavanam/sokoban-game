// Copyright 2024 Sharvani Bhavanam

#include "Sokoban.hpp"
#include <fstream>
#include <algorithm>

namespace SB {

Sokoban::Sokoban() {
    loadTextures();
}

Sokoban::Sokoban(const std::string& filename) {
    loadTextures();
    loadLevel(filename);
}

void Sokoban::loadTextures() {  // Load textures
    textures["wall"].loadFromFile("kenney_sokobanPack/block_06.png");
    textures["floor"].loadFromFile("kenney_sokobanPack/ground_01.png");
    textures["storage"].loadFromFile("kenney_sokobanPack/ground_04.png");
    textures["box"].loadFromFile("kenney_sokobanPack/crate_03.png");
    textures["box_on_storage"].loadFromFile("kenney_sokobanPack/crate_03.png");
    textures["player"].loadFromFile("kenney_sokobanPack/player_05.png");
}

void Sokoban::loadLevel(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open the file.");
    }

        unsigned int h, w;
        file >> h >> w;
        gridHeight = h;
        gridWidth = w;

        grid.resize(gridHeight, std::vector<char>(gridWidth, '.'));
        for (unsigned int y = 0; y < gridHeight; ++y) {
            for (unsigned int x = 0; x < gridWidth; ++x) {
                file >> grid[y][x];
                if (grid[y][x] == '@') {
                    playerPosition = {x, y};
                }
            }
        }
}

unsigned int Sokoban::height() const { return gridHeight; }  // Getters for grid dimensions
unsigned int Sokoban::width() const { return gridWidth; }

unsigned int Sokoban::pixelHeight() const { return gridHeight * TILE_SIZE; }
unsigned int Sokoban::pixelWidth() const { return gridWidth * TILE_SIZE; }

sf::Vector2u Sokoban::playerLoc() const { return playerPosition; }

bool Sokoban::isWon() const {
    // in part B
    return false;
}

void Sokoban::movePlayer(Direction dir) {
    int dx = 0, dy = 0;
    switch (dir) {
        case Direction::Up: dy = -1; break;
        case Direction::Down: dy = 1; break;
        case Direction::Left: dx = -1; break;
        case Direction::Right: dx = 1; break;
    }

    unsigned int newX = playerPosition.x + dx;
    unsigned int newY = playerPosition.y + dy;

    if (newX >= 0 && newX < gridWidth && newY >= 0 && newY < gridHeight) {
        char nextCell = grid[newY][newX];
        if (nextCell == '.' || nextCell == 'a') {  // Check if the player can move
            playerPosition = {static_cast<unsigned>(newX), static_cast<unsigned>(newY)};
        } else if (nextCell == 'A') {  // Check if the player can push a box
            unsigned int boxNewX = newX + dx;
            unsigned int boxNewY = newY + dy;
            if (boxNewX >= 0 && boxNewX < gridWidth && boxNewY >= 0 && boxNewY < gridHeight &&
                (grid[boxNewY][boxNewX] == '.' || grid[boxNewY][boxNewY] == 'a')) {
                grid[newY][newX] = '.';  // Move box and player
                grid[boxNewY][boxNewX] = 'A';
                playerPosition = {static_cast<unsigned>(newX), static_cast<unsigned>(newY)};
            }
        }
    }
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite;

    for (unsigned int y = 0; y < gridHeight; ++y) {
        for (unsigned int x = 0; x < gridWidth; ++x) {
            switch (grid[y][x]) {
                case '#':  // Wall
                    sprite.setTexture(textures.at("wall"));
                    break;
                case '.':  // Floor
                    sprite.setTexture(textures.at("floor"));
                    break;
                case 'a':  // Storage location
                    sprite.setTexture(textures.at("storage"));
                    break;
                case 'A':  // Box
                    sprite.setTexture(textures.at("box"));
                    break;
                case '1':  // Box on storage
                    sprite.setTexture(textures.at("box_on_storage"));
                    break;
                default:
                    sprite.setTexture(textures.at("floor"));
            }

            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            target.draw(sprite, states);
        }
    }

    sprite.setTexture(textures.at("player"));  // Draw player
    sprite.setPosition(playerPosition.x * TILE_SIZE, playerPosition.y * TILE_SIZE);
    target.draw(sprite, states);
}

std::ostream& operator<<(std::ostream& out, const Sokoban& s) {
    for (unsigned int y = 0; y < s.gridHeight; ++y) {
        for (unsigned int x = 0; x < s.gridWidth; ++x) {
            out << s.grid[y][x];
        }
        out << '\n';
    }
    return out;
}

std::istream& operator>>(std::istream& in, Sokoban& s) {
    in >> s.gridHeight >> s.gridWidth;
    s.grid.resize(s.gridHeight, std::vector<char>(s.gridWidth, '.'));

    for (unsigned int y = 0; y < s.gridHeight; ++y) {
        for (unsigned int x = 0; x < s.gridWidth; ++x) {
            in >> s.grid[y][x];
            if (s.grid[y][x] == '@') {
                s.playerPosition = {static_cast<unsigned>(x), static_cast<unsigned>(y)};
            }
        }
    }
    return in;
}

}  // namespace SB