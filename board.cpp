#include "board.h"

int squareIndex(int file, int rank) {
    return rank * 8 + file;
}
//Rechnung Spalte (file) und Reihe (rank) in einen Index von 0–63 um

void clearBoard(Board& board) {
    for (int i = 0; i < 64; i++) {
        board.squares[i].piece   = NONE;
        board.squares[i].color   = WHITE;
        board.squares[i].isEmpty = true;
    }
    board.sideToMove      = WHITE;
    board.castlingRights  = WHITE_KINGSIDE | WHITE_QUEENSIDE |
                            BLACK_KINGSIDE | BLACK_QUEENSIDE;
    board.enPassantSquare = -1;
    board.halfMoveClock   = 0;
    board.fullMoveNumber  = 1;
}
// zurücksetzung des Schachbretts auf die Anfangsposition

void placePiece(Board& board, int file, int rank,
                PieceType piece, Color color) {
    int idx = squareIndex(file, rank);
    board.squares[idx].piece   = piece;
    board.squares[idx].color   = color;
    board.squares[idx].isEmpty = false;
}
// Platziert eine Figur auf dem Schachbrett an der angegebenen Position (file, rank)

void setupStartPosition(Board& board) {
    clearBoard(board);

    // Weiße Bauern (Reihe 2 = rank 1)
    for (int file = 0; file < 8; file++)
        placePiece(board, file, 1, PAWN, WHITE);

    // Schwarze Bauern (Reihe 7 = rank 6)
    for (int file = 0; file < 8; file++)
        placePiece(board, file, 6, PAWN, BLACK);

    // Weiße Hauptfiguren (Reihe 1 = rank 0)
    placePiece(board, 0, 0, ROOK,   WHITE);
    placePiece(board, 1, 0, KNIGHT, WHITE);
    placePiece(board, 2, 0, BISHOP, WHITE);
    placePiece(board, 3, 0, QUEEN,  WHITE);
    placePiece(board, 4, 0, KING,   WHITE);
    placePiece(board, 5, 0, BISHOP, WHITE);
    placePiece(board, 6, 0, KNIGHT, WHITE);
    placePiece(board, 7, 0, ROOK,   WHITE);

    // Schwarze Hauptfiguren (Reihe 8 = rank 7)
    placePiece(board, 0, 7, ROOK,   BLACK);
    placePiece(board, 1, 7, KNIGHT, BLACK);
    placePiece(board, 2, 7, BISHOP, BLACK);
    placePiece(board, 3, 7, QUEEN,  BLACK);
    placePiece(board, 4, 7, KING,   BLACK);
    placePiece(board, 5, 7, BISHOP, BLACK);
    placePiece(board, 6, 7, KNIGHT, BLACK);
    placePiece(board, 7, 7, ROOK,   BLACK);
}
// Initialisiert das Schachbrett mit der Standard-Startposition

char pieceToChar(PieceType p, Color c) {
    const char whites[] = {'P','N','B','R','Q','K',' '};
    const char blacks[] = {'p','n','b','r','q','k',' '};
    return (c == WHITE) ? whites[p] : blacks[p];
}
// Konvertiert einen PieceType und Color in ein Zeichen für die Darstellung

void printBoard(const Board& board) {
    std::cout << "\n  a b c d e f g h\n";
    std::cout << "  ----------------\n";

    for (int rank = 7; rank >= 0; rank--) {
        std::cout << (rank + 1) << " |";
        for (int file = 0; file < 8; file++) {
            int idx = squareIndex(file, rank);
            const Square& sq = board.squares[idx];
            if (sq.isEmpty)
                std::cout << ". ";
            else
                std::cout << pieceToChar(sq.piece, sq.color) << " ";
        }
        std::cout << "| " << (rank + 1) << "\n";
    }

    std::cout << "  ----------------\n";
    std::cout << "  a b c d e f g h\n\n";
    std::cout << "Am Zug: " << (board.sideToMove == WHITE ? "Weiß" : "Schwarz") << "\n";
}
// Brett im Terminal
