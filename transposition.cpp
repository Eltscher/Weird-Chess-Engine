#include "transposition.h"
#include <cstdlib>
#include <cstring>

static uint64_t ZOBRIST_PIECES[2][6][64];
static uint64_t ZOBRIST_SIDE;
static TTEntry  TT[TT_SIZE];
//Zufallszahlengenerator für Zobrist-Hashing initialisieren

static uint64_t rand64() {
    return ((uint64_t)rand()) ^
           ((uint64_t)rand() << 15) ^
           ((uint64_t)rand() << 30) ^
           ((uint64_t)rand() << 45) ^
           ((uint64_t)rand() << 60);
}
//Zufällige 64-Bit-Zahl generieren

void initZobrist() {
    srand(12345); // Fester Seed für reproduzierbare Hashes

    for (int color = 0; color < 2; color++)
        for (int piece = 0; piece < 6; piece++)
            for (int sq = 0; sq < 64; sq++)
                ZOBRIST_PIECES[color][piece][sq] = rand64();

    ZOBRIST_SIDE = rand64();
    ttClear();
}
//Zobrist-Hashing-Tabellen initialisieren

uint64_t computeHash(const Board& board) {
    uint64_t hash = 0;

    for (int sq = 0; sq < 64; sq++) {
        const Square& s = board.squares[sq];
        if (!s.isEmpty)
            hash ^= ZOBRIST_PIECES[s.color][s.piece][sq];
    }

    if (board.sideToMove == BLACK)
        hash ^= ZOBRIST_SIDE;

    return hash;
}
//Zobrist-Hash für die aktuelle Stellung berechnen

void ttStore(uint64_t hash, int score, int depth, TTFlag flag) {
    int idx = hash % TT_SIZE;
    TT[idx].hash  = hash;
    TT[idx].score = score;
    TT[idx].depth = depth;
    TT[idx].flag  = flag;
    TT[idx].valid = true;
}
//Eintrag in die Transpositionstabelle speichern

bool ttProbe(uint64_t hash, int depth,
             int alpha, int beta, int& score) {
    int idx = hash % TT_SIZE;
    TTEntry& entry = TT[idx];

    if (!entry.valid || entry.hash != hash)
        return false;

    if (entry.depth < depth)
        return false;

    if (entry.flag == TT_EXACT) {
        score = entry.score;
        return true;
    }
    if (entry.flag == TT_ALPHA && entry.score <= alpha) {
        score = alpha;
        return true;
    }
    if (entry.flag == TT_BETA && entry.score >= beta) {
        score = beta;
        return true;
    }

    return false;
}
//Eintrag in der Transpositionstabelle abfragen

void ttClear() {
    memset(TT, 0, sizeof(TT)); //Alle Einträge in der Transpositionstabelle auf ungültig setzen
}
//Transpositionstabelle leeren
