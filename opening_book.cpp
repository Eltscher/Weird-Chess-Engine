#include "opening_book.h"
#include <cstdlib>

const std::vector<BookEntry> BOOK = {

    // ===========================
    // E4 EROEFFNUNGEN
    // ===========================

    // --- Italienisch ---
    {"e2e4 e7e5 g1f3 b8c6 f1c4", "Italienisch"},
    {"e2e4 e7e5 g1f3 b8c6 f1c4 f8c5", "Italienisch — Giuoco Piano"},
    {"e2e4 e7e5 g1f3 b8c6 f1c4 f8c5 c2c3", "Italienisch — c3"},
    {"e2e4 e7e5 g1f3 b8c6 f1c4 f8c5 c2c3 g8f6", "Italienisch — c3 Nf6"},
    {"e2e4 e7e5 g1f3 b8c6 f1c4 f8c5 c2c3 d7d6", "Italienisch — c3 d6"},
    {"e2e4 e7e5 g1f3 b8c6 f1c4 f8c5 b2b4", "Italienisch — Evans Gambit"},
    {"e2e4 e7e5 g1f3 b8c6 f1c4 f8c5 b2b4 c5b4", "Evans Gambit angenommen"},
    {"e2e4 e7e5 g1f3 b8c6 f1c4 g8f6", "Italienisch — Zwei Springer"},
    {"e2e4 e7e5 g1f3 b8c6 f1c4 g8f6 d2d3", "Italienisch — d3"},
    {"e2e4 e7e5 g1f3 b8c6 f1c4 g8f6 f3g5", "Italienisch — Ng5 Angriff"},
    {"e2e4 e7e5 g1f3 b8c6 f1c4 g8f6 f3g5 d7d5", "Italienisch — Zwei Springer d5"},
    {"e2e4 e7e5 g1f3 b8c6 f1c4 f8e7", "Italienisch — Ungarisch"},

    // --- Spanisch ---
    {"e2e4 e7e5 g1f3 b8c6 f1b5", "Spanisch"},
    {"e2e4 e7e5 g1f3 b8c6 f1b5 a7a6", "Spanisch — Morphy"},
    {"e2e4 e7e5 g1f3 b8c6 f1b5 a7a6 b5a4 g8f6", "Spanisch — Offene Variante"},
    {"e2e4 e7e5 g1f3 b8c6 f1b5 a7a6 b5a4 g8f6 e1g1", "Spanisch — Hauptvariante"},
    {"e2e4 e7e5 g1f3 b8c6 f1b5 a7a6 b5a4 g8f6 e1g1 f8e7", "Spanisch — Geschlossen"},
    {"e2e4 e7e5 g1f3 b8c6 f1b5 a7a6 b5a4 g8f6 e1g1 f8e7 f1e1 b7b5", "Spanisch — Hauptlinie"},
    {"e2e4 e7e5 g1f3 b8c6 f1b5 a7a6 b5c6", "Spanisch — Tauschvariante"},
    {"e2e4 e7e5 g1f3 b8c6 f1b5 f8c5", "Spanisch — Klassisch"},
    {"e2e4 e7e5 g1f3 b8c6 f1b5 g8f6", "Spanisch — Berliner"},
    {"e2e4 e7e5 g1f3 b8c6 f1b5 d7d6", "Spanisch — Steinitz"},
    {"e2e4 e7e5 g1f3 b8c6 f1b5 g7g6", "Spanisch — Smyslov"},
    {"e2e4 e7e5 g1f3 b8c6 f1b5 a7a6 b5a4 d7d6", "Spanisch — Steinitz verzoegert"},

    // --- Sizilianisch ---
    {"e2e4 c7c5", "Sizilianisch"},
    {"e2e4 c7c5 g1f3", "Sizilianisch — Open"},
    {"e2e4 c7c5 g1f3 d7d6 d2d4 c5d4 f3d4", "Sizilianisch — Open d6"},
    {"e2e4 c7c5 g1f3 d7d6 d2d4 c5d4 f3d4 g8f6 b1c3", "Sizilianisch — Hauptvariante"},
    {"e2e4 c7c5 g1f3 d7d6 d2d4 c5d4 f3d4 g8f6 b1c3 a7a6", "Sizilianisch — Najdorf"},
    {"e2e4 c7c5 g1f3 d7d6 d2d4 c5d4 f3d4 g8f6 b1c3 g7g6", "Sizilianisch — Drache"},
    {"e2e4 c7c5 g1f3 d7d6 d2d4 c5d4 f3d4 g8f6 b1c3 e7e6", "Sizilianisch — Scheveningen"},
    {"e2e4 c7c5 g1f3 b8c6 d2d4 c5d4 f3d4", "Sizilianisch — Klassisch"},
    {"e2e4 c7c5 g1f3 b8c6 d2d4 c5d4 f3d4 g8f6 b1c3 d7d6", "Sizilianisch — Klassisch d6"},
    {"e2e4 c7c5 g1f3 e7e6 d2d4 c5d4 f3d4", "Sizilianisch — Kan"},
    {"e2e4 c7c5 b1c3", "Sizilianisch — Geschlossen"},
    {"e2e4 c7c5 b1c3 b8c6 g2g3", "Sizilianisch — Geschlossen g3"},
    {"e2e4 c7c5 c2c3", "Sizilianisch — Alapin"},
    {"e2e4 c7c5 c2c3 g8f6", "Sizilianisch — Alapin Nf6"},
    {"e2e4 c7c5 c2c3 d7d5", "Sizilianisch — Alapin d5"},
    {"e2e4 c7c5 f2f4", "Sizilianisch — Grand Prix Angriff"},
    {"e2e4 c7c5 g1f3 d7d6 f1b5", "Sizilianisch — Rossolimo"},
    {"e2e4 c7c5 g1f3 b8c6 f1b5", "Sizilianisch — Rossolimo Nc6"},

    // --- Franzoesisch ---
    {"e2e4 e7e6", "Franzoesisch"},
    {"e2e4 e7e6 d2d4 d7d5", "Franzoesisch — Hauptvariante"},
    {"e2e4 e7e6 d2d4 d7d5 b1c3", "Franzoesisch — Winawer Vorbereitung"},
    {"e2e4 e7e6 d2d4 d7d5 b1c3 f8b4", "Franzoesisch — Winawer"},
    {"e2e4 e7e6 d2d4 d7d5 b1c3 g8f6", "Franzoesisch — Klassisch"},
    {"e2e4 e7e6 d2d4 d7d5 b1c3 g8f6 c1g5", "Franzoesisch — Klassisch Bg5"},
    {"e2e4 e7e6 d2d4 d7d5 b1d2", "Franzoesisch — Tarrasch"},
    {"e2e4 e7e6 d2d4 d7d5 b1d2 g8f6", "Franzoesisch — Tarrasch Nf6"},
    {"e2e4 e7e6 d2d4 d7d5 b1d2 c7c5", "Franzoesisch — Tarrasch c5"},
    {"e2e4 e7e6 d2d4 d7d5 e4e5", "Franzoesisch — Vormarsch"},
    {"e2e4 e7e6 d2d4 d7d5 e4e5 c7c5", "Franzoesisch — Vormarsch c5"},
    {"e2e4 e7e6 d2d4 d7d5 e4d5", "Franzoesisch — Tausch"},

    // --- Caro-Kann ---
    {"e2e4 c7c6", "Caro-Kann"},
    {"e2e4 c7c6 d2d4 d7d5", "Caro-Kann — Hauptvariante"},
    {"e2e4 c7c6 d2d4 d7d5 b1c3", "Caro-Kann — Klassisch"},
    {"e2e4 c7c6 d2d4 d7d5 b1c3 d5e4 c3e4", "Caro-Kann — Klassisch Hauptlinie"},
    {"e2e4 c7c6 d2d4 d7d5 b1d2", "Caro-Kann — Smyslov"},
    {"e2e4 c7c6 d2d4 d7d5 e4e5", "Caro-Kann — Vormarsch"},
    {"e2e4 c7c6 d2d4 d7d5 e4d5", "Caro-Kann — Panov Angriff"},
    {"e2e4 c7c6 d2d4 d7d5 e4d5 c6d5 c2c4", "Caro-Kann — Panov"},
    {"e2e4 c7c6 c2c4", "Caro-Kann — c4"},

    // --- Pirc / Modernes ---
    {"e2e4 d7d6 d2d4 g8f6 b1c3 g7g6", "Pirc"},
    {"e2e4 d7d6 d2d4 g8f6 b1c3 g7g6 f2f4", "Pirc — Oesterreichischer Angriff"},
    {"e2e4 d7d6 d2d4 g8f6 b1c3 g7g6 c1e3", "Pirc — Klassisch"},
    {"e2e4 g7g6 d2d4 f8g7", "Modernes"},
    {"e2e4 g7g6 d2d4 f8g7 b1c3 d7d6", "Modernes — Hauptvariante"},

    // --- Skandinavisch ---
    {"e2e4 d7d5", "Skandinavisch"},
    {"e2e4 d7d5 e4d5", "Skandinavisch — Hauptvariante"},
    {"e2e4 d7d5 e4d5 d8d5 b1c3", "Skandinavisch — c3"},
    {"e2e4 d7d5 e4d5 g8f6", "Skandinavisch — Marshall"},
    {"e2e4 d7d5 e4d5 d8d5 b1c3 d5a5", "Skandinavisch — Qa5"},

    // --- Koenigsgambit ---
    {"e2e4 e7e5 f2f4", "Koenigsgambit"},
    {"e2e4 e7e5 f2f4 e5f4", "Koenigsgambit — Angenommen"},
    {"e2e4 e7e5 f2f4 e5f4 g1f3", "Koenigsgambit — Nf3"},
    {"e2e4 e7e5 f2f4 e5f4 g1f3 g7g5", "Koenigsgambit — g5"},
    {"e2e4 e7e5 f2f4 f8c5", "Koenigsgambit — Abgelehnt Bc5"},
    {"e2e4 e7e5 f2f4 d7d5", "Koenigsgambit — Falkbeer"},

    // --- Wiener Spiel ---
    {"e2e4 e7e5 b1c3", "Wiener Spiel"},
    {"e2e4 e7e5 b1c3 g8f6", "Wiener Spiel — Nf6"},
    {"e2e4 e7e5 b1c3 f8c5", "Wiener Spiel — Bc5"},
    {"e2e4 e7e5 b1c3 b8c6 f2f4", "Wiener Gambit"},

    // --- Petrov ---
    {"e2e4 e7e5 g1f3 g8f6", "Petrov"},
    {"e2e4 e7e5 g1f3 g8f6 f3e5", "Petrov — Hauptvariante"},
    {"e2e4 e7e5 g1f3 g8f6 f3e5 d7d6 e5f3 f6e4 d2d4", "Petrov — Klassisch"},
    {"e2e4 e7e5 g1f3 g8f6 d2d4", "Petrov — Moderncenter"},

    // ===========================
    // D4 EROEFFNUNGEN
    // ===========================

    // --- Damengambit ---
    {"d2d4 d7d5 c2c4", "Damengambit"},
    {"d2d4 d7d5 c2c4 e7e6", "Damengambit — Abgelehnt"},
    {"d2d4 d7d5 c2c4 e7e6 b1c3 g8f6 g1f3", "Damengambit — Hauptvariante"},
    {"d2d4 d7d5 c2c4 e7e6 b1c3 g8f6 c1g5", "Damengambit — Bg5"},
    {"d2d4 d7d5 c2c4 e7e6 b1c3 f8e7", "Damengambit — Klassisch"},
    {"d2d4 d7d5 c2c4 d5c4", "Damengambit — Angenommen"},
    {"d2d4 d7d5 c2c4 d5c4 g1f3", "Damengambit — Angenommen Nf3"},
    {"d2d4 d7d5 c2c4 d5c4 e2e4", "Damengambit — Angenommen e4"},
    {"d2d4 d7d5 c2c4 c7c6", "Slawisch"},
    {"d2d4 d7d5 c2c4 c7c6 g1f3 g8f6", "Slawisch — Hauptvariante"},
    {"d2d4 d7d5 c2c4 c7c6 g1f3 g8f6 b1c3", "Slawisch — c3"},
    {"d2d4 d7d5 c2c4 c7c6 g1f3 g8f6 b1c3 d5c4", "Slawisch — Angenommen"},
    {"d2d4 d7d5 c2c4 c7c6 b1c3 g8f6 g1f3 e7e6", "Halbslawisch"},
    {"d2d4 d7d5 c2c4 c7c6 b1c3 g8f6 g1f3 e7e6 c1g5", "Botvinnik"},
    {"d2d4 d7d5 c2c4 c7c6 b1c3 g8f6 g1f3 e7e6 e2e3", "Meran"},

    // --- Koenigsindisch ---
    {"d2d4 g8f6 c2c4 g7g6", "Koenigsindisch"},
    {"d2d4 g8f6 c2c4 g7g6 b1c3 f8g7", "Koenigsindisch — Fianchetto"},
    {"d2d4 g8f6 c2c4 g7g6 b1c3 f8g7 e2e4 d7d6", "Koenigsindisch — Hauptvariante"},
    {"d2d4 g8f6 c2c4 g7g6 b1c3 f8g7 e2e4 d7d6 g1f3", "Koenigsindisch — Klassisch"},
    {"d2d4 g8f6 c2c4 g7g6 b1c3 f8g7 e2e4 d7d6 g1f3 e8g8", "Koenigsindisch — Hauptlinie"},
    {"d2d4 g8f6 c2c4 g7g6 b1c3 f8g7 e2e4 d7d6 f2f3", "Koenigsindisch — Saemisch"},
    {"d2d4 g8f6 c2c4 g7g6 b1c3 f8g7 e2e4 d7d6 c1e3", "Koenigsindisch — Averbakh"},
    {"d2d4 g8f6 c2c4 g7g6 g1f3 f8g7 g2g3", "Koenigsindisch — Fianchetto"},
    {"d2d4 g8f6 c2c4 g7g6 g1f3 f8g7 g2g3 e8g8 f1g2 d7d6", "Koenigsindisch — Fianchetto Hauptlinie"},

    // --- Nimzoindisch ---
    {"d2d4 g8f6 c2c4 e7e6 b1c3 f8b4", "Nimzoindisch"},
    {"d2d4 g8f6 c2c4 e7e6 b1c3 f8b4 e2e3", "Nimzoindisch — Rubinstein"},
    {"d2d4 g8f6 c2c4 e7e6 b1c3 f8b4 d1c2", "Nimzoindisch — Klassisch"},
    {"d2d4 g8f6 c2c4 e7e6 b1c3 f8b4 a2a3", "Nimzoindisch — Saemisch"},
    {"d2d4 g8f6 c2c4 e7e6 b1c3 f8b4 g1f3", "Nimzoindisch — Drei Springer"},
    {"d2d4 g8f6 c2c4 e7e6 b1c3 f8b4 f2f3", "Nimzoindisch — Leningrad"},

    // --- Damensindisch ---
    {"d2d4 g8f6 c2c4 e7e6 g1f3 b7b6", "Damensindisch"},
    {"d2d4 g8f6 c2c4 e7e6 g1f3 b7b6 e2e3", "Damensindisch — e3"},
    {"d2d4 g8f6 c2c4 e7e6 g1f3 b7b6 g2g3", "Damensindisch — Fianchetto"},
    {"d2d4 g8f6 c2c4 e7e6 g1f3 b7b6 b1c3", "Damensindisch — c3"},

    // --- Gruenfeld ---
    {"d2d4 g8f6 c2c4 g7g6 b1c3 d7d5", "Gruenfeld"},
    {"d2d4 g8f6 c2c4 g7g6 b1c3 d7d5 c4d5 f6d5", "Gruenfeld — Tausch"},
    {"d2d4 g8f6 c2c4 g7g6 b1c3 d7d5 c4d5 f6d5 e2e4", "Gruenfeld — Russisch"},
    {"d2d4 g8f6 c2c4 g7g6 b1c3 d7d5 g1f3", "Gruenfeld — Nf3"},
    {"d2d4 g8f6 c2c4 g7g6 b1c3 d7d5 d1b3", "Gruenfeld — Katalanisch"},

    // --- Benoni ---
    {"d2d4 g8f6 c2c4 c7c5 d4d5", "Benoni"},
    {"d2d4 g8f6 c2c4 c7c5 d4d5 e7e6", "Benoni — Modernes"},
    {"d2d4 g8f6 c2c4 c7c5 d4d5 e7e6 b1c3 e6d5 c4d5 d7d6", "Benoni — Hauptvariante"},
    {"d2d4 g8f6 c2c4 c7c5 d4d5 e7e6 b1c3 e6d5 c4d5 g7g6", "Benoni — Fianchetto"},

    // --- Hollaendisch ---
    {"d2d4 f7f5", "Hollaendisch"},
    {"d2d4 f7f5 c2c4 g8f6", "Hollaendisch — Nf6"},
    {"d2d4 f7f5 c2c4 g8f6 g2g3", "Hollaendisch — Fianchetto"},
    {"d2d4 f7f5 c2c4 e7e6", "Hollaendisch — Klassisch"},
    {"d2d4 f7f5 c2c4 g8f6 b1c3 e7e6 g1f3 f8e7", "Hollaendisch — Klassisch Hauptlinie"},
    {"d2d4 f7f5 c2c4 g8f6 b1c3 g7g6", "Hollaendisch — Leningrad"},

    // --- Londoner System ---
    {"d2d4 d7d5 g1f3 g8f6 c1f4", "Londoner System"},
    {"d2d4 d7d5 g1f3 g8f6 c1f4 e7e6", "Londoner System — e6"},
    {"d2d4 d7d5 g1f3 g8f6 c1f4 c7c5", "Londoner System — c5"},
    {"d2d4 g8f6 g1f3 d7d5 c1f4", "Londoner System — Nf6"},
    {"d2d4 g8f6 g1f3 e7e6 c1f4", "Londoner System — e6"},

    // --- Tromp / Trompowsky ---
    {"d2d4 g8f6 c1g5", "Trompowsky"},
    {"d2d4 g8f6 c1g5 d7d5", "Trompowsky — d5"},
    {"d2d4 g8f6 c1g5 g8e4", "Trompowsky — Ne4"},

    // ===========================
    // NF3 / C4 EROEFFNUNGEN
    // ===========================

    // --- Englisch ---
    {"c2c4", "Englisch"},
    {"c2c4 e7e5", "Englisch — e5"},
    {"c2c4 e7e5 b1c3", "Englisch — c3"},
    {"c2c4 e7e5 b1c3 g8f6", "Englisch — Nf6"},
    {"c2c4 e7e5 b1c3 g8f6 g1f3 b8c6", "Englisch — Vier Springer"},
    {"c2c4 c7c5", "Englisch — Symmetrisch"},
    {"c2c4 c7c5 b1c3", "Englisch — Symmetrisch c3"},
    {"c2c4 c7c5 b1c3 g8f6 g1f3", "Englisch — Symmetrisch Nf3"},
    {"c2c4 c7c5 g1f3 g8f6", "Englisch — Symmetrisch Nf6"},
    {"c2c4 g8f6 b1c3", "Englisch — Nf6"},
    {"c2c4 g8f6 b1c3 d7d5", "Englisch — d5"},
    {"c2c4 g8f6 b1c3 e7e5", "Englisch — Umgekehrter Sizilianer"},
    {"c2c4 g8f6 g1f3 g7g6", "Englisch — g6"},
    {"c2c4 e7e6 b1c3", "Englisch — e6"},

    // --- Reti ---
    {"g1f3", "Reti"},
    {"g1f3 d7d5 c2c4", "Reti — Hauptvariante"},
    {"g1f3 d7d5 c2c4 d5c4", "Reti — Angenommen"},
    {"g1f3 d7d5 g2g3", "Reti — g3"},
    {"g1f3 d7d5 g2g3 g8f6 f1g2", "Reti — Fianchetto"},
    {"g1f3 g8f6 c2c4 g7g6", "Reti — g6"},
    {"g1f3 g8f6 c2c4 e7e6 g2g3", "Reti — e6 g3"},
    {"g1f3 d7d5 c2c4 e7e6 g2g3 g8f6 f1g2 f8e7", "Katalanisch"},
    {"g1f3 d7d5 c2c4 e7e6 g2g3 g8f6 f1g2 f8e7 e1g1 e8g8", "Katalanisch — Offen"},

    // --- Katalanisch ---
    {"d2d4 g8f6 c2c4 e7e6 g2g3", "Katalanisch"},
    {"d2d4 g8f6 c2c4 e7e6 g2g3 d7d5 f1g2", "Katalanisch — Hauptvariante"},
    {"d2d4 g8f6 c2c4 e7e6 g2g3 d7d5 f1g2 f8e7 g1f3", "Katalanisch — Geschlossen"},
    {"d2d4 g8f6 c2c4 e7e6 g2g3 d7d5 f1g2 d5c4", "Katalanisch — Offen"},

    // ===========================
    // UNREGULMAESSIGE / WEITERE
    // ===========================

    // --- Bird ---
    {"f2f4", "Bird"},
    {"f2f4 d7d5 g1f3", "Bird — Hauptvariante"},
    {"f2f4 e7e5", "Bird — From Gambit"},

    // --- Sokolsky ---
    {"b2b4", "Sokolsky"},
    {"b2b4 e7e5 c1b2", "Sokolsky — Hauptvariante"},

    // --- Nimzowitsch-Larsen ---
    {"b2b3", "Nimzowitsch-Larsen"},
    {"b2b3 e7e5 c1b2", "Nimzowitsch-Larsen — e5"},
    {"b2b3 d7d5 c1b2", "Nimzowitsch-Larsen — d5"},

    // --- Polnisch ---
    {"b2b4 e7e5 c1b2 f8b4", "Polnisch"},

    // --- Van't Kruijs ---
    {"e2e3", "Van't Kruijs"},

    // --- Grob ---
    {"g2g4", "Grob"},
    {"g2g4 d7d5 c1g5", "Grob — Hauptvariante"},

    // --- Blackmar-Diemer Gambit ---
    {"d2d4 d7d5 e2e4 d5e4 b1c3", "Blackmar-Diemer Gambit"},
    {"d2d4 d7d5 e2e4 d5e4 b1c3 g8f6 f2f3", "Blackmar-Diemer — Hauptvariante"},

    // --- Budapest Gambit ---
    {"d2d4 g8f6 c2c4 e7e5", "Budapest Gambit"},
    {"d2d4 g8f6 c2c4 e7e5 d4e5 f6e4", "Budapest Gambit — Hauptvariante"},

    // --- Aljechin ---
    {"e2e4 g8f6", "Aljechin"},
    {"e2e4 g8f6 e4e5 f6d5", "Aljechin — Hauptvariante"},
    {"e2e4 g8f6 e4e5 f6d5 d2d4 d7d6", "Aljechin — Klassisch"},
    {"e2e4 g8f6 e4e5 f6d5 c2c4 d5b6 d2d4", "Aljechin — Vier Bauern"},

    // --- Nimzowitsch ---
    {"e2e4 b8c6", "Nimzowitsch"},
    {"e2e4 b8c6 d2d4 d7d5", "Nimzowitsch — d5"},
    {"e2e4 b8c6 g1f3 d7d6", "Nimzowitsch — d6"},

    // --- Owen ---
    {"e2e4 b7b6", "Owen"},
    {"e2e4 b7b6 d2d4 c8b7", "Owen — Hauptvariante"},

    // --- Englund Gambit ---
    {"d2d4 e7e5", "Englund Gambit"},
    {"d2d4 e7e5 d4e5 b8c6", "Englund Gambit — Hauptvariante"},

    // --- Benko Gambit ---
    {"d2d4 g8f6 c2c4 c7c5 d4d5 b7b5", "Benko Gambit"},
    {"d2d4 g8f6 c2c4 c7c5 d4d5 b7b5 c4b5 a7a6", "Benko Gambit — Hauptvariante"},
    {"d2d4 g8f6 c2c4 c7c5 d4d5 b7b5 c4b5 a7a6 b5a6", "Benko Gambit — Angenommen"},

    // --- Volga Gambit ---
    {"d2d4 g8f6 c2c4 c7c5 d4d5 b7b5 c4b5 a7a6 e2e3", "Volga Gambit"},

    // --- Doppel-Koenigsindisch ---
    {"d2d4 g8f6 g1f3 g7g6 c2c4 f8g7 b1c3 e8g8", "Doppel-Koenigsindisch"},

    // --- Colle System ---
    {"d2d4 d7d5 g1f3 g8f6 e2e3", "Colle System"},
    {"d2d4 d7d5 g1f3 g8f6 e2e3 e7e6 f1d3", "Colle — Hauptvariante"},

    // --- Stonewall ---
    {"d2d4 d7d5 e2e3 g8f6 f1d3 c7c5 c2c3 b8c6 f2f4", "Stonewall"},

    // --- Torre Angriff ---
    {"d2d4 g8f6 g1f3 e7e6 c1g5", "Torre Angriff"},
    {"d2d4 g8f6 g1f3 d7d5 c1g5", "Torre Angriff — d5"},
};

