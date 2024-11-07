// Copyright 2024 Sharvani Bhavanam

#include "Sokoban.hpp"
#include <fstream>
#include <algorithm>
#include <string>

namespace SB {

Sokoban::Sokoban() {
    loadTextures();
}

Sokoban::Sokoban(const std::string& filename) : levelFilename(filename) {
    loadTextures();
    loadLevel(levelFilename);

    if (!backgroundMusic.openFromFile("bg_music.wav")) {
        std::cerr << "Error: Could not load background music.\n";
    } else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(50);
        backgroundMusic.play();
    }

    if (!victorySoundBuffer.loadFromFile("level-win-6416.wav")) {
        std::cerr << "Error: Could not load victory sound.\n";
    } else {
        victorySound.setBuffer(victorySoundBuffer);
    }
}

void Sokoban::playVictorySound() {
    backgroundMusic.stop();
    victorySound.setVolume(70);
    victorySound.play();
}

void Sokoban::playBackgroundSound() {
    backgroundMusic.play();
}

void Sokoban::reset() {
    loadLevel(levelFilename);
    gameClock.restart();
    while (!undoStack.empty()) undoStack.pop();
    while (!redoStack.empty()) redoStack.pop();
}

void Sokoban::loadTextures() {  // Load textures
    textures["wall"].loadFromFile("kenney_sokobanPack/block_06.png");
    textures["floor"].loadFromFile("kenney_sokobanPack/ground_01.png");
    textures["storage"].loadFromFile("kenney_sokobanPack/ground_04.png");
    textures["box"].loadFromFile("kenney_sokobanPack/crate_03.png");
    textures["box_on_storage"].loadFromFile("kenney_sokobanPack/crate_03.png");
    textures["player_up"].loadFromFile("kenney_sokobanPack/player_U.png");
    textures["player_down"].loadFromFile("kenney_sokobanPack/player_D.png");
    textures["player_left"].loadFromFile("kenney_sokobanPack/player_L.png");
    textures["player_right"].loadFromFile("kenney_sokobanPack/player_R.png");
    currentPlayerTexture = &textures["player_down"];
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
                    pos = {x, y};
                }
            }
        }
}

unsigned int Sokoban::height() const { return gridHeight; }
unsigned int Sokoban::width() const { return gridWidth; }

unsigned int Sokoban::pixelHeight() const { return gridHeight * TILE_SIZE; }
unsigned int Sokoban::pixelWidth() const { return gridWidth * TILE_SIZE; }

sf::Vector2u Sokoban::playerLoc() const { return pos; }

bool Sokoban::isWon() const {
    std::vector<sf::Vector2u> box_pos;
    std::vector<sf::Vector2u> stor_pos;

    for (unsigned int y = 0; y < gridHeight; ++y) {
        for (unsigned int x = 0; x < gridWidth; ++x) {
            if (grid[y][x] == 'A') {  // Box position
                box_pos.emplace_back(x, y);
            } else if (grid[y][x] == 'a') {  // Storage position
                stor_pos.emplace_back(x, y);
            }
        }
    }

    auto pos_comp = [](const sf::Vector2u& lhs, const sf::Vector2u& rhs) {
        return (lhs.x == rhs.x) ? (lhs.y < rhs.y) : (lhs.x < rhs.x);
    };

    std::sort(box_pos.begin(), box_pos.end(), pos_comp);
    std::sort(stor_pos.begin(), stor_pos.end(), pos_comp);

    auto check_eq = [](const sf::Vector2u& v, const sf::Vector2u& v2) -> bool {
        return (v.x == v2.x) && (v.y == v2.y);
    };

    auto check = [box_pos, stor_pos, check_eq]() -> bool {
        if (stor_pos.size() > box_pos.size()) {
            int i = 0;
            if (!std::equal(box_pos.begin(), box_pos.end(), stor_pos.begin())) {
                if (!check_eq(box_pos.at(i), stor_pos.at(i)) &&
                    check_eq(box_pos.at(i), stor_pos.at(i + 1)) &&
                    check_eq(box_pos.at(i + 1), stor_pos.at(i + 2)))
                    return true;
                if (check_eq(box_pos.at(i), stor_pos.at(i)) &&
                    !check_eq(box_pos.at(i + 1), stor_pos.at(i + 1)) &&
                    check_eq(box_pos.at(i + 1), stor_pos.at(i + 2)))
                    return true;
                return false;
            } else {
                return true;
            }
        }
        return std::equal(stor_pos.begin(), stor_pos.end(), box_pos.begin());
    };

    return check();
}

void Sokoban::saveState() {
    GameState currentState;
    currentState.playerPos = pos;
    currentState.grid = grid;

    undoStack.push(currentState);  // Save to undo stack

    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

void Sokoban::undo() {
    if (!undoStack.empty()) {
        redoStack.push({pos, grid});

        GameState previousState = undoStack.top();
        undoStack.pop();

        pos = previousState.playerPos;  // Restore the previous state
        grid = previousState.grid;
    }
}

void Sokoban::redo() {
    if (!redoStack.empty()) {
        undoStack.push({pos, grid});

        GameState nextState = redoStack.top();
        redoStack.pop();

        pos = nextState.playerPos;  // Restore the next state
        grid = nextState.grid;
    }
}

void Sokoban::movePlayer(Direction dir) {
     if (isWon()) {
        return;
     }

    saveState();

    int dx = 0, dy = 0;
    switch (dir) {
        case Direction::Up:
            dy = -1;
            currentPlayerTexture = &textures["player_up"];
            break;
        case Direction::Down:
            dy = 1;
            currentPlayerTexture = &textures["player_down"];
            break;
        case Direction::Left:
            dx = -1;
            currentPlayerTexture = &textures["player_left"];
            break;
        case Direction::Right:
            dx = 1;
            currentPlayerTexture = &textures["player_right"];
            break;
    }

    unsigned int X = (pos.x + dx);
    unsigned int Y = (pos.y + dy);

    if (X >= 0 && X < gridWidth && Y >= 0 && Y < gridHeight) {
        char nextCell = grid[Y][X];

        if (nextCell == '.' || nextCell == 'a' || nextCell == '@') {
            pos = {static_cast<unsigned>(X), static_cast<unsigned>(Y)};
        } else if (nextCell == 'A' || nextCell == '1') {
            unsigned int boX = X + dx;
            unsigned int boY = Y + dy;
            if (boX >= 0 && boX < gridWidth && boY >= 0 && boY < gridHeight) {
                char nextCell = grid[boY][boX];

                if (nextCell == '.' || nextCell == 'a' || nextCell == '@') {
                    grid[Y][X] = (nextCell == '1') ? 'a' : '.';

                    grid[boY][boX] = (nextCell == 'a') ? '1' : 'A';
                    pos = {static_cast<unsigned>(X), static_cast<unsigned>(Y)};
                }
            }
        }
    }
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite;

    for (unsigned int y = 0; y < gridHeight; y++) {
        for (unsigned int x = 0; x < gridWidth; x++) {
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

    sprite.setTexture(*currentPlayerTexture);
    sprite.setPosition(pos.x * TILE_SIZE, pos.y * TILE_SIZE);
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
                s.pos = {static_cast<unsigned>(x), static_cast<unsigned>(y)};
            }
        }
    }
    return in;
}

}  // namespace SB
