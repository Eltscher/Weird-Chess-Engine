#ifndef OPENING_BOOK_H
#define OPENING_BOOK_H

#include "move_validation.h"
#include <vector>
#include <string>

struct BookEntry {
    std::string moves;
    std::string name;
};

bool isInOpeningBook(const std::vector<std::string>& playedMoves);
Move getBookMove(const Board& board, const std::vector<std::string>& playedMoves);
bool hasBookMove(const std::vector<std::string>& playedMoves);

#endif