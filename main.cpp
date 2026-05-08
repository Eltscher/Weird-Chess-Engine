#include "move_generation.h"
#include "move_validation.h"  // Kennt jetzt board.h UND move_generation.h
#include <iostream>

int main() {
    Board board;                      // Brett erstellen
    setupStartPosition(board);        // Figuren aufstellen
    printBoard(board);                // Brett anzeigen

    MoveList moves = generateAllMoves(board);              // Züge generieren
    std::cout << "Mögliche Züge: " << moves.count << "\n"; // Anzahl ausgeben

    if (isCheckmate(board))
        std::cout << "Schachmatt!\n";
    else if (isStalemate(board))
        std::cout << "Patt!\n";
    else
        std::cout << "Spiel läuft.\n";
    
    return 0;  // Programm erfolgreich beendet
}