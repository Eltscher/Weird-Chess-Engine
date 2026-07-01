#include "search.h"
#include "quiescence.h"
#include "transposition.h"

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

    bonus += rand() % 70;

    return bonus;
}
// Personality Bonus -changeable

// Erkenmung ob Endspiel
bool isEndgame(const Board& board) {
    int pieceCount = 0;
    for (int i = 0; i < 64; i++) {
        if (!board.squares[i].isEmpty &&
             board.squares[i].piece != PAWN &&
             board.squares[i].piece != KING)
            pieceCount++;
    }
    return pieceCount <= 4; // Wenig Figuren = Endspiel
}

int negamax(Board board, int depth, int alpha, int beta,
            bool nullMoveAllowed) {
    // Transposition Table abfragen
    uint64_t hash = computeHash(board);
    int ttScore;
    if (ttProbe(hash, depth, alpha, beta, ttScore))
        return ttScore;

    if (depth == 0)
        return quiescence(board, alpha, beta);

    MoveList moves = generateLegalMoves(board);

    if (moves.count == 0) {
        if (isInCheck(board, board.sideToMove))
            return -100000;
        return 0;
    }
    
    // Null Move Pruning
    if (nullMoveAllowed &&
        depth >= 3 &&
        !isInCheck(board, board.sideToMove) &&
        !isEndgame(board)) {

        // Passzug machen
        Board nullBoard = board;
        nullBoard.sideToMove = (board.sideToMove == WHITE) ? BLACK : WHITE;
        nullBoard.enPassantSquare = -1;

        // Mit reduzierter Tiefe suchen (R=2)
        int nullScore = -negamax(nullBoard, depth - 3, -beta, -beta + 1, false);

        if (nullScore >= beta) {
            ttStore(hash, beta, depth, TT_BETA);
            return beta;
        }
    }

    sortMoves(board, moves);

    int best    = -999999;
    TTFlag flag = TT_ALPHA;
    int    movesSearched = 0;

    for (int i = 0; i < moves.count; i++) {
        Board copy = board;
        applyMove(copy, moves.moves[i]);

        int score;
        bool isCapture = !board.squares[moves.moves[i].to].isEmpty;
        bool inCheck   = isInCheck(copy, copy.sideToMove);
        //LMR

        if (movesSearched >= 3 &&
            depth >= 3 &&
            !isCapture &&
            !inCheck &&
            !isInCheck(board, board.sideToMove)) {

            int reduction = 1;
            if (movesSearched >= 6) reduction = 2;

            score = -negamax(copy, depth - 1 - reduction,
                             -alpha - 1, -alpha, true);

            if (score > alpha)
                score = -negamax(copy, depth - 1, -beta, -alpha, true);

        } else {
            score = -negamax(copy, depth - 1, -beta, -alpha, true);
        }

        movesSearched++;

        if (score > best) {
            best = score;
            if (score > alpha) {
                alpha = score;
                flag  = TT_EXACT;
            }
        }
        if (alpha >= beta) {
            ttStore(hash, beta, depth, TT_BETA);
            return beta;
        }
    }

    ttStore(hash, best, depth, flag);
    return best;
}
// Negamax mit Alpha-Beta-Schnitt und Transposition Table

SearchResult findBestMove(const Board& board, int maxDepth) {
    srand(time(nullptr));

    MoveList moves = generateLegalMoves(board);
    SearchResult result;
    result.score = -999999;
    result.bestMove = moves.moves[0];
    result.depth    = 1;

    for (int depth = 1; depth <= maxDepth; depth++) {
        int        bestScore    = -999999;
        Move       bestMove     = moves.moves[0];

        sortMoves(board, moves);

        for (int i = 0; i < moves.count; i++) {
            Board copy = board;
            applyMove(copy, moves.moves[i]);

            int score = -negamax(copy, depth - 1, -999999, 999999, true);

            // Personality Bonus nur auf oberster Ebene
            score += personalityBonus(board, moves.moves[i]);

            if (score > bestScore) {
                bestScore = score;
                bestMove  = moves.moves[i];
            }
        }

        // Ergebnis dieser Tiefe speichern
        result.score    = bestScore;
        result.bestMove = bestMove;
        result.depth    = depth;
    }

    return result;
}
// Hauptfunktion zur Suche des besten Zuges


