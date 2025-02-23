# *Chessie - Chess Engine prototype - bitboard representation, move validation and game evaluation*

**Author:** *Daniel Kuchta*

**Type:** *Game Engine*

**Target Platform:** *Linux*

**Perceived difficulty:** *60h*

*Short description and motivation:*

The main purpose of the program is really just to provide me and/or other possible future contributors/tinkerers with a deeper insigth into the development of chess AI. The program should serve as a basis for further development of chess AI and testing various approaches. It offers efficient bitboard representation for the game state as well as functions for validating moves, loading from and storing to a .txt file, making a naive next move and printing current game status such as when there is a checkmate or castling on the board.

## User interface
The motivation is reflected in the user interface or more precisely in the absence of it in the standard meaning of the word. The main interface is CLI and the program's documentation.

### CLI
Running the program with '--help' argument returns the following: 

The software provides basic chess engine functionality such as recording your games, playing for a single or both players, checking the validity of a move or evaluating a players position. You can run it interactively, use it to automate some chess-related workflow or even use it as a simple opponent. You can run the program with several arguments:
</br>-n --new For a new game session. 
</br>-f --file  The path to the input game file. Please note that if the game is finished the program will 
</br>-l --log The path to the output log file.
</br>-e --eval Returns evaluation of a player's position based on the provided ID - 0 = white 1 = black. 

*A few examples of running the program:*
</br>*chessie -n*
</br>stdout: Waiting for white's move.
</br>stdin: A7::A5

*chessie --file 23010903.txt -e 0*
</br>stdout: The white won the game. 
</br>stdout: The game is over.

### Library

1. int get_current_value(int player)
2. bool is_valid(Move move, int player)
3. void make_move(Move move, int player)
4. int load_game_from_txt(string path)
5. void save_game_to_txt(string path)
6. string get_game_status()
7. Move make_move_naive(int player)

## Architecture

*Describe, in short, higher level architecture of your program. Main components, networking, APIs...*
As of now, the program has 3 main components:

1. Game mechanic - attack tables, bitboard representation, move validation
2. Move maker - simple heuristic for making naive moves
3. Utilities  - option parsing, laoding game from a file, setting up the environment, logging to a file

## Development & Testing
**Build system:** *CMake*

**Testing Framework:** *GoogleTest*

**Required libraries/frameworks:** TBD during the development

*What parts of the code would you like to test and how?*

Unit tests: 

1. move validation - various scenarios with valid and invalid moves 
2. storing & loading game to and from a .txt file 

Functional tests: 

1. a few end-to-end game testing scenarios with both valid and attempted invalid moves 

Performance tests:

1. evaluations / sec 
2. next_move / sec - especially interesting if more sophisticated strategies were developed 

## Acceptance criteria
**Minimum Viable Product:**

MVP should include the functions for game representation, storing and loading from a .txt file and be able to validate moves. This all should be done utilizing bitboards for efficient manipulation and representation of the game. Also, it's a de facto industry standard. 

**Extensions:**

An obvious next step would be to implement more sophisticated search and AI strategies for making moves. Then, I would like to implement a graphical UI. 