#ifndef TIME_MANAGEMENT_H
#define TIME_MANAGEMENT_H

#include <chrono>
#include <string>

struct TimeControl {
    int wtime;      // Weisse Zeit in ms (-1 = unbekannt)
    int btime;      // Schwarze Zeit in ms (-1 = unbekannt)
    int winc;       // Weisses Inkrement in ms
    int binc;       // Schwarzes Inkrement in ms
    int movetime;   // Feste Zeit pro Zug (-1 = nicht gesetzt)
    int movestogo;  // Züge bis zur Zeitkontrolle (0 = unbekannt)
};

TimeControl parseTimeControl(const std::string& line);
int calculateDepth(const TimeControl& tc, bool isWhite);

#endif