#include "move_generation.h"  // Kennt jetzt board.h UND move_generation.h
#include <iostream>

int main() {
    Board board;                      // Brett erstellen
    setupStartPosition(board);        // Figuren aufstellen
    printBoard(board);                // Brett anzeigen

    MoveList moves = generateAllMoves(board);              // Züge generieren
    std::cout << "Mögliche Züge: " << moves.count << "\n"; // Anzahl ausgeben

    return 0;  // Programm erfolgreich beendet
}