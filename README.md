# BubbleBreaker

**BubbleBreaker** is a classic brick-breaking game developed using CMake. The game features a paddle, a ball, and breakable bricks that players need to destroy by bouncing the ball off the paddle.

## Features

- **Main Menu**: Upon launching the game, you are presented with the main menu. Click **Play Solo** to start the game.
- **Gameplay**:
- Use the **left** and **right arrow keys** to move the paddle.
  - The objective is to keep the ball above the paddle by bouncing it off, and destroy all the bricks on the screen.
  - If the ball falls below the paddle 3 times, you lose the game and return to the main menu.
  - If all bricks are destroyed, you win and the game returns to the main menu.

## Controls

- **Left Arrow**: Move the paddle left.
- **Right Arrow**: Move the paddle right.

## Installation

1. Clone the repository or download the source files.
2. Navigate to the project directory.
3. Run the following commands to build the project using CMake:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. After the build completes, run the game:

   ```bash
   ./BubbleBreaker
   ```

## Requirements

- CMake
- A C++ compiler that supports C++20 or higher
