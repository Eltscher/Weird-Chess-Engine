#include "time_management.h"
#include <sstream>

TimeControl parseTimeControl(const std::string& line) {
    TimeControl tc;
    tc.wtime     = -1;
    tc.btime     = -1;
    tc.winc      =  0;
    tc.binc      =  0;
    tc.movetime  = -1;
    tc.movestogo =  0;

    std::istringstream ss(line);
    std::string token;

    while (ss >> token) {
        if (token == "wtime")     ss >> tc.wtime;
        else if (token == "btime")     ss >> tc.btime;
        else if (token == "winc")      ss >> tc.winc;
        else if (token == "binc")      ss >> tc.binc;
        else if (token == "movetime")  ss >> tc.movetime;
        else if (token == "movestogo") ss >> tc.movestogo;
    }
    return tc;
}
// Ließt die Zeit aus einem UCI-Befehl

int calculateDepth(const TimeControl& tc, bool isWhite) {
    // Feste Zeit pro Zug
    if (tc.movetime > 0) {
        if (tc.movetime > 5000) return 5;
        if (tc.movetime > 2000) return 4;
        if (tc.movetime > 500)  return 3;
        return 2;
    }
// Feste zeit pro Zug, falls vorgabe, kann angepasst werden

int timeLeft = isWhite ? tc.wtime : tc.btime;
    int inc = isWhite ? tc.winc  : tc.binc;

    if (timeLeft < 0)
        return 4;
//Verbleibende Zeit

int movesLeft = (tc.movestogo > 0) ? tc.movestogo : 30;
int timePerMove = (timeLeft + inc * movesLeft) / movesLeft;
//Berechnung der verbleibenden Züge bis zur Zeitkontrolle

if (timePerMove > 10000) return 5;  // >10 Sekunden
    if (timePerMove >  5000) return 4;  // >5 Sekunden
    if (timePerMove >  1000) return 3;  // >1 Sekunde
    if (timePerMove >   300) return 2;  // >300ms
    return 1;                           // Notfall
}
// Wahl der Suchtiefe nach Zeit