#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE
#include <boost/test/unit_test.hpp>
#include "Sokoban.hpp"

/*
BOOST_AUTO_TEST_CASE(LoadLevelTest) {
    // Create Sokoban object with a sample level
    SB::Sokoban game("./level1.lvl");

    // Verify initial conditions after loading the level
    BOOST_CHECK_EQUAL(game.height(), 10);  // Example height
    BOOST_CHECK_EQUAL(game.width(), 10);   // Example width
    BOOST_CHECK_EQUAL(game.playerLoc(), sf::Vector2u(1, 1));  // Example player position
}

BOOST_AUTO_TEST_CASE(MovePlayerTest) {
    SB::Sokoban game("level1.lvl");

    // Test moving the player in various directions
    game.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(game.playerLoc(), sf::Vector2u(1, 2));  // Player moves down

    game.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(game.playerLoc(), sf::Vector2u(2, 2));  // Player moves right

    // Test boundary condition (e.g., wall blocking)
    game.movePlayer(SB::Direction::Left);  // Assuming wall is on the left
    BOOST_CHECK_EQUAL(game.playerLoc(), sf::Vector2u(2, 2));  // Position unchanged
}

BOOST_AUTO_TEST_CASE(PushBoxTest) {
    SB::Sokoban game("level1.lvl");

    // Move the player to a position to push a box
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Down);
    
    // Push the box down into a storage location
    game.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(game.playerLoc(), sf::Vector2u(2, 3));

    // Verify the box moved to the expected storage location
    BOOST_CHECK_EQUAL(game.isWon(), true);
}

BOOST_AUTO_TEST_CASE(WinConditionTest) {
    SB::Sokoban game("level1.lvl");

    // Move player and boxes to solve the level
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Down); 

    
    //BOOST_CHECK(game.isWon());
}
*/