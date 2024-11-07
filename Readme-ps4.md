# PS4: Sokoban

## Contact
Name: Sharvani Bhavanam
Section: 201
Time to Complete: 10 hours

## Description
This project is a Sokoban game built using the SFML library. The goal is to move all boxes into the storage spaces to win the game. A timer at the bottom of the screen tracks the game duration.

### Features
Describe what your major decisions were and why you did things that way.

#### Part a
1. To draw my grid on the screen based on the contents for each level, I dcided to override my draw function so it would iterate over each cell's texture.
2. I used map to load and manage textures so I could switch dynamically based on grid cell types.
#### Part b
1. The game restricts player movement based on grid content. If a player tries to move in a direction with a wall or outside the grid, the game blocks the movement. For box-pushing, the code checks if there’s an open storage space for the box to move into before allowing the player to push.
2.  I implemented a isWon function that checks if all boxes are in storage spaces, which triggers the win condition and stops further movement. This function compares the positions of boxes and storage cells in the grid.

### Memory
I used a 2D vector to store my level data- it stores the grid dimensions like height and width, and grid content like walls into the grid vector. 

### Lambdas
I did not use any lambda functions or utilize algorithms library.

### Issues
I made sure to check the grid is drawn properly, and the player moves only in open spots. I don't think there are any issues with my code.

### Extra Credit
I added a timer at the bottom of my screen using sf::Clock to start a timer when the game begins. I then made a function to keep track of the time. I also downloaded a font to display the time onto the screen.

## Acknowledgements

https://www.deefont.com/arial-font/

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban

Minesweeper and connect4 games implemented during class