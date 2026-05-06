#ifndef MOVE_GENERATION_H
#define MOVE_GENERATION_H

#include "board.h"

struct Move {
    int       from;
    int       to;
    PieceType promotion;
};

struct MoveList {
    Move moves[256];
    int  count;
};

// Funktions-Signaturen
void     addMove(MoveList& list, int from, int to, PieceType promotion = NONE);
bool     isOnBoard(int file, int rank);
bool     isEnemy(const Board& board, int idx, Color us);
bool     isEmpty(const Board& board, int idx);
void     generatePawnMoves(const Board& board, int idx, Color us, MoveList& list);
void     generateKnightMoves(const Board& board, int idx, Color us, MoveList& list);
void     generateSlidingMoves(const Board& board, int idx, Color us, MoveList& list, bool diagonal, bool straight);
void     generateKingMoves(const Board& board, int idx, Color us, MoveList& list);
MoveList generateAllMoves(const Board& board);

#endif