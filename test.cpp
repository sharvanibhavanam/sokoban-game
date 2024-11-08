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

/*
// Test Undo functionality
BOOST_AUTO_TEST_CASE(testUndoMove) {
    Sokoban _newgame;
    std::ifstream level("./level1.lvl");
    level >> _newgame;
    
    // Save state before the move
    _newgame.pushState();
    
    // Move the player right
    _newgame.movePlayer(SB::Direction::Right);
    sf::Vector2u PlayerPsAfterMove({4, 6});
    
    BOOST_REQUIRE_EQUAL(PlayerPsAfterMove.x, _newgame.playerLoc().x);
    BOOST_REQUIRE_EQUAL(PlayerPsAfterMove.y, _newgame.playerLoc().y);
    
    // Perform Undo
    _newgame.undo();
    sf::Vector2u PlayerPsBeforeUndo({3, 6});
    
    BOOST_REQUIRE_EQUAL(PlayerPsBeforeUndo.x, _newgame.playerLoc().x);
    BOOST_REQUIRE_EQUAL(PlayerPsBeforeUndo.y, _newgame.playerLoc().y);
}

// Test Redo functionality
BOOST_AUTO_TEST_CASE(testRedoMove) {
    Sokoban _newgame;
    std::ifstream level("./level1.lvl");
    level >> _newgame;
    
    // Save initial state and make a move
    _newgame.pushState();
    _newgame.movePlayer(SB::Direction::Right);
    sf::Vector2u PlayerPsAfterMove({4, 6});
    
    BOOST_REQUIRE_EQUAL(PlayerPsAfterMove.x, _newgame.playerLoc().x);
    BOOST_REQUIRE_EQUAL(PlayerPsAfterMove.y, _newgame.playerLoc().y);
    
    // Undo move
    _newgame.undo();
    sf::Vector2u PlayerPsBeforeUndo({3, 6});
    BOOST_REQUIRE_EQUAL(PlayerPsBeforeUndo.x, _newgame.playerLoc().x);
    BOOST_REQUIRE_EQUAL(PlayerPsBeforeUndo.y, _newgame.playerLoc().y);
    
    // Redo the move
    _newgame.redo();
    BOOST_REQUIRE_EQUAL(PlayerPsAfterMove.x, _newgame.playerLoc().x);
    BOOST_REQUIRE_EQUAL(PlayerPsAfterMove.y, _newgame.playerLoc().y);
}
*/
