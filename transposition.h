#ifndef TRANSPOSITION_H
#define TRANSPOSITION_H
#include "board.h"
#include <cstdint>

// Eintragstypen
enum TTFlag {
    TT_EXACT = 0,  // Exakter Score
    TT_ALPHA = 1,  // Upper bound
    TT_BETA  = 2   // Lower bound
};

struct TTEntry {
    uint64_t hash;   // Zobrist Hash der Position
    int      score;  // Bewertung
    int      depth;  // Suchtiefe
    TTFlag   flag;   // Typ des Eintrags
    bool     valid;  // Ist der Eintrag gueltig?
};

// Groesse der Tabelle (2^17 = ~131.000 Eintraege)
const int TT_SIZE = 1 << 17;

void     initZobrist();
uint64_t computeHash(const Board& board);
void     ttStore(uint64_t hash, int score, int depth, TTFlag flag);
bool     ttProbe(uint64_t hash, int depth, int alpha, int beta, int& score);
void     ttClear();


#endif