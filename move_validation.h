#ifndef MOVE_VALIDATION_H
#define MOVE_VALIDATION_H

#include "move_generation.h"

void applyMove(Board& board, const Move& move);
bool isSquareAttacked(const Board& board, int square, Color byColor);
bool isInCheck(const Board& board, Color color);
bool isLegalMove(Board board, const Move& move, Color us);
MoveList generateLegalMoves(const Board& board);
bool isCheckmate(const Board& board);
bool isStalemate(const Board& board);

//Funktion, um einen Zug auf dem Brett auszuführen (für die Validierung)

#endif