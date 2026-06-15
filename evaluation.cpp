#include "evaluation.h"

const int PIECE_VALUES[7] = {
    100,  // PAWN
    320,  // KNIGHT
    330,  // BISHOP
    500,  // ROOK
    900,  // QUEEN
    0,    // KING
    0     // NONE
};

// Gibt jeder Figur einen Grundwert

//Postionstabellen YAY

const int PAWN_TABLE[64] = {
     0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
     5,  5, 10, 25, 25, 10,  5,  5,
     0,  0,  0, 20, 20,  0,  0,  0,
     5, -5,-10,  0,  0,-10, -5,  5,
     5, 10, 10,-20,-20, 10, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0
};

const int KNIGHT_TABLE[64] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50
};

const int BISHOP_TABLE[64] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
};

const int ROOK_TABLE[64] = {
     0,  0,  0,  0,  0,  0,  0,  0,
     5, 10, 10, 10, 10, 10, 10,  5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
     0,  0,  0,  5,  5,  0,  0,  0
};

const int QUEEN_TABLE[64] = {
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
     -5,  0,  5,  5,  5,  5,  0, -5,
      0,  0,  5,  5,  5,  5,  0, -5,
    -10,  5,  5,  5,  5,  5,  0,-10,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
};

const int KING_TABLE[64] = {
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -10,-20,-20,-20,-20,-20,-20,-10,
     20, 20,  0,  0,  0,  0, 20, 20,
     20, 30, 10,  0,  0, 10, 30, 20
};

const int KING_ENDGAME_TABLE[64] = {
    -50,-40,-30,-20,-20,-30,-40,-50,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -50,-30,-30,-30,-30,-30,-30,-50
};

int getPieceTableValue(PieceType piece, Color color,
                       int square, bool endgame) {
    int idx = (color == WHITE) ? (63 - square) : square;

    switch (piece) {
        case PAWN:   return PAWN_TABLE[idx];
        case KNIGHT: return KNIGHT_TABLE[idx];
        case BISHOP: return BISHOP_TABLE[idx];
        case ROOK:   return ROOK_TABLE[idx];
        case QUEEN:  return QUEEN_TABLE[idx];
        case KING:   return endgame ? KING_ENDGAME_TABLE[idx]
                                    : KING_TABLE[idx];
        default:     return 0;
    }
}
// Gibt den Wert der Position einer Figur zurück, abhängig von ihrer Art, Farbe und Position auf dem Brett
bool isEndgameEval(const Board& board) {
    int queens  = 0;
    int pieces  = 0;
    for (int i = 0; i < 64; i++) {
        if (board.squares[i].isEmpty) continue;
        if (board.squares[i].piece == QUEEN)  queens++;
        if (board.squares[i].piece == ROOK  ||
            board.squares[i].piece == BISHOP ||
            board.squares[i].piece == KNIGHT)  pieces++;
    }
    return queens == 0 || (queens == 2 && pieces <= 2);
}
// Gibt zurück, ob die Stellung als Endspiel bewertet werden sollte

int evaluatePawnStructure(const Board& board, Color color) {
    int score = 0;
    int pawnsOnFile[8] = {0};

    // Bauern zaehlen
    for (int sq = 0; sq < 64; sq++) {
        if (!board.squares[sq].isEmpty &&
             board.squares[sq].piece == PAWN &&
             board.squares[sq].color == color) {
            int file = sq % 8;
            pawnsOnFile[file]++;
        }
    }

    for (int file = 0; file < 8; file++) {
        // Doppelte Bauern bestrafen
        if (pawnsOnFile[file] > 1)
            score -= 30 * (pawnsOnFile[file] - 1);

        // Isolierte Bauern bestrafen
        if (pawnsOnFile[file] > 0) {
            bool leftEmpty  = (file == 0 || pawnsOnFile[file-1] == 0);
            bool rightEmpty = (file == 7 || pawnsOnFile[file+1] == 0);
            if (leftEmpty && rightEmpty)
                score -= 20;
        }
    }

    return score;
}

int evaluateKingSafety(const Board& board, Color color) {
    int score     = 0;
    int kingSquare = -1;

    // Koenig finden
    for (int sq = 0; sq < 64; sq++) {
        if (!board.squares[sq].isEmpty &&
             board.squares[sq].piece == KING &&
             board.squares[sq].color == color) {
            kingSquare = sq;
            break;
        }
    }

    if (kingSquare == -1) return 0;

    int kingFile = kingSquare % 8;
    int kingRank = kingSquare / 8;
    int dir      = (color == WHITE) ? 1 : -1;

    // Bauernschild pruefen
    for (int df = -1; df <= 1; df++) {
        int f = kingFile + df;
        int r = kingRank + dir;
        if (f < 0 || f > 7 || r < 0 || r > 7) continue;
        int shieldSq = r * 8 + f;
        if (!board.squares[shieldSq].isEmpty &&
             board.squares[shieldSq].piece == PAWN &&
             board.squares[shieldSq].color == color)
            score += 10; // Bauer vor Koenig = gut
    }

    // Koenig in der Mitte bestrafen (Eroeffnung/Mittelspiel)
    if (kingFile >= 3 && kingFile <= 4)
        score -= 20;

    return score;
}

int evaluateRooks(const Board& board, Color color) {
    int score = 0;

    for (int sq = 0; sq < 64; sq++) {
        if (board.squares[sq].isEmpty) continue;
        if (board.squares[sq].piece != ROOK) continue;
        if (board.squares[sq].color != color) continue;

        int file = sq % 8;
        bool openFile = true;

        // Offene Linie pruefen (keine Bauern)
        for (int rank = 0; rank < 8; rank++) {
            int checkSq = rank * 8 + file;
            if (!board.squares[checkSq].isEmpty &&
                 board.squares[checkSq].piece == PAWN) {
                openFile = false;
                break;
            }
        }

        if (openFile)
            score += 25; // Turm auf offener Linie
    }

    return score;
}

int evaluateBoard(const Board& board) {
    int score   = 0;
    bool endgame = isEndgameEval(board);

    // Material + Piece-Square Tables
    for (int idx = 0; idx < 64; idx++) {
        const Square& sq = board.squares[idx];
        if (sq.isEmpty) continue;

        int value = PIECE_VALUES[sq.piece]
                  + getPieceTableValue(sq.piece, sq.color, idx, endgame);

        if (sq.color == WHITE) score += value;
        else                   score -= value;
    }

    // Bauernstruktur
    score += evaluatePawnStructure(board, WHITE);
    score -= evaluatePawnStructure(board, BLACK);

    // Koenigssicherheit (nur im Mittelspiel)
    if (!endgame) {
        score += evaluateKingSafety(board, WHITE);
        score -= evaluateKingSafety(board, BLACK);
    }

    // Turmaktivitaet
    score += evaluateRooks(board, WHITE);
    score -= evaluateRooks(board, BLACK);

    return score;
}

// Berechnung des Gesamtwerts der Stellung

