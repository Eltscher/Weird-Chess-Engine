# Weird Chess Engine — How to Use

## Requirements

- Windows 10 or higher
- [MinGW](https://winlibs.com) installed (g++ compiler)
- [Arena Chess GUI](http://www.playwitharena.de) to play against the engine

---

## Installation

1. File Structure

Make sure the following files are all in the same folder:

```
Weird Chess Engine/
├── board.h
├── board.cpp
├── move_generation.h
├── move_generation.cpp
├── move_validation.h
├── move_validation.cpp
├── evaluation.h
├── evaluation.cpp
├── quiescence.h
├── quiescence.cpp
├── search.h
├── search.cpp
├── opening_book.h
├── opening_book.cpp
├── uci.h
├── uci.cpp
└── main.cpp
```

2. Compile the Engine

Open a terminal (CMD or PowerShell) in the project folder and type:

```bash
g++ -O2 -o Weird Chess Engine main.cpp board.cpp move_generation.cpp move_validation.cpp evaluation.cpp quiescence.cpp search.cpp uci.cpp opening_book.cpp
```

This creates a `Weird Chess Engine.exe` in your folder — that is your engine.

---

Loading the Engine in Arena

1. Start Arena Chess GUI
2. Click `Engines` → `Install New Engine`
3. Select your `chess.exe`
4. In the Engine Management window, set Type to `UCI`
5. Click `Apply` → `OK`
6. The engine now appears as Weird Chess Engine

---

## Playing Against the Engine

1. Click `Engines` → `Manage`
2. Select Weird Chess Engine
3. Click `New Game`
4. Choose your color (White or Black)
5. The game begins!

---

## Adjusting Difficulty

The engine strength is controlled by the search depth in `search.cpp`.

Find this line:

```cpp
SearchResult result = findBestMove(board, 4);
```

Change the `4` as desired:

| Depth | Strength | Speed |
|---|---|---|
| 2 | Very weak | Instant |
| 3 | Weak | Very fast |
| 4 | Medium (Default) | Fast |
| 5 | Strong | Slower |
| 6 | Very strong | Slow |

After changing, recompile:

```bash
g++ -O2 -o Weird Chess Engine main.cpp board.cpp move_generation.cpp move_validation.cpp evaluation.cpp quiescence.cpp search.cpp uci.cpp opening_book.cpp
```

---

## Adjusting the Personality

The engine has a built-in personality that makes it unpredictable.
It is controlled in `search.cpp`:

```cpp
// Randomness — higher = more unpredictable
bonus += rand() % 40;

// Aggression — prefer capturing pieces
if (!board.squares[move.to].isEmpty)
    bonus += 50;

// Center control — prefer central squares
if (toFile >= 3 && toFile <= 4 &&
    toRank >= 3 && toRank <= 4)
    bonus += 30;
```
---

## Common Errors

| Error | Solution |
|---|---|
| `g++` not recognized | Install MinGW and set PATH |
| Engine does not appear in Arena | Set Type to UCI in Engine Management |
| Engine is too slow | Reduce search depth to 3 |
