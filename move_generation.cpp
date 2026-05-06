#include "move_generation.h"
#include <cmath>

void addMove(MoveList& list, int from, int to,
             PieceType promotion = NONE) {
    list.moves[list.count].from      = from;
    list.moves[list.count].to        = to;
    list.moves[list.count].promotion = promotion;
    list.count++;
}
//Fügt einen Zug zur Liste hinzu

bool isOnBoard(int file, int rank) {
    return file >= 0 && file <= 7 &&
           rank >= 0 && rank <= 7;
}
// ist ein Feld auf dem Brett?

bool isEnemy(const Board& board, int idx, Color us) {
    if (board.squares[idx].isEmpty) return false;
    return board.squares[idx].color != us;
}
// ist auf einem Feld eine gegnerische Figur?

bool isEmpty(const Board& board, int idx) {
    return board.squares[idx].isEmpty;
}
// ist ein Feld leer?

void generatePawnMoves(const Board& board, int idx,
                       Color us, MoveList& list) {
    int file = idx % 8;
    int rank = idx / 8;
    int dir  = (us == WHITE) ? 1 : -1;
    int startRank    = (us == WHITE) ? 1 : 6;
    int promoteRank  = (us == WHITE) ? 6 : 1;
    
// Generiert alle möglichen Züge für einen Bauern an der gegebenen Position (idx) und fügt sie zur Liste hinzu

int oneStep = squareIndex(file, rank + dir);
if (isOnBoard(file, rank + dir) && isEmpty(board, oneStep)) {
    if (rank == promoteRank) {
         addMove(list, idx, oneStep, QUEEN);
         addMove(list, idx, oneStep, ROOK);
         addMove(list, idx, oneStep, BISHOP);
         addMove(list, idx, oneStep, KNIGHT);
     } else {
          addMove(list, idx, oneStep);
       }
}
 // Ein Schritt vorwärts

    if (rank == startRank) {
        int twoStep = squareIndex(file, rank + 2 * dir);
        if (isOnBoard(file, rank + 2 * dir) && isEmpty(board, oneStep) && isEmpty(board, twoStep))
            addMove(list, idx, twoStep);
    }

// Zwei Schritte vorwärts vom Startfeld

    for (int df = -1; df <= 1; df += 2) {
        int captureFile = file + df;
        if (isOnBoard(captureFile, rank + dir)) {
            int captureIdx = squareIndex(captureFile, rank + dir);
            if (isEnemy(board, captureIdx, us)) {
                if (rank == promoteRank) {
                    addMove(list, idx, captureIdx, QUEEN);
                    addMove(list, idx, captureIdx, ROOK);
                    addMove(list, idx, captureIdx, BISHOP);
                    addMove(list, idx, captureIdx, KNIGHT);
                } else {
                    addMove(list, idx, captureIdx);
                }
            }
        }
    }
// Schrägschläge (Captures)

    if (board.enPassantSquare != -1) {
        int epFile = board.enPassantSquare % 8;
        if (rank == ((us == WHITE) ? 4 : 3) && std::abs(epFile - file) == 1) {
            addMove(list, idx, board.enPassantSquare);
        }
    }
}
// En Passant

void generateKnightMoves(const Board& board, int idx,
                         Color us, MoveList& list) {
    int file = idx % 8;
    int rank = idx / 8;

    int jumps[8][2] = {
        {-2,-1},{-2,+1},{-1,-2},{-1,+2},
        {+1,-2},{+1,+2},{+2,-1},{+2,+1}
    };
// Spinger

    for (int i = 0; i < 8; i++) {
        int f = file + jumps[i][0];
        int r = rank + jumps[i][1];
        if (!isOnBoard(f, r)) continue;
        int target = squareIndex(f, r);
        if (isEmpty(board, target) || isEnemy(board, target, us))
            addMove(list, idx, target);
    }
}
// Generiert alle möglichen Züge für einen Springer an der gegebenen Position (idx) und fügt sie zur Liste hinzu

