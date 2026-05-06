Make an interessting chess engine
Workflow:
GUI sends position
      ↓
Engine reads the board
      ↓
Move Generator creates all legal moves
      ↓
Search tries each move recursively
      ↓
Evaluation scores each resulting position
      ↓
Search picks the best move
      ↓
Engine sends "bestmove" back to GUI