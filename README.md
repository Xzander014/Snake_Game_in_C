# Snake Game in C

A simple **Snake Game** written in C that runs in the terminal. This game does not use external libraries like `ncurses` and features real-time movement, food generation, and score tracking.

## Features
- Terminal-based snake game
- Real-time movement using non-blocking input
- Random food generation avoiding snake body
- Score tracking
- Adjustable speed increase as you progress
- Simple controls

## Installation & Compilation

### Linux
To compile and run the game on Linux, use the following commands:

```sh
# Install GCC if not installed
sudo apt update && sudo apt install gcc -y

# Compile the game
gcc snake_game.c -o snake_game

# Run the game
./snake_game
```

### Windows
To compile and run the game on Windows, follow these steps:

1. Install [MinGW](https://www.mingw-w64.org/) and ensure `gcc` is in your system path.
2. Open a command prompt and navigate to the folder where `snake_game.c` is located.
3. Compile the game using:
   ```sh
   gcc snake_game.c -o snake_game.exe
   ```
4. Run the game with:
   ```sh
   snake_game.exe
   ```

## How to Play
- **W** - Move Up
- **S** - Move Down
- **A** - Move Left
- **D** - Move Right
- **X** - Exit Game

### Objective
1. Move the snake using `WASD` keys.
2. Eat `@` (food) to grow and increase your score.
3. Avoid hitting the walls or yourself.
4. The game ends if you collide with the walls or your own body.

## Dependencies
- Standard C libraries (`stdio.h`, `stdlib.h`, `time.h`, `unistd.h`, `termios.h`, `sys/select.h`)
- Compatible with Linux and macOS (may require modifications for Windows)

## To-Do (Future Improvements)
- Implement difficulty levels
- Add game-over screen with restart option
- Optimize movement for better responsiveness
- Improve UI rendering for a smoother experience

## License
This project is open-source and available under the MIT License.

## Contributing
Feel free to fork the repository, open issues, or submit pull requests to improve the game!

