#include "move_validation.h"

void applyMove(Board& board, const Move& move) {
    Square& from = board.squares[move.from];
    Square& to   = board.squares[move.to];

    to.piece   = from.piece;
    to.color   = from.color;
    to.isEmpty = false;

    from.piece   = NONE;
    from.color   = WHITE;
    from.isEmpty = true;

//Führt einen Zug aus

        if (move.promotion != NONE) {
            to.piece = move.promotion; // Umwandlung bei Bauern
        }
    
    if (from.piece == PAWN) {
        int fromFile = move.from % 8;
        int fromRank = move.from / 8;
        int toFile   = move.to % 8;
        int toRank   = move.to / 8;

        if (fromFile != toFile && board.squares[move.to].isEmpty) {
            int capturedPawnIdx = (board.sideToMove == WHITE)
                ? move.to - 8
                : move.to + 8;
            board.squares[capturedPawnIdx].piece   = NONE;
            board.squares[capturedPawnIdx].color   = WHITE;
            board.squares[capturedPawnIdx].isEmpty = true;
            }
    }
// EN PASSANT-Logik

    if (from.piece == KING) {
        int diff = move.to - move.from;
        if (diff == 2) {
            int rookFrom = move.from + 3;
            int rookTo   = move.from + 1;
            board.squares[rookTo].piece     = ROOK;
            board.squares[rookTo].color     = board.squares[rookFrom].color;
            board.squares[rookTo].isEmpty   = false;
            board.squares[rookFrom].piece   = NONE;
            board.squares[rookFrom].isEmpty = true;
        }
        if (diff == -2) {
            int rookFrom = move.from - 4;
            int rookTo   = move.from - 1;
            board.squares[rookTo].piece     = ROOK;
            board.squares[rookTo].color     = board.squares[rookFrom].color;
            board.squares[rookTo].isEmpty   = false;
            board.squares[rookFrom].piece   = NONE;
            board.squares[rookFrom].isEmpty = true;
        }
    }

    board.sideToMove = (board.sideToMove == WHITE) ? BLACK : WHITE;
}
// ROCHADEN-Logik

bool isSquareAttacked(const Board& board, int square, Color byColor) {
    for (int idx = 0; idx < 64; idx++) {
        const Square& sq = board.squares[idx];
        if (sq.isEmpty || sq.color != byColor) continue;
        MoveList list;
        list.count = 0;

        switch (sq.piece) {
            case PAWN:
                generatePawnMoves(board, idx, byColor, list);
                break;
            case KNIGHT:
                generateKnightMoves(board, idx, byColor, list);
                break;
            case BISHOP:
                generateSlidingMoves(board, idx, byColor, list, true, false);
                break;
            case ROOK:
                generateSlidingMoves(board, idx, byColor, list, false, true);
                break;
            case QUEEN:
                generateSlidingMoves(board, idx, byColor, list, true, true);
                break;
            case KING:
                generateKingMoves(board, idx, byColor, list);
                break;
            default: break;
        }
// Generiert alle Züge dieser Figur und prüft ob das gesuchte Feld dabei ist

        for (int i = 0; i < list.count; i++) {
            if (list.moves[i].to == square) {
                return true;
            }
        }
    }
    return false;
}
// Greift Feld an

bool isInCheck(const Board& board, Color color) {
    // König finden
    int kingSquare = -1;
    for (int idx = 0; idx < 64; idx++) {
        if (!board.squares[idx].isEmpty &&
             board.squares[idx].piece == KING &&
             board.squares[idx].color == color) {
            kingSquare = idx;
            break;
        }
    }
// Sucht den König

if (kingSquare == -1) return false;

    Color enemy = (color == WHITE) ? BLACK : WHITE;
    return isSquareAttacked(board, kingSquare, enemy);
}
// Prüft ob der König im Schach steht

bool isLegalMove(Board board, const Move& move, Color us) {
    applyMove(board, move);
    return !isInCheck(board, us);
}
// Prüft ob ein Zug legal ist, indem er ihn auf einem Kopie des Bretts ausführt

MoveList generateLegalMoves(const Board& board) {
    MoveList pseudoLegal = generateAllMoves(board);
    MoveList legal;
    legal.count = 0;
    Color us = board.sideToMove;

    for (int i = 0; i < pseudoLegal.count; i++) {
        if (isLegalMove(board, pseudoLegal.moves[i], us))
            addMove(legal, pseudoLegal.moves[i].from,
                           pseudoLegal.moves[i].to,
                           pseudoLegal.moves[i].promotion);
    }
    return legal;
}
// Generiert alle legalen Züge, indem er die Pseudo-legalen Züge filtert

bool isCheckmate(const Board& board) {
    if (!isInCheck(board, board.sideToMove)) return false;
    return generateLegalMoves(board).count == 0;
}
// Prüft ob es Schachmatt ist

bool isStalemate(const Board& board) {
    if (isInCheck(board, board.sideToMove)) return false;
    return generateLegalMoves(board).count == 0;
}
// Prüft ob es Patt ist