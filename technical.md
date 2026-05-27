# Weird Chess Engine - Technical Documentation

Author: Leon  
Language: C++/C
Protocol: UCI (Universal Chess Interface)

---

## Architecture Overview

```
main.cpp
uci.cpp              - Reads UCI commands, talks to GUI
opening_book.cpp     - Opening book
search.cpp           - Finds the best move
quiescence.cpp       - Captures search
evaluation.cpp       - Scores positions
move_validation.cpp  - Filters illegal moves
move_generation.cpp  - Generates all moves
board.cpp            - Board state
```

Each layer depends on the one below it. `board.cpp` is the foundation everything else builds on.

---

## File Descriptions

### `board.h` / `board.cpp`
Defines the core data structures and board management.

Key structs:
```cpp
struct Square {
    PieceType piece;   // What piece is here
    Color     color;   // Whose piece
    bool      isEmpty; // Is the square empty
};

struct Board {
    Square squares[64];    // All 64 squares
    Color  sideToMove;     // Whose turn
    int    castlingRights; // Who can still castle
    int    enPassantSquare;// En passant target (-1 if none)
    int    halfMoveClock;  // For 50-move rule
    int    fullMoveNumber; // Move counter
};
```

Key functions:
- `setupStartPosition()` - Sets up the standard starting position
- `clearBoard()` - Empties the board
- `placePiece()` - Places a piece on a square
- `printBoard()` - Prints the board to the terminal
- `squareIndex(file, rank)` - Converts file/rank to 0–63 index

---

### `move_generation.h` / `move_generation.cpp`
Generates all pseudo-legal moves for every piece type.

Key structs:
```cpp
struct Move {
    int from;              // Source square (0–63)
    int to;                // Target square (0–63)
    PieceType promotion;   // Promotion piece (NONE if not a promotion)
};

struct MoveList {
    Move moves[256];  // Up to 256 moves per position
    int  count;       // How many moves are in the list
};
```

Key functions:
- `generatePawnMoves()` - Handles single/double push, captures, en passant, promotion
- `generateKnightMoves()` - All 8 L-shaped jumps
- `generateSlidingMoves()` - Bishops, rooks, queens (rays until blocked)
- `generateKingMoves()` - One step in all directions + castling
- `generateAllMoves()` - Combines all of the above

Note: These are pseudo-legal moves - they do not check if the king is left in check.

---

### `move_validation.h` / `move_validation.cpp`
Filters pseudo-legal moves down to fully legal moves.

Key functions:
- `applyMove()` - Executes a move on the board (handles en passant, castling, promotion, castling rights)
- `isSquareAttacked()` - Checks if a square is attacked by a given color
- `isInCheck()` - Checks if a king is in check
- `isLegalMove()` - Applies a move on a copy of the board and checks if the king is in check afterward
- `generateLegalMoves()` - Filters all pseudo-legal moves to only legal ones
- `isCheckmate()` - In check + no legal moves
- `isStalemate()` - Not in check + no legal moves

---

### `evaluation.h` / `evaluation.cpp`
Scores a position as a number from White's perspective.

- Positive score → White is winning
- Negative score → Black is winning
- Zero → Equal position

Components:
1. Material value - Each piece has a base value:

| Piece | Value |
|---|---|
| Pawn | 100 |
| Knight | 320 |
| Bishop | 330 |
| Rook | 500 |
| Queen | 900 |

2. Piece-square tables - Bonus points based on where a piece stands. For example knights in the center get +20, knights in corners get -50.

---

### `quiescence.h` / `quiescence.cpp`
Prevents the Horizon Effect. After normal search depth is reached, continues searching all captures until the position is quiet. Prevents the engine from missing obvious recaptures.

---

### `search.h` / `search.cpp`
Finds the best move using Negamax with Alpha-Beta pruning.

Algorithm:
```
negamax(position, depth):
    if depth == 0 → evaluate position
    for each legal move:
        make move on copy
        score = -negamax(copy, depth - 1)
        if score > best → remember this move
    return best score
```

Alpha-Beta pruning skips branches that cannot possibly improve the result - this makes the search several times faster.

Personality system:
```cpp
int personalityBonus(board, move):
    bonus += rand() % 40      // Randomness
    bonus += 50 if capture    // Aggression
    bonus += 30 if center     // Center preference
```

The personality bonus is added on top of the search score, making the engine unpredictable without sacrificing too much strength.

**Search depth:** Default is 4 (looks 4 moves ahead). Can be changed in `search.cpp`.

---
### `opening_book.h` / `opening_book.cpp`
Engine plays instantly from the book for the first 8-10 moves. Randomly chooses between multiple valid continuations for unpredictability.
Covered openings: Italian, Spanish, Sicilian, French, Caro-Kann, King's Gambit, Queen's Gambit, King's Indian, Nimzo-Indian, Gruenfeld, English, Reti, Catalan, and many more.

---

### `uci.h` / `uci.cpp`
Implements the UCI protocol so Arena and other GUIs can talk to the engine.

UCI flow:
```
GUI sends:     uci
Engine sends:  id name WeirdChessEngine
               id author Leon
               uciok

GUI sends:     isready
Engine sends:  readyok

GUI sends:     position startpos moves e2e4 e7e5
Engine reads:  applies all moves to internal board

GUI sends:     go
Engine sends:  bestmove g1f3
```

---

## Known Limitations

| Limitation | Description |
|---|---|
| No time management | Engine always searches to depth 4 (if not changed), ignoring the clock |
| No transposition table | Same positions evaluated multiple times |
| No endgame tables | Engine may struggle in simple endgames |
| Basic evaluation | Only material + piece-square tables, no pawn structure |
| No repetition detection | Engine does not avoid threefold repetition |

---

## Possible Improvements

- Move Ordering — Sort captures and checks first for better pruning 
- Time management - Stop searching when time is running low
- Transposition table - Cache previously evaluated positions (Zobrist hashing)
- Better evaluation - Pawn structure, king safety, mobility
- Iterative deepening - Search depth 1, then 2, then 3... for better move ordering