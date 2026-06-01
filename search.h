#ifndef SEARCH_H
#define SEARCH_H

#include "evaluation.h"
#include "quiescence.h"
#include "transposition.h"
#include <cstdlib>
#include <ctime>
#include <chrono>

struct SearchResult {
    Move  bestMove;
    int   score;
    int   depth;
};

bool         isEndgame(const Board& board);
int          negamax(Board board, int depth, int alpha, int beta, bool nullMoveAllowed);
SearchResult findBestMove(const Board& board, int maxDepth);

#endif