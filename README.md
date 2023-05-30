# Hangman

## Description
* This is a console-based Hangman game written in C++. The objective of the game is to guess a hidden word by entering one letter at a time. The game supports two modes: Solo Play and Multiplayer. In Solo Play mode, you play against the computer, while in Multiplayer mode, you can play with your friends.

* The game offers different difficulty levels: easy, medium, hard, and impossible. Each difficulty level has a different number of allowed attempts and corresponding points. The goal is to accumulate a total of 20 points to win the game. Winning at the impossible level instantly grants you 20 points and leads to victory.

## Technologies Used
The Hangman game is implemented in C++ and uses the following libraries:

* windows.h: Used for Windows-specific console functions.
* iostream: Used for input/output operations.
* fstream: Used for file input/output operations.
* conio.h: Used for console input/output operations.
* string: Used for string manipulation.
* ctime: Used for time-related operations.
* vector: Used for creating and manipulating dynamic arrays.

## Setup and Execution
To run the Hangman game, follow these steps:

1. Clone the repository: git clone https://github.com/your-username/hangman-game.git.
2. Navigate to the project directory: cd hangman-game.
3. Compile the source code: g++ hangman.cpp -o hangman.
4. Run the executable: ./hangman.

## How to Play
1. Launch the game by following the setup instructions.
2. Select the desired game mode:
   * Solo Play (1): Play against the computer.
   * Play with Friends (2): Multiplayer mode to play with friends.
3. For Solo Play:
   1. Choose the difficulty level: (1) easy, (2) medium, (3) hard, (4) impossible.
   2. Guess the hidden word by entering one letter at a time.
   3. Each correct guess earns you points based on the difficulty level.
   4. Accumulate 20 points to win the game.
4. For Multiplayer:
   1. Each player takes turns choosing a challenging word for the opponents to guess.
   2. Enter a word with at least 3 characters.
   3. The chosen word will make it harder for the opponents to guess.
   4. Players earn points for correct guesses and lose points for incorrect guesses.
   5. The game continues until a player reaches the target score or runs out of attempts.

## Acknowledgements
This project was created by [your-name]. Feel free to contribute to the repository and improve the game. Have fun playing Hangman!
