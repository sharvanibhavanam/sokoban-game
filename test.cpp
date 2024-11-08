// Copyright 2024 Sharvani Bhavanam
#include <fstream>
#include "Sokoban.hpp"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE
#include <boost/test/unit_test.hpp>

using SB::Sokoban;

// Test player movement functions
BOOST_AUTO_TEST_CASE(testMoveUp) {
    Sokoban _newgame;
    std::ifstream level("./level1.lvl");
    level >> _newgame;

    _newgame.movePlayer(SB::Direction::Up);
    sf::Vector2u PlayerPs({3, 5});

    BOOST_REQUIRE_EQUAL(PlayerPs.x, _newgame.playerLoc().x);
    BOOST_REQUIRE_EQUAL(PlayerPs.y, _newgame.playerLoc().y);
}

BOOST_AUTO_TEST_CASE(testMoveDown) {
    Sokoban _newgame;
    std::ifstream level("./level1.lvl");
    level >> _newgame;

    _newgame.movePlayer(SB::Direction::Down);
    sf::Vector2u PlayerPs({3, 7});

    BOOST_REQUIRE_EQUAL(PlayerPs.x, _newgame.playerLoc().x);
    BOOST_REQUIRE_EQUAL(PlayerPs.y, _newgame.playerLoc().y);
}

BOOST_AUTO_TEST_CASE(testMoveRight) {
    Sokoban _newgame;
    std::ifstream level("./level1.lvl");
    level >> _newgame;

    _newgame.movePlayer(SB::Direction::Right);
    sf::Vector2u PlayerPs({4, 6});

    BOOST_REQUIRE_EQUAL(PlayerPs.x, _newgame.playerLoc().x);
    BOOST_REQUIRE_EQUAL(PlayerPs.y, _newgame.playerLoc().y);
}

BOOST_AUTO_TEST_CASE(testMoveLeft) {
    Sokoban _newgame;
    std::ifstream level("./level1.lvl");
    level >> _newgame;

    _newgame.movePlayer(SB::Direction::Left);
    sf::Vector2u PlayerPs({2, 6});

    BOOST_REQUIRE_EQUAL(PlayerPs.x, _newgame.playerLoc().x);
    BOOST_REQUIRE_EQUAL(PlayerPs.y, _newgame.playerLoc().y);
}