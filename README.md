# Snake Game in C 🐍🎮

## Overview

This project is a terminal-based implementation of the classic Snake game, developed entirely in C. Designed to be both engaging and challenging, the game includes various adjustable settings and dynamic gameplay mechanics that provide an exciting experience for players of all skill levels.

As my final project for the Harvard CS50 course, this game showcases my understanding of core C programming concepts. In developing this project, I implemented fundamental elements such as pointers, custom data structures, and dynamic memory management. Additionally, I applied input handling techniques to ensure smooth and responsive gameplay. These features allowed me to deepen my knowledge of lower-level programming and memory management.

This project demonstrates my ability to apply theoretical knowledge to build a practical, interactive application. Moreover, it highlights my skill in designing features and tackling problems effectively as they arise.

## Project Structure

The project is organized into several key files:

- main.c - Serves as the game’s entry point.

- src/settings.c - Manages the game’s settings interface and configuration options.

- src/gameplay.c - Contains the primary game mechanics.

- src/board.c - Handles the game board’s rendering and updates.

- src/snake.c - Defines the snake’s structure and gameplay logic.

- src/static_obstacles.c - Defines the static obstacles' structure and gameplay logic.

- src/dynamic_obstacles.c - Defines the dynamic obstacles' structure and gameplay logic.

- src/helpers.c - Provides various utility functions.


## Design Choices

### Separation:
Each file is responsible for a specific part of the game, such as the settings, gameplay, snake object, etc. This partition simplifying code organization and debugging. In addition, it improves the project’s readability and maintainability. 

### Real-Time Input Handling:
To capture user input without interrupting gameplay, the GetAsyncKeyState function was used. This implementation enables smooth and responsive controls, which enhances the user experience. 

### ANSI Escape Codes:
Utilizing ANSI escape codes allows for precise cursor control in the terminal, enabling the game to update only the necessary parts of the board. That is, it allows to avoid redrawing the entire board and clearing the terminal each frame. Therefore, this approach significantly reduces computational overhead, resulting in smoother gameplay and an enhanced user experience. Additionally, the use of ANSI codes enables color printing on the screen, further enriching the visual experience for players.

### Custom Data Structures:
The snake and the different obstacle types are each implemented using linked lists, enabling dynamic and efficient management of these objects. Specifically, the snake is implemented as a doubly linked list, allowing O(1) movement operations (independent of the snake’s length). This approach ensures that the game can adjust these essential elements in real-time, accommodating changes during gameplay without the constraints of fixed-size data structures.

### Incorporation of Randomness:
To enhance gameplay unpredictability and replayability, randomness plays a crucial role throughout the game. It affects various aspects, such as the snake’s starting position, apple placement, and obstacle generation, which is dynamically adjusted based on the player’s score. Additionally, obstacle features like type, initial position, and movement pattern (e.g., up-down or left-right) are randomized as well. This creates a unique and engaging experience for each session, with increasing difficulty that keeps the gameplay both challenging and exciting.

### Difficulty Mode Selection:
Players can choose from three difficulty levels: easy, medium, and hard. The selected difficulty affects several aspects of gameplay, including initial game speed, probability of spawning each of the obstacle types, and speed increase rate in dynamic speed mode (if enabled). This feature allows players to customize the challenge level to match their skill and preferences, with higher difficulties providing a more intense and unpredictable experience.

### Board Size Selection:
The game includes three different board sizes: small, medium, and large. This customization enables players to tailor the gameplay experience to their preferences, with smaller boards offering a more intense and fast-paced challenge, while larger boards provide more space and a slower-paced strategy. 

### Dynamic Speed Mode: 
In this mode, the game’s speed adjusts dynamically based on the player’s performance. That is, in each score increment, the sleep time between frames decreases. To ensure a challenging yet fair experience, the game speed increases rapidly at the beginning, offering an impressive challenge. Once the score exceeds a certain threshold, the rate of change slows down, resulting in a more gradual difficulty curve as the game progresses. 

### Invisible Walls Mode
This mode allows the user to control the “transparency” of the walls. That is, if enabled the snake can traverse through the board’s boundaries, reappearing on the opposite side. This setting enhances the game customization level, provides players with an extra layer of strategic flexibility.

### Score Tracking:
The game tracks the player’s score, which increases each time the snake eats an apple. This feature contributes to the overall user experience. 
