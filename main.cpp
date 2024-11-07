// Copyright 2024 Sharvani Bhavanam

#include <iomanip>
#include <sstream>
#include "Sokoban.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <level filename>\n";
        return 1;
    }

    SB::Sokoban game(argv[1]);

    unsigned int window_w = game.pixelWidth();
    unsigned int window_h = game.pixelHeight() + 50;

    if (window_w == 0 || window_h == 0) {
        std::cerr << "Error: Invalid level dimensions.\n";
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(window_w, window_h), "Sokoban");

    sf::Font font;
    if (!font.loadFromFile("arial.TTF")) {
        std::cerr << "Error: Could not load font.\n";
        return 1;
    }

    sf::Text elapsedTimeText;
    elapsedTimeText.setFont(font);
    elapsedTimeText.setCharacterSize(24);
    elapsedTimeText.setFillColor(sf::Color::White);
    elapsedTimeText.setPosition(10, window_h - 40);

    sf::Text winText;
    winText.setFont(font);
    winText.setString("Congratulations, you won!");
    winText.setCharacterSize(48);
    winText.setFillColor(sf::Color::Black);
    float xPos = window_w / 2 - winText.getGlobalBounds().width / 2;
    float yPos = window_h / 2;
    winText.setPosition(xPos, yPos);

    sf::Clock clock;
    bool gameWon = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;

        if (key == sf::Keyboard::Up || key == sf::Keyboard::W) {
            game.movePlayer(SB::Direction::Up);
        } else if (key == sf::Keyboard::Down || key == sf::Keyboard::S) {
            game.movePlayer(SB::Direction::Down);
        } else if (key == sf::Keyboard::Left || key == sf::Keyboard::A) {
            game.movePlayer(SB::Direction::Left);
        } else if (key == sf::Keyboard::Right || key == sf::Keyboard::D) {
            game.movePlayer(SB::Direction::Right);
        } else if (key == sf::Keyboard::R) {
            game.reset();
        }

        if (game.isWon()) {
            gameWon = true;
        }
    }
}

        sf::Time elapsed = game.getGameClock().getElapsedTime();
        int seconds = static_cast<int>(elapsed.asSeconds());
        int minutes = seconds / 60;
        seconds %= 60;

        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << minutes << ":"
           << std::setw(2) << std::setfill('0') << seconds;
        elapsedTimeText.setString("Time: " + ss.str());

        window.clear();
        window.draw(game);
        window.draw(elapsedTimeText);

        if (gameWon) window.draw(winText);

        window.display();
    }

    return 0;
}
