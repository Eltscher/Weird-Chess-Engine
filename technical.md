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
time_management.cpp  - Calculates search depth based on clock
transposition.cpp    - Zobrist hashing + caching
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
1. Material value
2. Piece-square tables (endgame-aware King table)
3. Pawn structure:
   - Doubled pawns: -30 per extra pawn on same file
   - Isolated pawns: -20 if no pawns on adjacent files
4. King safety (middlegame only):
   - Pawn shield: +10 per pawn in front of king
   - King in center: -20
5. Rook activity:
   - Open file bonus: +25

---

### `quiescence.h` / `quiescence.cpp`
Prevents the Horizon Effect. After normal search depth is reached, continues searching all captures until the position is quiet. Prevents the engine from missing obvious recaptures.

---

### `search.h` / `search.cpp`
Finds the best move using Negamax with Alpha-Beta pruning, Iterative Deepening and Null Move Pruning.

Algorithm:
```
negamax(position, depth, nullMoveAllowed):
    probe transposition table
    if depth == 0 → quiescence search
    if nullMoveAllowed → try null move pruning
    for each legal move (sorted by MVV-LVA):
        make move on copy
        score = -negamax(copy, depth - 1, true)
        if score > best → remember this move
    store in transposition table
    return best score
```

Iterative Deepening: searches depth 1, then 2, then 3... up to maxDepth.
Each iteration uses results from the previous one for better move ordering.

Null Move Pruning: if passing the turn still results in a score >= beta,
the branch is pruned. Disabled in check and endgame positions.

Move Ordering (MVV-LVA): captures are searched first, sorted by
Most Valuable Victim - Least Valuable Attacker.

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

### `transposition.h` / `transposition.cpp`
Implements Zobrist hashing and a transposition table.
Prevents the same position from being evaluated multiple times.
Stores exact scores, upper bounds (TT_ALPHA) and lower bounds (TT_BETA).

---

### `time_management.h` / `time_management.cpp`
Reads wtime, btime, winc, binc and movetime from UCI go command.
Calculates optimal search depth based on remaining time.
Depth 1-5 depending on time per move.

---

## Known Limitations

| Limitation | Description |
|---|---|
| No repetition detection | May repeat moves in drawn positions |
| No endgame tables | Struggles in K+P vs K endgames |
| No NNUE | Uses handcrafted evaluation instead of neural network |
| Basic pawn evaluation | No passed pawns or pawn chains |

---

## Possible Improvements

- Better evaluation - Pawn structure, king safety, mobility
- Late Move Reduction — reduce depth for moves later in the list
- Endgame tables — perfect play in simple endgames
- Repetition detection — avoid drawing in winning positions
- NNUE — neural network evaluation like Stockfish