void generateSlidingMoves(const Board& board, int idx,
                          Color us, MoveList& list,
                          bool diagonal, bool straight) {
    int file = idx % 8;
    int rank = idx / 8;

    int dirs[8][2] = {
        {0,1},{0,-1},{1,0},{-1,0},   // gerade (Turm)
        {1,1},{1,-1},{-1,1},{-1,-1}  // diagonal (Läufer)
    };

    int start = straight ? 0 : 4;
    int end   = diagonal ? 8 : 4;
// Läufer und Turm und Dame

 for (int d = start; d < end; d++) {
        int f = file;
        int r = rank;

        while (true) {
            f += dirs[d][0];
            r += dirs[d][1];
            if (!isOnBoard(f, r)) break;
            int target = squareIndex(f, r);

            if (isEmpty(board, target)) {
                addMove(list, idx, target);
            } else {
                if (isEnemy(board, target, us))
                    addMove(list, idx, target);
                break;
            }
        }
    }
}
// Generiert alle möglichen Züge für eine gleitende Figur (Läufer, Turm, Dame) an der gegebenen Position (idx) und fügt sie zur Liste hinzu

void generateKingMoves(const Board& board, int idx,
                       Color us, MoveList& list) {
    int file = idx % 8;
    int rank = idx / 8;

    int dirs[8][2] = {
        {0,1},{0,-1},{1,0},{-1,0},
        {1,1},{1,-1},{-1,1},{-1,-1}
    };

    for (int i = 0; i < 8; i++) {
        int f = file + dirs[i][0];
        int r = rank + dirs[i][1];
        if (!isOnBoard(f, r)) continue;
        int target = squareIndex(f, r);
        if (isEmpty(board, target) || isEnemy(board, target, us))
            addMove(list, idx, target);
    }
// König

if (us == WHITE && (board.castlingRights & WHITE_KINGSIDE)) {
        if (isEmpty(board, squareIndex(5,0)) &&
            isEmpty(board, squareIndex(6,0)))
            addMove(list, idx, squareIndex(6,0));
    }
    if (us == BLACK && (board.castlingRights & BLACK_KINGSIDE)) {
        if (isEmpty(board, squareIndex(5,7)) &&
            isEmpty(board, squareIndex(6,7)))
            addMove(list, idx, squareIndex(6,7));
    }

    // Rochade Damenseite
    if (us == WHITE && (board.castlingRights & WHITE_QUEENSIDE)) {
        if (isEmpty(board, squareIndex(1,0)) &&
            isEmpty(board, squareIndex(2,0)) &&
            isEmpty(board, squareIndex(3,0)))
            addMove(list, idx, squareIndex(2,0));
    }
    if (us == BLACK && (board.castlingRights & BLACK_QUEENSIDE)) {
        if (isEmpty(board, squareIndex(1,7)) &&
            isEmpty(board, squareIndex(2,7)) &&
            isEmpty(board, squareIndex(3,7)))
            addMove(list, idx, squareIndex(2,7));
    }
}
// Rochade

MoveList generateAllMoves(const Board& board) {
    MoveList list;
    list.count = 0;
    Color us = board.sideToMove;

    for (int idx = 0; idx < 64; idx++) {
        const Square& sq = board.squares[idx];
        if (sq.isEmpty || sq.color != us) continue;

        switch (sq.piece) {
            case PAWN:
                generatePawnMoves(board, idx, us, list);
                break;
            case KNIGHT:
                generateKnightMoves(board, idx, us, list);
                break;
            case BISHOP:
                generateSlidingMoves(board, idx, us, list, true, false);
                break;
            case ROOK:
                generateSlidingMoves(board, idx, us, list, false, true);
                break;
            case QUEEN:
                generateSlidingMoves(board, idx, us, list, true, true);
                break;
            case KING:
                generateKingMoves(board, idx, us, list);
                break;
            default: break;
        }
    }
    return list;
}
// Generiert alle möglichen Züge für die aktuelle Stellung und gibt sie als MoveList zurück



