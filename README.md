# Multiplayer Sudoku Game

A local Sudoku game written in C++ with a Qt graphical interface. One to four people can play on the same computer, taking turns to fill in a shared puzzle and earn points for correct answers. This is a university course project.

![SudokuRec2](https://github.com/Ricardo-Straub/Sudoku/assets/108030615/f93686f9-01b9-46ef-88a4-448ca9558227)

## Gameplay

- Choose the number of players and play on a shared Sudoku board.
- The game presents a puzzle with missing cells and keeps a completed solution to check guesses.
- Each correct entry adds the entered number to the current player's score.
- An incorrect guess passes the turn to the next player. A player can make at most five consecutive guesses before the turn passes, even if the guesses are correct.
- At the end of the game, the player with the highest score wins.

## Implementation

The project uses C++ and Qt for the interface and game logic. Its source includes the main window, menu window, Qt UI files, and a CMake build configuration. Guess checking uses the completed solution behind the puzzle; this is a local game, not an online multiplayer service.

## Build and run

Open `CMakeLists.txt` in a Qt installation or Qt Creator with a compatible Qt kit, configure the project, and build and run it there. The repository includes the C++ source and `.ui` files. The precise Qt version and a clean-checkout build have not been independently verified in this README.

## Scope

This is an early C++ course project, not a production-ready Sudoku application. The main focus is the playable Qt interface, turn handling, solution-based answer checking, and per-player scoring.