bool hasBookMove(const std::vector<std::string>& playedMoves) {
    std::string played = "";
    for (size_t i = 0; i < playedMoves.size(); i++) {
        if (i > 0) played += " ";
        played += playedMoves[i];
    }

    for (const BookEntry& entry : BOOK) {
        if (entry.moves.find(played) == 0 && entry.moves.size() > played.size())
            return true;
    }
    return false;
}

bool isInOpeningBook(const std::vector<std::string>& playedMoves) {
    std::string played = "";
    for (size_t i = 0; i < playedMoves.size(); i++) {
        if (i > 0) played += " ";
        played += playedMoves[i];
    }

    for (const BookEntry& entry : BOOK) {
        if (entry.moves.find(played) == 0)
            return true;
    }
    return false;
}

Move getBookMove(const Board& board, const std::vector<std::string>& playedMoves) {
    std::string played = "";
    for (size_t i = 0; i < playedMoves.size(); i++) {
        if (i > 0) played += " ";
        played += playedMoves[i];
    }

    std::vector<std::string> candidates;
    for (const BookEntry& entry : BOOK) {
        if (entry.moves.find(played) == 0 && entry.moves.size() > played.size()) {
            std::string rest = entry.moves.substr(played.empty() ? 0 : played.size() + 1);
            std::string nextMove = rest.substr(0, rest.find(' '));
            if (nextMove.size() >= 4)
                candidates.push_back(nextMove);
        }
    }

    if (!candidates.empty()) {
        std::string chosen = candidates[rand() % candidates.size()];
        Move move;
        move.from      = squareIndex(chosen[0]-'a', chosen[1]-'1');
        move.to        = squareIndex(chosen[2]-'a', chosen[3]-'1');
        move.promotion = NONE;
        return move;
    }

    MoveList legal = generateLegalMoves(board);
    if (legal.count > 0) return legal.moves[0];
    return Move{};
}
