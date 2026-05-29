#include "search.h"
#include "quiescence.h"

// Figurenwerte fuer MVV-LVA
static const int MVV_LVA_VALUES[7] = {
    100,  // PAWN
    320,  // KNIGHT
    330,  // BISHOP
    500,  // ROOK
    900,  // QUEEN
    0,    // KING
    0     // NONE
};
// Schlagbewertung

int mvvLvaScore(const Board& board, const Move& move) {
    if (board.squares[move.to].isEmpty)
        return 0;

    int victimValue   = MVV_LVA_VALUES[board.squares[move.to].piece];
    int attackerValue = MVV_LVA_VALUES[board.squares[move.from].piece];

    return victimValue * 10 - attackerValue;
}
// Berechnung des Scores

void sortMoves(const Board& board, MoveList& moves) {
    // Insertion Sort — gut fuer kleine Listen
    for (int i = 1; i < moves.count; i++) {
        Move key = moves.moves[i];
        int keyScore = mvvLvaScore(board, key);
        int j = i - 1;

        while (j >= 0 && mvvLvaScore(board, moves.moves[j]) < keyScore) {
            moves.moves[j + 1] = moves.moves[j];
            j--;
        }
        moves.moves[j + 1] = key;
    }
}
// Sortierung nach MVV-LVA Score

int personalityBonus(const Board& board, const Move& move) {
    int bonus = 0;

    if (!board.squares[move.to].isEmpty)
        bonus += 50;

    int toFile = move.to % 8;
    int toRank = move.to / 8;
    if (toFile >= 3 && toFile <= 4 &&
        toRank >= 3 && toRank <= 4)
        bonus += 30;

    bonus += rand() % 40;

    return bonus;
}
// Personality Bonus -changeable

int negamax(Board board, int depth, int alpha, int beta) {
    if (depth == 0)
        return quiescence(board, alpha, beta);

    MoveList moves = generateLegalMoves(board);

    if (moves.count == 0) {
        if (isInCheck(board, board.sideToMove))
            return -100000;
        return 0;
    }

    // Move Ordering — Schlaege zuerst!
    sortMoves(board, moves);

    int best = -999999;

    for (int i = 0; i < moves.count; i++) {
        Board copy = board;
        applyMove(copy, moves.moves[i]);

        int score = -negamax(copy, depth - 1, -beta, -alpha);

        if (score > best)
            best = score;
        if (score > alpha)
            alpha = score;
        if (alpha >= beta)
            break;
    }

    return best;
}
// Negamax mit Alpha-Beta Pruning

SearchResult findBestMove(const Board& board, int depth) {
    srand(time(nullptr));

    MoveList moves = generateLegalMoves(board);
    SearchResult result;
    result.score = -999999;
    if (moves.count == 0) {
        result.bestMove = {};
        return result;
    }
    result.bestMove = moves.moves[0];

    // Moves sortieren
    sortMoves(board, moves);

    for (int i = 0; i < moves.count; i++) {
        Board copy = board;
        applyMove(copy, moves.moves[i]);

        int score = -negamax(copy, depth - 1, -999999, 999999);

        // Personality Bonus nur auf oberster Ebene
        score += personalityBonus(board, moves.moves[i]);

        if (score > result.score) {
            result.score    = score;
            result.bestMove = moves.moves[i];
        }
    }

    return result;
}
// Hauptfunktion zur Suche des besten Zuges


