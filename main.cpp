#include "uci.h"
#include "transposition.h"
#include <iostream>

int main() {
    initZobrist();
    uciLoop();
    return 0;
}

// Großen Dank an das CPW (https://www.chessprogramming.org)