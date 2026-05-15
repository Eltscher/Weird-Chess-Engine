#ifndef SEARCH_H
#define SEARCH_H

#include "evaluation.h"
#include <cstdlib>
#include <ctime>

struct SearchResult {
    Move  bestMove;
    int   score;
};

SearchResult findBestMove(const Board& board, int depth);

#endif