#ifndef UCI_H
#define UCI_H

#include "search.h"
#include <string>
#include <sstream>

void uciLoop();
Move parseMoveString(const Board& board, const std::string& moveStr);
void applyMovesFromString(Board& board, const std::string& movesStr);

#endif