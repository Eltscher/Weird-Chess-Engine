#include "search.h"
#include <iostream>

int main() {
    Board board;
    setupStartPosition(board);
    printBoard(board);

    std::cout << "Engine denkt...\n";

    SearchResult result = findBestMove(board, 4);

    int fromFile = result.bestMove.from % 8;
    int fromRank = result.bestMove.from / 8;
    int toFile   = result.bestMove.to   % 8;
    int toRank   = result.bestMove.to   / 8;

    char files[] = "abcdefgh";
    std::cout << "Bester Zug: "
              << files[fromFile] << (fromRank + 1)
              << " -> "
              << files[toFile]   << (toRank + 1)
              << "\n";
    std::cout << "Score: " << result.score << "\n";

    return 0;
}