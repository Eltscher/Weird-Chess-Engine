#include "move_validation.h"

void applyMove(Board& board, const Move& move) {
    Square from = board.squares[move.from];

    board.squares[move.to].piece   = from.piece;
    board.squares[move.to].color   = from.color;
    board.squares[move.to].isEmpty = false;

    board.squares[move.from].piece   = NONE;
    board.squares[move.from].color   = WHITE;
    board.squares[move.from].isEmpty = true;

//Führt einen Zug aus

    if (move.promotion != NONE)
        board.squares[move.to].piece = move.promotion;
    
    if (from.piece == PAWN) {
            int fromFile = move.from % 8;
            int toFile   = move.to % 8;
            if (fromFile != toFile && board.enPassantSquare == move.to) {
                int capturedPawnIdx = (from.color == WHITE)
                    ? move.to - 8
                    : move.to + 8;
                board.squares[capturedPawnIdx].piece   = NONE;
                board.squares[capturedPawnIdx].color   = WHITE;
                board.squares[capturedPawnIdx].isEmpty = true;
            }
            if (std::abs(move.to - move.from) == 16)
                board.enPassantSquare = (move.from + move.to) / 2;
            else
                board.enPassantSquare = -1;
        } else {
            board.enPassantSquare = -1;
        }
// EN PASSANT-Logik

    if (from.piece == KING) {
            int diff = move.to - move.from;
            if (diff == 2) {
                int rookFrom = move.from + 3;
                int rookTo   = move.from + 1;
                board.squares[rookTo].piece     = ROOK;
                board.squares[rookTo].color     = from.color;
                board.squares[rookTo].isEmpty   = false;
                board.squares[rookFrom].piece   = NONE;
                board.squares[rookFrom].isEmpty = true;
            }
            if (diff == -2) {
                int rookFrom = move.from - 4;
                int rookTo   = move.from - 1;
                board.squares[rookTo].piece     = ROOK;
                board.squares[rookTo].color     = from.color;
                board.squares[rookTo].isEmpty   = false;
                board.squares[rookFrom].piece   = NONE;
                board.squares[rookFrom].isEmpty = true;
            }
        }
        if (board.squares[squareIndex(4,0)].piece != KING ||
        board.squares[squareIndex(4,0)].color != WHITE)
        board.castlingRights &= ~(WHITE_KINGSIDE | WHITE_QUEENSIDE);

    if (board.squares[squareIndex(4,7)].piece != KING ||
        board.squares[squareIndex(4,7)].color != BLACK)
        board.castlingRights &= ~(BLACK_KINGSIDE | BLACK_QUEENSIDE);

    if (board.squares[squareIndex(0,0)].piece != ROOK ||
        board.squares[squareIndex(0,0)].color != WHITE)
        board.castlingRights &= ~WHITE_QUEENSIDE;

    if (board.squares[squareIndex(7,0)].piece != ROOK ||
        board.squares[squareIndex(7,0)].color != WHITE)
        board.castlingRights &= ~WHITE_KINGSIDE;

    if (board.squares[squareIndex(0,7)].piece != ROOK ||
        board.squares[squareIndex(0,7)].color != BLACK)
        board.castlingRights &= ~BLACK_QUEENSIDE;

    if (board.squares[squareIndex(7,7)].piece != ROOK ||
        board.squares[squareIndex(7,7)].color != BLACK)
        board.castlingRights &= ~BLACK_KINGSIDE;

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