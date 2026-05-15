#include "search.h"

int negamax(Board board, int depth, int alpha, int beta) {
    if (depth == 0)
        return evaluateBoard(board) * 
               (board.sideToMove == WHITE ? 1 : -1);
// Suche - Basis ist Negam -> Variante von Minmax

 MoveList moves = generateLegalMoves(board);

    if (moves.count == 0) {
        if (isInCheck(board, board.sideToMove))
            return -100000; // Schachmatt
        return 0;           // Patt
    }
// Erkennung Schachmatt oder Patt

    for (int i = moves.count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Move temp       = moves.moves[i];
        moves.moves[i]  = moves.moves[j];
        moves.moves[j]  = temp;
    }
// Zufällige Sortierung der Züge

    int best = -999999;

    for (int i = 0; i < moves.count; i++) {
        Board copy = board;
        applyMove(copy, moves.moves[i]);
        copy.sideToMove = (board.sideToMove == WHITE) ? BLACK : WHITE;

        int score = -negamax(copy, depth - 1, -beta, -alpha);

        if (score > best)
            best = score;
        if (score > alpha)
            alpha = score;
        if (alpha >= beta)
            break; // Beta-Cutoff
    }

    return best;
}
// Negamax-Algorithmus mit Alpha-Beta-Schnitt
//alpha → bester Score den gefunden konnte
//beta → bester Score den der Gegner zulassen würde

int personalityBonus(const Board& board, const Move& move) {
    int bonus = 0;

    // Schlagen bevorzugen
    if (!board.squares[move.to].isEmpty)
        bonus += 50;

    // Zentrumskontrolle bevorzugen
    int toFile = move.to % 8;
    int toRank = move.to / 8;
    if (toFile >= 3 && toFile <= 4 &&
        toRank >= 3 && toRank <= 4)
        bonus += 30;

    // Leichte Zufälligkeit
    bonus += rand() % 40;

    return bonus;
}
//Persönlichkeit: Gibt bestimmten Zügen einen Bonus

SearchResult findBestMove(const Board& board, int depth) {
    srand(time(nullptr));

    MoveList moves = generateLegalMoves(board);
    SearchResult result;
    result.score = -999999;

    // Fallback
    result.bestMove = moves.moves[0];
//Initialisiert die Suche

   for (int i = 0; i < moves.count; i++) {
        Board copy = board;
        applyMove(copy, moves.moves[i]);
        copy.sideToMove = (board.sideToMove == WHITE) ? BLACK : WHITE;

        int score = -negamax(copy, depth - 1, -999999, 999999);

        // Personality Bonus hinzufügen
        score += personalityBonus(board, moves.moves[i]);

        if (score > result.score) {
            result.score    = score;
            result.bestMove = moves.moves[i];
        }
    }

    return result;
}
//Geht alle Züge durch und findet den besten

