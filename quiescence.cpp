#include "quiescence.h"

int quiescence(Board board, int alpha, int beta) {
    // Aktuelle Position bewerten
    int stand_pat = evaluateBoard(board) *
                   (board.sideToMove == WHITE ? 1 : -1);
// Bewertung der position

    // Beta Cutoff
    if (stand_pat >= beta)
        return beta;

    // Alpha aktualisieren
    if (stand_pat > alpha)
        alpha = stand_pat;
//Alpha-Beta Pruning

    // Nur Schläge generieren - Filter
    MoveList allMoves = generateLegalMoves(board);
    MoveList captures;
    captures.count = 0;

    for (int i = 0; i < allMoves.count; i++) {
        if (!board.squares[allMoves.moves[i].to].isEmpty)
            addMove(captures,
                    allMoves.moves[i].from,
                    allMoves.moves[i].to,
                    allMoves.moves[i].promotion);
    }

    // Alle Schläge untersuchen
    for (int i = 0; i < captures.count; i++) {
        Board copy = board;
        applyMove(copy, captures.moves[i]);

        int score = -quiescence(copy, -beta, -alpha);

        if (score >= beta)
            return beta;
        if (score > alpha)
            alpha = score;
    }

    return alpha;
}
