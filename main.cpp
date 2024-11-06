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

    unsigned int windowWidth = game.pixelWidth();
    unsigned int windowHeight = game.pixelHeight() + 50;  // Extra height for the timer display

    if (windowWidth == 0 || windowHeight == 0) {
        std::cerr << "Error: Invalid level dimensions.\n";
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sokoban");

    sf::Font font;  // Load font for displaying elapsed time
    if (!font.loadFromFile("arial.TTF")) {
        std::cerr << "Error: Could not load font.\n";
        return 1;
    }


    sf::Text elapsedTimeText;
    elapsedTimeText.setFont(font);
    elapsedTimeText.setCharacterSize(24);
    elapsedTimeText.setFillColor(sf::Color::White);
    elapsedTimeText.setPosition(10, windowHeight - 40);

    sf::Text winText;
    winText.setFont(font);
    winText.setString("Congratulations, you won!");
    winText.setCharacterSize(48);
    winText.setFillColor(sf::Color::Black);
    winText.setPosition(windowWidth / 2 - winText.getGlobalBounds().width / 2, windowHeight / 2);

    sf::Clock clock;
    bool gameWon = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) game.movePlayer(SB::Direction::Up);
            else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) game.movePlayer(SB::Direction::Down);
            else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) game.movePlayer(SB::Direction::Left);
            else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) game.movePlayer(SB::Direction::Right);
            else if (event.key.code == sf::Keyboard::R) game.reset();
            
            if (game.isWon()) {
                    gameWon = true;
                }
            }
        }

        sf::Time elapsed = game.getGameClock().getElapsedTime();  // Get the elapsed time
        int seconds = static_cast<int>(elapsed.asSeconds());
        int minutes = seconds / 60;
        seconds %= 60;

        std::stringstream ss;  // Format elapsed time
        ss << std::setw(2) << std::setfill('0') << minutes << ":"
           << std::setw(2) << std::setfill('0') << seconds;
        elapsedTimeText.setString("Time: " + ss.str());

        window.clear();

        window.draw(game);

        window.draw(elapsedTimeText);

        if (gameWon) {
            window.draw(winText);
        }

        window.display();
    }

    return 0;
}