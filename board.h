#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>

enum PieceType {
    PAWN   = 0,
    KNIGHT = 1,
    BISHOP = 2,
    ROOK   = 3,
    QUEEN  = 4,
    KING   = 5,
    NONE   = 6
};

enum Color {
    WHITE = 0,
    BLACK = 1
};

enum CastlingRights {
    NO_CASTLING     = 0,
    WHITE_KINGSIDE  = 1,
    WHITE_QUEENSIDE = 2,
    BLACK_KINGSIDE  = 4,
    BLACK_QUEENSIDE = 8
};

struct Square {
    PieceType piece;
    Color     color;
    bool      isEmpty;
};

struct Board {
    Square squares[64];
    Color  sideToMove;
    int    castlingRights;
    int    enPassantSquare;
    int    halfMoveClock;
    int    fullMoveNumber;
};

// Funktions-Signaturen
int  squareIndex(int file, int rank);
void clearBoard(Board& board);
void placePiece(Board& board, int file, int rank, PieceType piece, Color color);
void setupStartPosition(Board& board);
char pieceToChar(PieceType p, Color c);
void printBoard(const Board& board);

#endif