#ifndef UCI_H
#define UCI_H

#include "search.h"
#include "opening_book.h"
#include <string>
#include <sstream>
#include <vector>

void uciLoop();
Move parseMoveString(const Board& board, const std::string& moveStr);
void applyMovesFromString(Board& board, const std::string& movesStr);

#endif