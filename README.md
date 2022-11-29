# Go
A game of [Go](https://en.wikipedia.org/wiki/Go_(game)) played on the command line

## Compilation
Use **CMake** with the provided **CMakeLists.txt** file or compile directly using your preferred C compiler. For example, the following command compiles the source code into an executable named "go" using GCC:
```bash
cd src
gcc main.c board.c display.c rule.c play.c -I../include -o go
```

## Gameplay
A game session can be initiated by running the compiled executable, after which the following will be shown on the console.
```
    A   B   C   D   E   F   G   H   I
  +---+---+---+---+---+---+---+---+---+
9 |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+
8 |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+
7 |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+
6 |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+
5 |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+
4 |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+
3 |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+
2 |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+
1 |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+
             X's prisoner: 0
             O's prisoner: 0
Enter:
   (1) a coordinate ([A-I][1-9]) to place a stone
   (2) P to pass
   (3) U to undo last move
X's move:
```
Each player then takes turn making a move. A move must be in the format **[A-I][1-9]** (case-insensitive) representing a coordinate on the 9x9 board.

Other possible moves include:
- **P** to pass
- **U** to undo last move

Invalid moves that cannot be played include:
- Playing on already occupied coordinate
- Suicide

**NOTE: Ko rules are not implemented**

Once two **P**'s have been played consecutively, the game will end and both player must choose groups that will be removed from the board. Enter **P** when the removal has finished.

Score will be calculated using territory scoring with 6.5 Komi. Komi can be modified in **include/rule.h**.